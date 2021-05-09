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
    std::vector<channel_configurations> channels_configurations;
    channels_configurations = settings.get_channels_configurations();

    for (channel_configurations configurations : channels_configurations)
    {
        groups.push_back(GroupFactory::make_group(configurations));
        groups.back()->set_all_workers();
    }
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