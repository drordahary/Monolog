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
    channel_configurations configurations;
    DataWorkerPool *data_pool;
    DirectoryReader dir_reader;
    RedisHandler redis_handler;

public:
    MetadataWorker(channel_configurations configurations);
    ~MetadataWorker();

    void enable_pool_usage(DataWorkerPool *data_pool);
    void start_working();
};