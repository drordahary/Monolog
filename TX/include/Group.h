#pragma once

#include "essential.h"
#include "MetadataWorker.h"
#include "DataWorkerPool.h"
#include "Settings.h"

class Group
{
private:
    int channel_id;
    channel_configurations configurations;

    MetadataWorker *metadata_worker;
    DataWorkerPool *data_worker_pool;

    boost::thread *metadata_thread;

public:
    Group(channel_configurations configurations, int channel_id);
    ~Group();

    void set_all_workers();
    void set_metadata_worker();
    void set_data_pool();
    void start_transmitting();
    void terminate_pool();
};