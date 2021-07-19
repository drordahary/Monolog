#include "../include/StartUp.h"

StartUp::StartUp()
{
    redis_handler.connect_to_redis();
    redis_handler.select_database(REDIS_DB_ID);
}

StartUp::~StartUp()
{
    for (Group *group : groups)
    {
        delete group;
    }

    ntp_thread->join();
    delete ntp_thread;
    delete time_worker;
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

    time_worker = new TimeWorker(redis_handler.get_ntp_ip(), redis_handler.get_ntp_port());
    ntp_thread = new boost::thread(boost::bind(&TimeWorker::start_updating, time_worker));
}

void StartUp::terminate_now()
{
    for (Group *group : groups)
    {
        group->terminate_pool();
    }
}