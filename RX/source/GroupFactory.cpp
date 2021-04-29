#include "../include/GroupFactory.h"

Group *GroupFactory::make_group(channel_configurations configurations, int channel_id)
{
    return new Group(configurations, channel_id);
}