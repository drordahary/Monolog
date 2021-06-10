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

    void set_all_workers(const unsigned int &metadata_port, const std::vector<unsigned int> &data_ports);
    void set_metadata_worker(const unsigned int &port);
    void set_data_pool(const std::vector<unsigned int> &ports);
    void start_transmitting();
    void terminate_pool();
};