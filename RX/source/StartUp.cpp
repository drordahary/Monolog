#include "../include/StartUp.h"

StartUp::StartUp()
{
}

StartUp::~StartUp()
{
}

void StartUp::set_infrastructure()
{
    settings.set_logger();
    settings.set_redis();
    settings.fetch_configurations();
}