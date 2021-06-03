#pragma once

#include "essential.h"
#include "Settings.h"
#include "FileStream.h"

#define OVERHEAD_SIZE 30

class DataWorker
{
private:
    channel_configurations configurations;
    FileStream file;

public:
    DataWorker(channel_configurations configurations);
    ~DataWorker();

    void start_transmitting(const std::string &file_path);
    int calculate_amount_to_read(const int &size, const int &completed);
};