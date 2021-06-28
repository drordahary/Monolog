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
    channel_id = hex_to_int(data.substr(0, HEX_LENGTH));
    file_id = hex_to_int(data.substr(HEX_LENGTH, HEX_LENGTH));
    packet_id = hex_to_int(data.substr(HEX_LENGTH * 2, HEX_LENGTH));
}

int Deserializer::hex_to_int(std::string hexadecimal)
{
    return std::stoul(hexadecimal, nullptr, BASE_16);
}

int Deserializer::get_packet_id()
{
    return packet_id;
}

int Deserializer::get_file_id()
{
    return file_id;
}

int Deserializer::get_channel_id()
{
    return channel_id;
}