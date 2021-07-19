#include "../include/TimeWorker.h"

TimeWorker::TimeWorker(unsigned int port)
{
    max_fd = -1;
    FD_ZERO(&sockets);
    buffer = new char[TIME_BUFFER_SIZE + 1];
}

TimeWorker::~TimeWorker()
{
    close(settings.fd);
    delete[] buffer;

    FD_ZERO(&sockets);
    FD_ZERO(&copy);
}

void TimeWorker::set_socket(unsigned int port)
{
    settings.fd = socket(AF_INET, SOCK_DGRAM, 0);

    if (settings.fd < 0)
    {
        throw(ExceptionsHandler::bad_socket_creation());
    }

    memset(&(settings.server_address), 0, sizeof(settings.server_address));
    memset(&(settings.client_address), 0, sizeof(settings.client_address));

    settings.server_address.sin_family = AF_INET;
    settings.server_address.sin_addr.s_addr = INADDR_ANY;
    settings.server_address.sin_port = htons(port);

    settings.socket_len = 0;

    int bind_result = bind(settings.fd, (const struct sockaddr *)&settings.server_address,
                           sizeof(settings.server_address));

    if (bind_result < 0)
    {
        slog_error("%d", errno);
        throw(ExceptionsHandler::bad_bind());
    }

    FD_SET(settings.fd, &sockets);
    if (settings.fd > max_fd)
    {
        max_fd = settings.fd;
    }
}

void TimeWorker::start_receiving()
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

        handle_readable();
    }
}

void TimeWorker::handle_readable()
{
    if (FD_ISSET(settings.fd, &copy))
    {
        std::fill(buffer, buffer + TIME_BUFFER_SIZE + 1, '\0');
        settings.receive_len = recvfrom(settings.fd, buffer, TIME_BUFFER_SIZE + 1, 0,
                                        (struct sockaddr *)&settings.client_address, &settings.socket_len);

        if (settings.receive_len > 0)
        {
            current_time = buffer;
            system_command = "sudo date +%s -s @" + current_time;
            system(system_command.c_str());
            slog_trace("Updated time to: %s", current_time.c_str());
        }
    }
}

void TimeWorker::set_pipe()
{
    if (pipe(pfd) == -1)
    {
        throw(ExceptionsHandler::bad_pipe());
    }

    FD_SET(pfd[0], &sockets);
    max_fd = pfd[0];
}

void TimeWorker::self_pipe()
{
    write(pfd[1], "X", 1);
}