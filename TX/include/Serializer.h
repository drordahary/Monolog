#pragma once

#include "essential.h"

class Serializer
{
private:
    int packet_id;

public:
    Serializer();
    ~Serializer();

    std::string serialize_packet(std::string &data, int &file_id, int &channel_id);
    std::string int_to_hex(int &id);
    void reset_packet_id();
};