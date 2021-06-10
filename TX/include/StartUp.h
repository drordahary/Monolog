#pragma once

#include "essential.h"
#include "Settings.h"
#include "Group.h"
#include "GroupFactory.h"
#include "Ports.h"

class StartUp
{
private:
    Settings settings;
    Ports ports;
    std::vector<Group *> groups;

public:
    StartUp();
    ~StartUp();

    void set_infrastructure();
    void set_groups();
    void set_ports();

    void initiate_transmitters();

    void terminate_now();
};