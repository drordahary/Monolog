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

    void save_metadata(std::string &key, std::pair<std::string, std::string> &field);
    bool key_hash_exists(const std::string &key);
    int get_last_file_id(const std::string &key);
    void handle_new_channel_hash(const std::string &key);

    void increment_file_id(const std::string &key);

    std::string get_ntp_ip();
    int get_ntp_port();
};