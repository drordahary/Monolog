#include "../include/TimeWorker.h"

TimeWorker::TimeWorker(std::string ip, unsigned int port) : ntp_client(IL_NTP_IP, NTP_PORT),
                                                            Transmitter(ip, port, TIME_BUFFER_SIZE)
{
}

TimeWorker::~TimeWorker()
{
}

void TimeWorker::start_updating()
{
    while (!exiting)
    {
        current_time = std::to_string(ntp_client.request_time());
        strncpy(buffer, current_time.c_str(), TIME_BUFFER_SIZE);

        transmit_packet();

        std::this_thread::sleep_for(std::chrono::milliseconds(NTP_UPDATE_DELAY_MS));
    }
}