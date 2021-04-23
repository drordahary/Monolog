#include "../include/essential.h"
#include "../include/StartUp.h"

int main()
{
    try
    {
        StartUp start_up;
    }

    catch (const std::string &exception)
    {
        slog_fatal("%s", exception);
    }

    return EXIT_SUCCESS;
}