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
}

void StartUp::set_infrastructure()
{
    settings.set_logger();
    settings.set_redis();
    settings.fetch_configurations();
}

void StartUp::set_groups()
{
    std::map<int, channel_configurations> channels_configurations;
    channels_configurations = settings.get_channels_configurations();
    int channel_id;

    for (auto const &configurations : channels_configurations)
    {
        channel_id = configurations.first;
        groups.push_back(GroupFactory::make_group(configurations.second, channel_id));
        groups.back()->set_all_workers(ports.get_metadata_port(channel_id), ports.get_data_ports(channel_id));
    }
}

void StartUp::set_ports()
{
    ports.set_configurations(settings.get_channels_configurations());
    ports.set_all_ports();
}

void StartUp::initiate_transmitters()
{
    for (Group *group : groups)
    {
        group->start_transmitting();
    }
}

void StartUp::terminate_now()
{
    for (Group *group : groups)
    {
        group->terminate_pool();
    }
}