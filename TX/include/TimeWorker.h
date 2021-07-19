#pragma once

#include "essential.h"
#include "Transmitter.h"
#include "../ntp/client.hpp"

#define NTP_UPDATE_DELAY_MS 5000
#define TIME_BUFFER_SIZE 20
#define IL_NTP_IP "162.159.200.1"
#define NTP_PORT 123

class TimeWorker : public Transmitter
{
private:
    NTPClient ntp_client;
    std::string current_time;

public:
    TimeWorker(std::string ip, unsigned int port);
    ~TimeWorker();

    void start_updating();
};