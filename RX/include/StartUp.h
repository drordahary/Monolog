#pragma once

#include "essential.h"
#include "Settings.h"

class StartUp
{
private:
    Settings settings;

public:
    StartUp();
    ~StartUp();

    void set_infrastructure();
};