#pragma once

#include "essential.h"
#include "RedisHandler.h"

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

public:
    MetadataWorker();
    ~MetadataWorker();

    void start_working(std::string data);
    void organize_metadata(std::string &metadata);
    void save_metadata_to_redis();
};