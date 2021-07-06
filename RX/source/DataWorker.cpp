#include "../include/DataWorker.h"

DataWorker::DataWorker()
{
    buffer_size = 0;
    redis_handler.connect_to_redis();
    redis_handler.select_database(REDIS_RX_DB);
}

DataWorker::~DataWorker()
{
}

void DataWorker::start_working(std::string &data, int &buffer_size)
{
    this->buffer_size = buffer_size;
    deserializer.deserialize_packet(data);

    channel_id = deserializer.get_channel_id();
    file_id = deserializer.get_file_id();
    packet_id = deserializer.get_packet_id();
    raw_data = deserializer.get_raw_data();

    inspect_packet_case();
}

void DataWorker::inspect_packet_case()
{
    if (redis_handler.file_exists(channel_id, file_id))
    {
        handle_packet();
    }

    else
    {
        construct_untracked_file();
    }
}

void DataWorker::handle_packet()
{
    std::string path = std::string(FILES_DIR) + redis_handler.get_file_path(channel_id, file_id);
    int file_size = redis_handler.get_file_size(channel_id, file_id);
    int offset = calculate_file_offset(file_size);

    DirectoryOrganizer::produce_structure(path);

    stream.create_file(path);
    stream.close_file();
    stream.set_file(path);

    stream.write_to_file(raw_data, offset);
    stream.close_file();
}

void DataWorker::construct_untracked_file()
{
    FileStream untracked_stream;

    std::string file_name = std::to_string(channel_id) + std::to_string(file_id);
    untracked_stream.create_file(std::string(UNTRACKED_DIR) + file_name);

    std::string packet_metadata = std::to_string(packet_id) + "," + std::to_string(raw_data.length()) + "\n";

    untracked_stream.append_to_file(packet_metadata);
    untracked_stream.append_to_file(raw_data);
    untracked_stream.append_to_file("\n");

    untracked_stream.close_file();
}

int DataWorker::calculate_file_offset(const int &file_size)
{
    int offset = packet_id * (buffer_size - OVERHEAD_SIZE);

    if (offset > file_size)
    {
        offset = file_size - (offset - file_size);
    }

    return offset;
}