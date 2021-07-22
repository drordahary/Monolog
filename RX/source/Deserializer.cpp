#include "../include/Deserializer.h"

Deserializer::Deserializer()
{
    packet_id = -1;
    file_id = -1;
    channel_id = -1;
}

Deserializer::~Deserializer()
{
}

void Deserializer::deserialize_packet(std::string &data)
{
    channel_id = Deserializer::hex_to_int(data.substr(0, HEX_LENGTH));
    file_id = Deserializer::hex_to_int(data.substr(HEX_LENGTH, HEX_LENGTH));
    packet_id = Deserializer::hex_to_int(data.substr(HEX_LENGTH * 2, HEX_LENGTH));
    raw_data = data.substr(HEX_LENGTH * 3);
}

int Deserializer::hex_to_int(std::string hexadecimal)
{
    return std::stoul(hexadecimal, nullptr, BASE_16);
}

int Deserializer::get_packet_id() const
{
    return packet_id;
}

int Deserializer::get_file_id() const
{
    return file_id;
}

int Deserializer::get_channel_id() const
{
    return channel_id;
}

const std::string &Deserializer::get_raw_data() const
{
    return raw_data;
}