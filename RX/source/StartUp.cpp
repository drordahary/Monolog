#include "../include/StartUp.h"

StartUp::StartUp()
{
}

StartUp::~StartUp()
{
    for (Group *group : groups)
    {
        delete group;
    }

    delete data_pool;
    delete metadata_pool;
}

void StartUp::set_infrastructure()
{
    settings.set_logger();
    settings.set_redis();
    settings.fetch_configurations();
}

void StartUp::set_ports()
{
    ports.set_configurations(settings.get_channels_configurations());
    ports.set_all_ports();
}

void StartUp::set_pools()
{
    data_pool = new DataWorkerPool();
    data_pool->set_workers(pool_settings::data_pool_size);

    metadata_pool = new MetadataWorkerPool();
    metadata_pool->set_workers(pool_settings::metadata_pool_size);
}

void StartUp::set_groups()
{
    std::map<int, channel_configurations> channels_configurations;
    channels_configurations = settings.get_channels_configurations();
    int channel_id;

    for (auto &configurations : channels_configurations)
    {
        channel_id = configurations.first;
        groups.push_back(GroupFactory::make_group(configurations.second, channel_id));
        groups.back()->set_pools(data_pool, metadata_pool);
        groups.back()->set_receivers(ports.get_metadata_port(channel_id), ports.get_data_ports(channel_id));
    }
}

void StartUp::terminate_now()
{
    for (Group *group : groups)
    {
        group->terminate_receivers();
    }

    data_pool->terminate_pool();
    metadata_pool->terminate_pool();
}