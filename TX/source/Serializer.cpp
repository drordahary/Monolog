#include "../include/Serializer.h"

Serializer::Serializer()
{
    packet_id = 0;
}

Serializer::~Serializer()
{
}

std::string Serializer::serialize_packet(std::string &data, int &file_id, int &channel_id)
{
    std::string serialized_string = int_to_hex(channel_id);
    serialized_string += int_to_hex(file_id);
    serialized_string += int_to_hex(packet_id);

    packet_id++;
    return serialized_string + data;
}

std::string Serializer::int_to_hex(int &id)
{
    std::stringstream hexadecimal;

	hexadecimal << "0x" << std::setfill('0') << std::setw(sizeof(int) * 2) << std::hex << id;
	return hexadecimal.str();
}

void Serializer::reset_packet_id()
{
    packet_id = 0;
}