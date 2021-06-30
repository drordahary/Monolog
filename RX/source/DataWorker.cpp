#include "../include/DataWorker.h"

DataWorker::DataWorker()
{
    redis_handler.connect_to_redis();
    redis_handler.select_database(REDIS_RX_DB);
}

DataWorker::~DataWorker()
{
}

void DataWorker::start_working(std::string &data)
{
    deserializer.deserialize_packet(data);

    channel_id = deserializer.get_channel_id();
    file_id = deserializer.get_file_id();
    packet_id = deserializer.get_packet_id();
    raw_data = deserializer.get_raw_data();
}

void DataWorker::inspect_packet_case()
{
    if (redis_handler.file_exists(channel_id, file_id))
    {
        handle_packet();
    }
}

void DataWorker::handle_packet()
{
}