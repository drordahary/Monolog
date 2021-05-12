#pragma once

#include "essential.h"
#include "Settings.h"
#include "RedisHandler.h"
#include "DataWorkerPool.h"
#include "DirectoryReader.h"
#include "DirectoryOrganizer.h"

#define REDIS_TX_DB 0

class MetadataWorker
{
private:
    int channel_id;
    channel_configurations configurations;
    DataWorkerPool *data_pool;
    DirectoryReader dir_reader;
    RedisHandler redis_handler;

public:
    MetadataWorker(channel_configurations configurations, int channel_id);
    ~MetadataWorker();

    void enable_pool_usage(DataWorkerPool *data_pool);
    void start_working();

    void save_metadata_to_redis(int &file_id, std::string &path, int &file_size);
};