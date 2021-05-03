#include "../include/Receivers.h"

Receivers::Receivers(channel_configurations configurations)
{
    this->configurations = configurations;
    FD_ZERO(&sockets);
    max_fd = -1;
}

Receivers::~Receivers()
{
    close(metadata_socket.fd);

    for (int i = 0; i < data_sockets.size(); i++)
    {
        close(data_sockets[i].fd);
    }

    FD_ZERO(&sockets);
    FD_ZERO(&copy);

    data_sockets.clear();
}

void Receivers::set_signal_handler(struct sigaction &sigbreak)
{
    this->sigbreak = sigbreak;
}

void Receivers::set_sockets(const int &metadata_port, const std::vector<int> &data_ports)
{
    set_metadata_socket(metadata_port);
    set_data_sockets(data_ports);
}

socket_settings Receivers::set_single_socket(const int &port)
{
    socket_settings single_socket;

    single_socket.fd = socket(AF_INET, SOCK_DGRAM, 0);

    if (single_socket.fd < 0)
    {
        throw(ExceptionsHandler::bad_socket_creation());
    }

    memset(&(single_socket.server_address), 0, sizeof(single_socket.server_address));
    memset(&(single_socket.client_address), 0, sizeof(single_socket.client_address));

    single_socket.server_address.sin_family = AF_INET;
    single_socket.server_address.sin_addr.s_addr = INADDR_ANY;
    single_socket.server_address.sin_port = htons(port);

    int bind_result = bind(single_socket.fd, (const struct sockaddr *)&single_socket.server_address,
                           sizeof(single_socket.server_address));

    if (bind_result < 0)
    {
        throw(ExceptionsHandler::bad_bind());
    }

    slog_info("Opened socket on port number: %d", port);
    return single_socket;
}

void Receivers::set_metadata_socket(const int &metadata_port)
{
    metadata_socket = set_single_socket(metadata_port);
    FD_SET(metadata_socket.fd, &sockets);
    max_fd = metadata_socket.fd;
}

void Receivers::set_data_sockets(const std::vector<int> &data_ports)
{
    for (const int &port : data_ports)
    {
        data_sockets.push_back(set_single_socket(port));
        FD_SET(data_sockets.back().fd, &sockets);

        if (data_sockets.back().fd > max_fd)
        {
            max_fd = data_sockets.back().fd;
        }
    }
}

void Receivers::start_receiving()
{
    sigset_t emptyset;
    int readable_count = 0;

    while (true)
    {
        copy = sockets;
        sigemptyset(&emptyset);

        readable_count = pselect(max_fd + 1, &copy, nullptr, nullptr, nullptr, &sigbreak.sa_mask);

        if (readable_count < 0)
        {
            if (errno != EINTR)
            {
                throw(ExceptionsHandler::bad_select());
            }
            return;
        }
    }
}

void Receivers::handle_readables()
{
    if (FD_ISSET(metadata_socket.fd, &copy))
    {
        handle_metadata();
        std::fill(buffer.begin(), buffer.end(), '\0');
    }

    for (int i = 0; i < data_sockets.size(); i++)
    {
        if (FD_ISSET(data_sockets[i].fd, &copy))
        {
            handle_data(data_sockets[i]);
        }
    }
}

void Receivers::handle_metadata()
{
    metadata_socket.receive_len = recvfrom(metadata_socket.fd, &buffer[0], buffer_size, 0,
                                           (struct sockaddr *)&metadata_socket.client_address, &metadata_socket.socket_len);

    if (metadata_socket.receive_len > 0)
    {
    }

    else
    {
        FD_CLR(metadata_socket.fd, &sockets);
    }
}

void Receivers::handle_data(socket_settings &data_socket)
{
    data_socket.receive_len = recvfrom(data_socket.fd, &buffer[0], buffer_size, 0,
                                       (struct sockaddr *)&data_socket.client_address, &data_socket.socket_len);

    if (data_socket.receive_len > 0)
    {
    }

    else
    {
        FD_CLR(data_socket.fd, &sockets);

        for (auto it = data_sockets.begin(); it != data_sockets.end(); it++)
        {
            if (it->fd == data_socket.fd)
            {
                data_sockets.erase(it);
                return;
            }
        }
    }
}