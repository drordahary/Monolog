#pragma once

#include "essential.h"
#include "Settings.h"
#include "RedisHandler.h"
#include "DataWorkerPool.h"
#include "DirectoryReader.h"


#define REDIS_TX_DB 0

class MetadataWorker
{
private:
    int channel_id;
    channel_configurations configurations;
    DataWorkerPool *data_pool;
    DirectoryReader dir_reader;
    RedisHandler redis_handler;
    std::vector<std::string> fixed_paths;
    std::vector<std::string> paths;

public:
    MetadataWorker(channel_configurations configurations, int channel_id);
    ~MetadataWorker();

    void enable_pool_usage(DataWorkerPool *data_pool);
    void start_working();

    void handle_paths();
    int get_file_size(const std::string &path);

    void save_metadata_to_redis(int &file_id, std::string &path, int &file_size);
};