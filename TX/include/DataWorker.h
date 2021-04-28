#pragma once

#include "essential.h"
#include "Settings.h"

class DataWorker
{
private:
    channel_configurations configurations;

public:
    DataWorker(channel_configurations configurations);
    ~DataWorker();
};