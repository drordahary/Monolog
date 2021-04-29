#pragma once

#include "essential.h"
#include "Settings.h"

typedef struct socket_settings
{
    int fd;
    struct sockaddr_in server_address;
    struct sockaddr_in client_address;
    socklen_t socket_len;
    int receive_len;
    int buffer_size;
    std::vector<unsigned char> buffer;

} socket_settings;

class Receivers
{
private:
    socket_settings metadata_socket;
    std::vector<socket_settings> data_sockets;
    int max_fd;

    fd_set sockets;
    fd_set copy;

    channel_configurations configurations;

public:
    Receivers(channel_configurations configurations);
    ~Receivers();

    void set_sockets(const int &metadata_port, const std::vector<int> &data_ports);
    socket_settings set_single_socket(const int &port);
    void set_metadata_socket(const int &metadata_port);
    void set_data_sockets(const std::vector<int> &data_ports);

    void start_receiving();
    void handle_readables();

    void handle_metadata();
    void handle_data(socket_settings &data_socket);
};