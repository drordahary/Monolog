#include "../include/ExceptionsHandler.h"

std::string ExceptionsHandler::bad_redis_connect()
{
    return "Cannot connect to Redis";
}

std::string ExceptionsHandler::bad_redis_reply()
{
    return "Cannot read from Redis";
}

std::string ExceptionsHandler::bad_file_move()
{
    return "Cannot move file";
}