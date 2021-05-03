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
    ports.set_offset_port(settings.get_channels_configurations()[0].port_offset);
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
    std::vector<channel_configurations> channels_configurations;
    channels_configurations = settings.get_channels_configurations();

    int current_channel_id = 0;

    for (channel_configurations configurations : channels_configurations)
    {
        groups.push_back(GroupFactory::make_group(configurations, current_channel_id));
        groups.back()->set_group_signal_handler(sigbreak);
        groups.back()->set_pools(data_pool, metadata_pool);
        groups.back()->set_receivers(ports.get_metadata_port(current_channel_id), ports.get_data_ports(current_channel_id));
        current_channel_id++;
    }
}

void StartUp::set_signal_handler(struct sigaction &sigbreak)
{
    this->sigbreak = sigbreak;
}

void StartUp::terminate_now()
{
    data_pool->terminate_pool();
    metadata_pool->terminate_pool();
}