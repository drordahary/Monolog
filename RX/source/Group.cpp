#include "../include/Group.h"

Group::Group(channel_configurations configurations, int channel_id) : receivers(configurations)
{
    this->channel_id = channel_id;
}

Group::~Group()
{
    receivers_thread->join();
    delete receivers_thread;
}

void Group::set_receivers(const int &metadata_port, const std::vector<int> &data_ports)
{
    receivers.set_sockets(metadata_port, data_ports);
    receivers.set_signal_handler(sigbreak);
    receivers_thread = new boost::thread(boost::bind(&Receivers::start_receiving, &receivers));
}

void Group::set_group_signal_handler(struct sigaction &sigbreak)
{
    this->sigbreak = sigbreak;
}