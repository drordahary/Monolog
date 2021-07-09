#pragma once

#include "essential.h"
#include "FileStream.h"
#include "DataWorker.h"

typedef struct untracked_file
{
    int file_id;
    int file_size;
    int buffer_size;
    std::string path;

} untracked_file;

class UntrackedWorker
{
private:
    int channel_id;
    struct event_base *base;
    redisAsyncContext *context;

public:
    UntrackedWorker(int channel_id);
    ~UntrackedWorker();

    void start_redis_async_connect();
    void subscribe_to_channel();
};

void handle_publishment(redisAsyncContext *ac, void *reply, void *privdata);
untracked_file organize_data(std::string &data);
void restore_file(untracked_file &file, const int &channel_id);