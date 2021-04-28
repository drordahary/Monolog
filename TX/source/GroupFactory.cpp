#include "../include/GroupFactory.h"

Group *GroupFactory::make_group(channel_configurations configurations)
{
    return new Group(configurations);
}