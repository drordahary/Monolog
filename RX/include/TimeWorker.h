#pragma once

#include "essential.h"
#include "Receivers.h"

#define TIME_BUFFER_SIZE 20

class TimeWorker
{
private:
    std::string current_time;
    std::string system_command;
    socket_settings settings;
    char *buffer;

    fd_set sockets;
    fd_set copy;
    int max_fd;
    int pfd[2];

public:
    TimeWorker(unsigned int port);
    ~TimeWorker();

    void set_socket(unsigned int port);

    void start_receiving();
    void handle_readable();

    void set_pipe();

    void self_pipe();
};