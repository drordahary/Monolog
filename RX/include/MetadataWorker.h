#pragma once

#include "essential.h"
#include "RedisHandler.h"
#include "UntrackedWorkerPool.h"

typedef struct metadata
{
    int channel_id;
    int file_id;
    std::string path;
    int file_size;

} metadata;

class MetadataWorker
{
private:
    RedisHandler redis_handler;
    metadata current_metadata;
    UntrackedWorkerPool *untracked_pool;

public:
    MetadataWorker(UntrackedWorkerPool *untracked_pool);
    ~MetadataWorker();

    void start_working(std::string data, const int &buffer_size);
    void organize_metadata(std::string &metadata);
    void save_metadata_to_redis();

    bool untracked_file_exists(const std::string &path);
};