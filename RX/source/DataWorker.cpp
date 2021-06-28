#include "../include/DataWorker.h"

DataWorker::DataWorker()
{
}

DataWorker::~DataWorker()
{
}

void DataWorker::start_working(std::string &data)
{
    deserializer.deserialize_packet(data);

    channel_id = deserializer.get_channel_id();
    file_id = deserializer.get_file_id();
    packet_id = deserializer.get_packet_id();

    slog_trace("%d, %d, %d", channel_id, file_id, packet_id);
}