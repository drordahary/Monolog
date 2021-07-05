#include "../include/FileMonitor.h"

std::map<int, std::vector<int>> FileMonitor::files_ids;

void FileMonitor::add_file_id(const int &channel_id, const int &file_id)
{
    if (!file_id_exists(channel_id, file_id))
    {
        files_ids[channel_id].push_back(file_id);
    }
}

bool FileMonitor::file_id_exists(const int &channel_id, const int &file_id)
{
    std::map<int, std::vector<int>>::const_iterator search = files_ids.find(channel_id);

    if (search != files_ids.end())
    {
        std::vector<int> copy = search->second;

        if (std::find(copy.begin(), copy.end(), file_id) != copy.end())
            ;
        {
            return true;
        }
    }

    return false;
}