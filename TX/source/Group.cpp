#include "../include/Group.h"

Group::Group(channel_configurations configurations)
{
    this->configurations = configurations;
}

Group::~Group()
{
    delete metadata_worker;
    delete data_worker_pool;
}

void Group::set_all_workers()
{
    set_metadata_worker();
    set_data_pool();
}

void Group::set_metadata_worker()
{
    metadata_worker = new MetadataWorker(configurations);
}

void Group::set_data_pool()
{
    data_worker_pool = new DataWorkerPool();
    data_worker_pool->set_workers(configurations.ports_per_channel, configurations);
}

void Group::start_transmitting()
{
    metadata_worker->enable_pool_usage(data_worker_pool);
    metadata_worker->start_working();
}

void Group::terminate_pool()
{
    data_worker_pool->terminate_pool();
}