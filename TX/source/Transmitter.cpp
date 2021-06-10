#include "../include/Transmitter.h"

Transmitter::Transmitter(std::string ip, unsigned int port, int buffer_size)
{
    configurations.ip = ip;
    configurations.port = port;

    this->buffer_size = buffer_size;
    buffer = new char[this->buffer_size + 1];

    set_socket();
}

Transmitter::~Transmitter()
{
    delete[] buffer;
    close(settings.fd);
}

void Transmitter::set_socket()
{
    std::fill(buffer, buffer + buffer_size + 1, '\0');

    settings.socket_len = sizeof(settings.server_address);

    if ((settings.fd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
    {
        throw(ExceptionsHandler::bad_socket_open());
    }

    settings.server_address.sin_family = AF_INET;
    settings.server_address.sin_port = htons(configurations.port);
    inet_pton(AF_INET, configurations.ip.c_str(), &(settings.server_address.sin_addr));

    slog_info("Opened socket on port: %d", configurations.port);
}

void Transmitter::transmitt_packet()
{
    if (sendto(settings.fd, buffer, buffer_size + 1, 0,
               (struct sockaddr *)&(settings.server_address), sizeof(settings.server_address)) == -1)
    {
        slog_warn("Could not send packet");
    }

    std::fill(buffer, buffer + buffer_size + 1, '\0');
}