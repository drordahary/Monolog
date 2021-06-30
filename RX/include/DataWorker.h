#pragma once

#include "essential.h"
#include "Deserializer.h"
#include "RedisHandler.h"

#define OVERHEAD_SIZE 30

class DataWorker
{
private:
    Deserializer deserializer;
    RedisHandler redis_handler;

    std::string raw_data;
    int packet_id;
    int file_id;
    int channel_id;

public:
    DataWorker();
    ~DataWorker();

    void start_working(std::string &data);
    void inspect_packet_case();
    void handle_packet();
};