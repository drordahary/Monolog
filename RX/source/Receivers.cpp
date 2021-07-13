#include "../include/Receivers.h"

Receivers::Receivers(channel_configurations configurations)
{
    this->configurations = configurations;
    FD_ZERO(&sockets);
    max_fd = -1;

    buffer_size = configurations.buffer_size;
    buffer = new char[this->configurations.buffer_size + 1];
    std::fill(buffer, buffer + buffer_size + 1, '\0');
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

    delete[] buffer;
    data_sockets.clear();
}

void Receivers::set_pools(DataWorkerPool *data_pool, MetadataWorkerPool *metadata_pool)
{
    this->data_pool = data_pool;
    this->metadata_pool = metadata_pool;
}

void Receivers::set_sockets(const int &metadata_port, const std::vector<unsigned int> &data_ports)
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

    single_socket.socket_len = 0;

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

    if (metadata_socket.fd > max_fd)
    {
        max_fd = metadata_socket.fd;
    }
}

void Receivers::set_data_sockets(const std::vector<unsigned int> &data_ports)
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
    int readable_count = 0;

    while (!exiting)
    {
        copy = sockets;
        readable_count = select(max_fd + 1, &copy, nullptr, nullptr, nullptr);

        if (FD_ISSET(pfd[0], &copy))
        {
            return;
        }

        if (readable_count < 0)
        {
            if (errno != EINTR)
            {
                throw(ExceptionsHandler::bad_select());
            }
            return;
        }

        handle_readables();
    }
}

void Receivers::handle_readables()
{
    if (FD_ISSET(metadata_socket.fd, &copy))
    {
        handle_metadata();
        std::fill(buffer, buffer + buffer_size + 1, '\0');
    }

    for (int i = 0; i < data_sockets.size(); i++)
    {
        if (FD_ISSET(data_sockets[i].fd, &copy))
        {
            handle_data(data_sockets[i]);
            std::fill(buffer, buffer + buffer_size + 1, '\0');
        }
    }
}

void Receivers::handle_metadata()
{
    metadata_socket.receive_len = recvfrom(metadata_socket.fd, buffer, buffer_size + 1, 0,
                                           (struct sockaddr *)&metadata_socket.client_address, &metadata_socket.socket_len);

    if (metadata_socket.receive_len > 0)
    {
        metadata_pool->add_job(std::string(buffer), buffer_size);
    }
}

void Receivers::handle_data(socket_settings &data_socket)
{
    data_socket.receive_len = recvfrom(data_socket.fd, buffer, buffer_size + 1, 0,
                                       (struct sockaddr *)&data_socket.client_address, &data_socket.socket_len);

    if (data_socket.receive_len > 0)
    {
        data_pool->add_job(std::string(buffer), buffer_size);
    }
}

void Receivers::set_pipe()
{
    if (pipe(pfd) == -1)
    {
        throw(ExceptionsHandler::bad_pipe());
    }

    FD_SET(pfd[0], &sockets);
    max_fd = pfd[0];
}

void Receivers::self_pipe()
{
    write(pfd[1], "X", 1);
}