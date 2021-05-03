#include "../include/essential.h"
#include "../include/StartUp.h"

StartUp start_up;

bool exiting = false;
struct sigaction sigbreak;
sigset_t emptyset, blockset;

void finish(int signal)
{
    start_up.terminate_now();
    exiting = true;
}

int install_signal_handler()
{
    sigemptyset(&blockset);
    sigaddset(&blockset, SIGINT);
    sigprocmask(SIG_BLOCK, &blockset, NULL);

    sigbreak.sa_handler = finish;
    sigbreak.sa_flags = 0;
    sigemptyset(&sigbreak.sa_mask);

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
        start_up.set_infrastructure();

        int success = install_signal_handler();
        if (!success)
        {
            slog_warn("Cannot set signal handler");
        }

        start_up.set_ports();
        start_up.set_pools();
        start_up.set_groups();

        sigprocmask(SIG_SETMASK, &blockset, NULL);

        while (!exiting)
        {
        }
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