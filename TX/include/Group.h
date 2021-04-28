#pragma once

#include "essential.h"
#include "MetadataWorker.h"
#include "DataWorkerPool.h"
#include "Settings.h"

class Group
{
private:
    channel_configurations configurations;

    MetadataWorker *metadata_worker;
    DataWorkerPool *data_worker_pool;

public:
    Group(channel_configurations configurations);
    ~Group();

    void set_all_workers();
    void set_metadata_worker();
    void set_data_pool();
    void terminate_pool();
};