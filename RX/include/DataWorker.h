#pragma once

#include "essential.h"
#include "Deserializer.h"
#include "RedisHandler.h"
#include "FileStream.h"

#define OVERHEAD_SIZE 30

class DataWorker
{
private:
    Deserializer deserializer;
    RedisHandler redis_handler;
    FileStream stream;
    int buffer_size;

    std::string raw_data;
    int packet_id;
    int file_id;
    int channel_id;

public:
    DataWorker();
    ~DataWorker();

    void start_working(std::string &data, int &buffer_size);
    void inspect_packet_case();
    void handle_packet();
    int calculate_file_offset(const int &file_size);
};