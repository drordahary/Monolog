#include "../include/ExceptionsHandler.h"

std::string ExceptionsHandler::bad_redis_connect()
{
    return "Cannot connect to Redis";
}

std::string ExceptionsHandler::bad_redis_reply()
{
    return "Cannot read from Redis";
}

std::string ExceptionsHandler::bad_socket_creation()
{
    return "Cannot create socket";
}

std::string ExceptionsHandler::bad_bind()
{
    return "Bind failed";
}

std::string ExceptionsHandler::bad_select()
{
    return "Select failed";
}

std::string ExceptionsHandler::bad_pipe()
{
    return "Pipe failed";
}

std::string ExceptionsHandler::bad_stream_open()
{
    return "Cannot open stream";
}