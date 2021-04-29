#include "../include/Group.h"

Group::Group(channel_configurations configurations, int channel_id) : receivers(configurations)
{
    this->channel_id = channel_id;
}

Group::~Group()
{
}

void Group::set_receivers(const int &metadata_port, const std::vector<int> &data_ports)
{
    receivers.set_sockets(metadata_port, data_ports);
    receivers.start_receiving();
}