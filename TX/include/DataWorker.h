#pragma once

#include "essential.h"
#include "Settings.h"
#include "FileStream.h"
#include "Transmitter.h"
#include "Serializer.h"

#define OVERHEAD_SIZE 30

class DataWorker : public Transmitter
{
private:
    channel_configurations configurations;
    FileStream file;
    Serializer serializer;

public:
    DataWorker(channel_configurations configurations, unsigned int port);
    ~DataWorker();

    void start_transmitting(const std::string &file_path, int &file_id, int &channel_id);
    int calculate_amount_to_read(const int &size, const int &completed);
    void organize_data(const std::string &data);
    void move_to_archive(const std::string &path);
};