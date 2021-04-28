#pragma once

#include "essential.h"
#include "Settings.h"

class MetadataWorker
{
private:
    channel_configurations configurations;

public:
    MetadataWorker(channel_configurations configurations);
    ~MetadataWorker();
};