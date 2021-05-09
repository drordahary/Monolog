#pragma once

#include "essential.h"
#include "Settings.h"
#include "DataWorkerPool.h"
#include "DirectoryReader.h"

class MetadataWorker
{
private:
    channel_configurations configurations;
    DataWorkerPool *data_pool;
    DirectoryReader dir_reader;

public:
    MetadataWorker(channel_configurations configurations);
    ~MetadataWorker();

    void enable_pool_usage(DataWorkerPool *data_pool);
    void start_working();
};