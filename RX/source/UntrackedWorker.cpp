#include "../include/UntrackedWorker.h"

UntrackedWorker::UntrackedWorker(int channel_id)
{
    this->channel_id = channel_id;
}

UntrackedWorker::~UntrackedWorker()
{
    redisAsyncDisconnect(context);
    event_base_free(base);
}

void UntrackedWorker::start_redis_async_connect()
{
    base = event_base_new();
    context = redisAsyncConnect("127.0.0.1", 6379);
}

void UntrackedWorker::subscribe_to_channel()
{
    std::string query = "subscribe channel" + std::to_string(channel_id);

    redisLibeventAttach(context, base);
    redisAsyncCommand(context, handle_publishment, (void *)(intptr_t)channel_id, query.c_str());
    event_base_dispatch(base);
}

void handle_publishment(redisAsyncContext *ac, void *reply, void *privdata)
{
    int channel_id = (intptr_t)channel_id;
    redisReply *r = (redisReply *)reply;
    std::string result;
    untracked_file file;

    if (reply == NULL)
    {
        throw(ExceptionsHandler::bad_redis_reply());
    }

    if (r->type == REDIS_REPLY_ARRAY && r->element[2]->type == REDIS_REPLY_STRING)
    {
        result = r->element[2]->str;
        file = organize_data(result);
        restore_file(file, channel_id);
    }
}

untracked_file organize_data(std::string &data)
{
    untracked_file file;

    std::stringstream data_stream(data);
    std::vector<std::string> result;
    std::string segment;

    while (std::getline(data_stream, segment, ','))
    {
        result.push_back(segment);
    }

    file.file_id = std::stoi(result[0]);
    file.file_size = std::stoi(result[1]);
    file.buffer_size = std::stoi(result[2]);
    file.path = result[3];

    return file;
}

void restore_file(untracked_file &file, const int &channel_id)
{
    std::string from_path = std::string(UNTRACKED_DIR) + std::to_string(channel_id);
    from_path += std::to_string(file.file_id);

    FileStream from_stream;
    from_stream.create_file(from_path);

    FileStream to_stream;
    to_stream.set_file(file.path);

    int offset = 0;
    int amount_to_read = 0;

    int packet_id = -1;
    std::string metadata;
    std::string data;

    size_t len = 0;
    int bytes_read = 0;
    char *line = NULL;

    while (offset < file.file_size)
    {
        bytes_read = getline(&line, &len, from_stream.get_file());
        metadata = line;

        packet_id = std::stoi(metadata.substr(0, metadata.find(",")));
        amount_to_read = std::stoi(metadata.substr(metadata.find(",") + 1));

        offset += bytes_read;
        from_stream.read_file(data, offset, amount_to_read);
        offset += amount_to_read;

        to_stream.write_to_file(data, calculate_file_offset(file.file_size, packet_id, file.buffer_size));
    }

    from_stream.close_file();
    to_stream.close_file();
}