#include "../include/FileHandler.h"

void FileHandler::move_file(std::string from, std::string to)
{
    slog_trace("FROM: %s", from.c_str());
    slog_trace("TO: %s", to.c_str());
    if (rename(from.c_str(), to.c_str()) != 0)
    {
        throw(ExceptionsHandler::bad_file_move());
    }
}