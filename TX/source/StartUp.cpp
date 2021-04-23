#include "../include/StartUp.h"

StartUp::StartUp()
{
    settings.set_logger();
    settings.set_redis();
    settings.fetch_configurations();
}

StartUp::~StartUp()
{
}