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
    static int hex_to_int(std::string hexadecimal);

    int get_packet_id() const;
    int get_file_id() const;
    int get_channel_id() const;
    const std::string &get_raw_data() const;
};