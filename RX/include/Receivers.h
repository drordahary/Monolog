#pragma once

#include "essential.h"
#include "Settings.h"
#include "DataWorkerPool.h"
#include "MetadataWorkerPool.h"

typedef struct socket_settings
{
    int fd;
    struct sockaddr_in server_address;
    struct sockaddr_in client_address;
    socklen_t socket_len;
    int receive_len;

} socket_settings;

class Receivers
{
private:
    socket_settings metadata_socket;
    std::vector<socket_settings> data_sockets;
    int max_fd;

    int buffer_size;
    char *buffer;

    fd_set sockets;
    fd_set copy;

    channel_configurations configurations;

    DataWorkerPool *data_pool;
    MetadataWorkerPool *metadata_pool;

    int pfd[2];

public:
    Receivers(channel_configurations configurations);
    ~Receivers();

    void set_pools(DataWorkerPool *data_pool, MetadataWorkerPool *metadata_pool);
    void set_sockets(const int &metadata_port, const std::vector<unsigned int> &data_ports);
    socket_settings set_single_socket(const int &port);
    void set_metadata_socket(const int &metadata_port);
    void set_data_sockets(const std::vector<unsigned int> &data_ports);

    void start_receiving();
    void handle_readables();

    void handle_metadata();
    void handle_data(socket_settings &data_socket);

    void set_pipe();
    void self_pipe();
};