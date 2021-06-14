#include "../include/Ports.h"

Ports::Ports()
{
    redis_handler.connect_to_redis();
    redis_handler.select_database(REDIS_DB_ID);
}

Ports::~Ports()
{
    ports.clear();
}

void Ports::set_configurations(const std::map<int, channel_configurations> &channels_configurations)
{
    this->channels_configurations = channels_configurations;
}

void Ports::set_all_ports()
{
    set_metadata_ports();
    set_data_ports();
}

void Ports::set_metadata_ports()
{
    int counter = 0;
    int port_offset;

    for (auto const &configuration : channels_configurations)
    {
        port_offset = configuration.second.port_offset;
        ports.insert({port_offset, std::vector<unsigned int>()});
    }
}

void Ports::set_data_ports()
{
    int port_offset;
    int ports_per_channel;

    for (auto const &configuration : channels_configurations)
    {
        port_offset = configuration.second.port_offset;
        ports_per_channel = configuration.second.ports_per_channel;

        for (int i = port_offset; i < port_offset + ports_per_channel; i++)
        {
            ports[port_offset].push_back(i + 1);
        }
    }
}

unsigned int Ports::get_metadata_port(const int &channel_id)
{
    return channels_configurations[channel_id].port_offset;
}

std::vector<unsigned int> &Ports::get_data_ports(const int &channel_id)
{
    return ports[channels_configurations[channel_id].port_offset];
}