#include "../include/essential.h"
#include "../include/StartUp.h"

bool exiting = false;

void finish(int signal)
{
    exiting = true;
    slog_info("Exited cleanly");
}

int set_signal_handler()
{
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
        StartUp start_up;
        start_up.set_infrastructure();

        int success = set_signal_handler();
        if (!success)
        {
            slog_warn("Cannot set signal handler");
        }

        while (!exiting)
        {
        }
    }

    catch (const std::string &exception)
    {
        slog_fatal("%s", exception);
    }

    return EXIT_SUCCESS;
}