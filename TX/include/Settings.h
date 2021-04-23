#pragma once

#include "essential.h"
#include "RedisHandler.h"

#define REDIS_DB_ID 4

typedef struct channel_configurations
{
    std::string source_ip;
    std::string destination_ip;
    std::string channel_directory;
    int port_offset;
    int ports_per_channel;
    int times_to_send;
    int buffer_size;

} channel_configurations;

class Settings
{
private:
    RedisHandler redis_handler;
    std::vector<channel_configurations> channels;

public:
    Settings();
    ~Settings();

    void set_logger();
    void set_redis();
    void fetch_configurations();
    void organize_results(const std::vector<std::string> &results);
};