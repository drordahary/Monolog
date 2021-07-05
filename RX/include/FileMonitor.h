#pragma once

#include "essential.h"

class FileMonitor
{
private:
    static std::map<int, std::vector<int>> files_ids;

public:
    static void add_file_id(const int &channel_id, const int &file_id);
    static bool file_id_exists(const int &channel_id, const int &file_id);
};