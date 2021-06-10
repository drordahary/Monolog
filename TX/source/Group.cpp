#include "../include/Group.h"

Group::Group(channel_configurations configurations, int channel_id)
{
    this->configurations = configurations;
    this->channel_id = channel_id;
}

Group::~Group()
{
    metadata_thread->join();
    delete metadata_thread;
    delete metadata_worker;
    delete data_worker_pool;
}

void Group::set_all_workers(const unsigned int &metadata_port, const std::vector<unsigned int> &data_ports)
{
    set_metadata_worker(metadata_port);
    set_data_pool(data_ports);
}

void Group::set_metadata_worker(const unsigned int &port)
{
    metadata_worker = new MetadataWorker(configurations, channel_id, port);
}

void Group::set_data_pool(const std::vector<unsigned int> &ports)
{
    data_worker_pool = new DataWorkerPool(configurations.ports_per_channel);
    data_worker_pool->set_workers(ports, configurations);
}

void Group::start_transmitting()
{
    metadata_worker->enable_pool_usage(data_worker_pool);
    metadata_thread = new boost::thread(boost::bind(&MetadataWorker::start_working, metadata_worker));
}

void Group::terminate_pool()
{
    data_worker_pool->terminate_pool();
}