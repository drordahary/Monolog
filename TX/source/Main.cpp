#include "../include/essential.h"
#include "../include/StartUp.h"

StartUp start_up;
bool exiting;

void finish(int signal)
{
    start_up.terminate_now();
    exiting = true;

    slog_info("Exited cleanly");
}

int set_signal_handler()
{
    exiting = false;

    struct sigaction sigbreak;
    sigbreak.sa_handler = &finish;
    sigemptyset(&sigbreak.sa_mask);
    sigbreak.sa_flags = 0;

    if (sigaction(SIGINT, &sigbreak, NULL) != 0)
    {
        return 0;
    }

    slog_info("Successfully applied function to the signal handler");

    return 1;
}

int main()
{
    try
    {
        start_up.set_infrastructure();

        int success = set_signal_handler();
        if (!success)
        {
            slog_warn("Cannot set signal handler");
        }

        start_up.set_ports();
        start_up.set_groups();
        start_up.initiate_transmitters();

        while (!exiting)
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
        }
    }

    catch (const std::string &exception)
    {
        slog_fatal("%s", exception.c_str());
    }

    return EXIT_SUCCESS;
}