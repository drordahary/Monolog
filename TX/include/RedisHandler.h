#pragma once

#include "essential.h"

namespace redis_settings
{
    const std::string ip = "127.0.0.1";
    const int port = 6379;
}

class RedisHandler
{
private:
    redisContext *context;
    redisReply *reply;
    std::string query;

public:
    RedisHandler();
    ~RedisHandler();

    void connect_to_redis();
    void select_database(const int &database_id);
    int get_channels_count();
    std::string get_configuration(const int &channel_id, const std::string &field);
};