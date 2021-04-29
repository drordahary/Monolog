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
    std::vector<Group *> groups;
    Ports ports;

public:
    StartUp();
    ~StartUp();

    void set_infrastructure();
    void set_ports();
    void set_groups();
};