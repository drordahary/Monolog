#pragma once

#include "essential.h"
#include "Receivers.h"
#include "DataWorkerPool.h"
#include "MetadataWorkerPool.h"

class Group
{
private:
    Receivers receivers;
    int channel_id;
    boost::thread *receivers_thread;

public:
    Group(channel_configurations configurations, int channel_id);
    ~Group();

    void set_receivers(const int &metadata_port, const std::vector<int> &data_ports);
    void set_pools(DataWorkerPool *data_pool, MetadataWorkerPool *metadata_pool);

    void terminate_receivers();
};