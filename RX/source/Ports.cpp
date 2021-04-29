#include "../include/Ports.h"

Ports::Ports()
{
    redis_handler.connect_to_redis();
    redis_handler.select_database(REDIS_DB_ID);
    channels_count = redis_handler.get_channels_count();
}

Ports::~Ports()
{
    ports.clear();
}

void Ports::set_configurations(const std::vector<channel_configurations> &channels_configurations)
{
    this->channels_configurations = channels_configurations;
}

void Ports::set_offset_port(const int &offset_port)
{
    this->offset_port = offset_port;
}

void Ports::set_all_ports()
{
    set_metadata_ports();
    set_data_ports();
}

void Ports::set_metadata_ports()
{
    for (int i = 0; i < channels_count; i++)
    {
        ports.insert({i + offset_port + 1, std::vector<int>()});
        ports[i + offset_port + 1].resize(channels_configurations[i].ports_per_channel);
    }
}

void Ports::set_data_ports()
{
    int multiplier = channels_count / MAX_PORTS_PER_CHANNEL + 1;

    for (int i = 0; i < channels_count; i++)
    {
        for (int j = 0; j < ports[i + offset_port + 1].size(); j++)
        {
            ports[i + offset_port + 1][j] = (offset_port + (multiplier * MAX_PORTS_PER_CHANNEL) + j);
        }

        multiplier++;
    }
}

int Ports::get_metadata_port(const int &channel_id)
{
    return offset_port + channel_id;
}

std::vector<int> &Ports::get_data_ports(const int &channel_id)
{
    return ports[channel_id + offset_port + 1];
}