#pragma once

#include "essential.h"
#include "Settings.h"
#include "Group.h"
#include "GroupFactory.h"
#include "Ports.h"
#include "TimeWorker.h"

class StartUp
{
private:
    Settings settings;
    Ports ports;
    std::vector<Group *> groups;

    RedisHandler redis_handler;
    TimeWorker *time_worker;
    boost::thread *ntp_thread;

public:
    StartUp();
    ~StartUp();

    void set_infrastructure();
    void set_groups();
    void set_ports();

    void initiate_transmitters();

    void terminate_now();
};