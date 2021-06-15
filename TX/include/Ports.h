#pragma once

#include "essential.h"
#include "RedisHandler.h"
#include "Settings.h"

class Ports
{
private:
    RedisHandler redis_handler;
    std::map<int, channel_configurations> channels_configurations;
    std::map<unsigned int, std::vector<unsigned int>> ports;

public:
    Ports();
    ~Ports();

    void set_configurations(const std::map<int, channel_configurations> &channels_configurations);

    void set_all_ports();
    void set_metadata_ports();
    void set_data_ports();

    unsigned int get_metadata_port(const int &channel_id);
    std::vector<unsigned int> &get_data_ports(const int &channel_id);
};