#pragma once

#include "essential.h"
#include "Group.h"
#include "Settings.h"

class GroupFactory
{
public:
    static Group *make_group(channel_configurations configurations, int channel_id);
};