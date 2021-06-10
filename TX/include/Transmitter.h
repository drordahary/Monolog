#pragma once

#include "essential.h"

typedef struct server_configurations
{
    std::string ip;
    unsigned int port;

} server_configurations;

typedef struct socket_settings
{
    int fd;
    struct sockaddr_in server_address;
    int socket_len;

} socket_settings;

class Transmitter
{
private:
    server_configurations configurations;
    socket_settings settings;

protected:
    char *buffer;
    int buffer_size;

public:
    Transmitter(std::string ip, unsigned int port, int buffer_size);
    virtual ~Transmitter();

    void set_socket();
    void transmitt_packet();
};