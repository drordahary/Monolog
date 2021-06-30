#pragma once

#include "essential.h"

#define HEX_LENGTH 10
#define BASE_16 16

class Deserializer
{
private:
    int packet_id;
    int file_id;
    int channel_id;
    std::string raw_data;

public:
    Deserializer();
    ~Deserializer();

    void deserialize_packet(std::string &data);
    int hex_to_int(std::string hexadecimal);

    int get_packet_id();
    int get_file_id();
    int get_channel_id();
    std::string &get_raw_data();
};