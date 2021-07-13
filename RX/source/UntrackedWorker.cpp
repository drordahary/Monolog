#include "../include/UntrackedWorker.h"

UntrackedWorker::UntrackedWorker()
{
}

UntrackedWorker::~UntrackedWorker()
{
}

void UntrackedWorker::start_working(std::string &data)
{
    organize_data(data);
    restore_file();
}

void UntrackedWorker::organize_data(std::string &data)
{
    std::stringstream data_stream(data);
    std::vector<std::string> result;
    std::string segment;

    while (std::getline(data_stream, segment, ','))
    {
        result.push_back(segment);
    }

    file.channel_id = std::stoi(result[0]);
    file.file_id = std::stoi(result[1]);
    file.file_size = std::stoi(result[2]);
    file.buffer_size = std::stoi(result[3]);
    file.path = result[4];

    slog_trace("%d %d %d %d", file.channel_id, file.file_id, file.file_size, file.buffer_size);
    slog_trace("PATH: %s", file.path.c_str());
}

void UntrackedWorker::restore_file()
{
    std::string from_path = std::string(UNTRACKED_DIR) + std::to_string(file.channel_id);
    from_path += std::to_string(file.file_id);

    FileStream from_stream;
    from_stream.create_file(from_path);
    from_stream.close_file();
    from_stream.set_file(from_path);

    FileStream to_stream;
    to_stream.create_file(file.path);
    to_stream.close_file();
    to_stream.set_file(file.path);

    int offset = 0;
    int amount_to_read = 0;
    int from_file_size = from_stream.get_size();

    int packet_id = -1;
    std::string metadata;
    std::string data;

    size_t len = 0;
    int bytes_read = 0;
    char *line = NULL;


    while (offset < from_file_size)
    {
        bytes_read = getline(&line, &len, from_stream.get_file());
        metadata = line;

        packet_id = std::stoi(metadata.substr(0, metadata.find(",")));
        amount_to_read = std::stoi(metadata.substr(metadata.find(",") + 1)) + 1;

        offset += bytes_read;

        from_stream.set_read_buffer(amount_to_read);
        data = from_stream.read_file(amount_to_read);
        if (data.length() > 0)
        {
            data.pop_back();
        }

        offset += amount_to_read;
        to_stream.write_to_file(data, calculate_file_offset(file.file_size, packet_id, file.buffer_size));
    }

    from_stream.close_file();
    to_stream.close_file();

    free(line);
    line = NULL;
}