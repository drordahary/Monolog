#pragma once

#include "essential.h"
#include "Settings.h"
#include "Group.h"
#include "GroupFactory.h"

class StartUp
{
private:
    Settings settings;
    std::vector<Group *> groups;

public:
    StartUp();
    ~StartUp();

    void set_infrastructure();
    void set_groups();

    void terminate_now();
};