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

    std::vector<int> get_channels_ids();
    std::string get_configuration(const int &channel_id, const std::string &field);

    void save_metadata(const std::string &key, const std::pair<std::string, std::string> &field);

    bool file_exists(const int &channel_id, const int &file_id);
    std::string get_file_path(const int &channel_id, const int &file_id);
    int get_file_size(const int &channel_id, const int &file_id);

    int get_ntp_port();
};