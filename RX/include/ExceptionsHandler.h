#pragma once

#include "essential.h"

class ExceptionsHandler
{
public:
    static std::string bad_redis_connect();
    static std::string bad_redis_reply();
    static std::string bad_socket_creation();
    static std::string bad_bind();
    static std::string bad_select();
};