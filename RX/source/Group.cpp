#include "../include/Group.h"

Group::Group(channel_configurations configurations, int channel_id) : receivers(configurations)
{
    this->channel_id = channel_id;
}

Group::~Group()
{
    receivers_thread->join();
    delete receivers_thread;
}

void Group::set_receivers(const int &metadata_port, const std::vector<int> &data_ports)
{
    receivers.set_sockets(metadata_port, data_ports);
    receivers_thread = new boost::thread(boost::bind(&Receivers::start_receiving, &receivers));
}

void Group::set_pools(DataWorkerPool *data_pool, MetadataWorkerPool *metadata_pool)
{
    receivers.set_pools(data_pool, metadata_pool);
}