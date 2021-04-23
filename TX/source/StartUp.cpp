#include "../include/StartUp.h"

StartUp::StartUp()
{
    settings.set_logger();
    settings.fetch_configurations();
}

StartUp::~StartUp()
{
}