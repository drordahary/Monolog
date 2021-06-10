#pragma once

#include "essential.h"
#include "RedisHandler.h"
#include "Settings.h"

#define MAX_PORTS_PER_CHANNEL 10

class Ports
{
private:
    RedisHandler redis_handler;
    std::vector<channel_configurations> channels_configurations;

    std::map<unsigned int, std::vector<unsigned int>> ports;
    int channels_count;
    int offset_port;

public:
    Ports();
    ~Ports();

    void set_configurations(const std::vector<channel_configurations> &channels_configurations);
    void set_offset_port(const int &offset_port);

    void set_all_ports();
    void set_metadata_ports();
    void set_data_ports();

    unsigned int get_metadata_port(const int &channel_id);
    std::vector<unsigned int> &get_data_ports(const int &channel_id);
};