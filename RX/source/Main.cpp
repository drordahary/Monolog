#include "../include/essential.h"
#include "../include/StartUp.h"

StartUp start_up;
bool exiting;

void finish(int signal)
{
    start_up.terminate_now();
    exiting = true;
}

int install_signal_handler()
{
    struct sigaction sigbreak;
    sigbreak.sa_handler = &finish;
    sigemptyset(&sigbreak.sa_mask);
    sigbreak.sa_flags = 0;

    if (sigaction(SIGINT, &sigbreak, NULL) != 0)
    {
        return 0;
    }
    return 1;
}

int main()
{
    try
    {
        exiting = false;
        start_up.set_infrastructure();

        int success = install_signal_handler();
        if (!success)
        {
            slog_warn("Cannot set signal handler");
        }

        start_up.set_ports();
        start_up.set_pools();
        start_up.set_groups();
        start_up.set_ntp();

        while (!exiting)
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
        }

        slog_info("Exited cleanly");
    }

    catch (const std::string &exception)
    {
        if (!exiting)
        {
            slog_fatal("%s", exception.c_str());
        }
    }

    return EXIT_SUCCESS;
}