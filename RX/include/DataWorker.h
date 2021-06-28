#pragma once

#include "essential.h"
#include "Deserializer.h"

#define OVERHEAD_SIZE 30

class DataWorker
{
private:
    Deserializer deserializer;
    int packet_id;
    int file_id;
    int channel_id;

public:
    DataWorker();
    ~DataWorker();

    void start_working(std::string &data);
};