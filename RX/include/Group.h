#pragma once

#include "essential.h"
#include "Receivers.h"

class Group
{
private:
    Receivers receivers;
    int channel_id;
    int metadata_port;
    std::vector<int> data_ports;

public:
    Group(channel_configurations configurations, int channel_id);
    ~Group();

    void set_receivers(const int &metadata_port, const std::vector<int> &data_ports);
};