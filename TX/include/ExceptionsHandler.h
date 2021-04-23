#pragma once

#include "essential.h"

class ExceptionsHandler
{
public:
    static std::string bad_redis_connect();
    static std::string bad_redis_reply();
};