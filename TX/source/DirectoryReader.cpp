#include "../include/DirectoryReader.h"

DirectoryReader::DirectoryReader()
{
}

DirectoryReader::~DirectoryReader()
{
    paths.clear();
}

void DirectoryReader::iterate_channel_dir(std::string current_dir)
{
    DIR *dir = opendir(current_dir.c_str());
    struct dirent *entry;

    while ((entry = readdir(dir)) != NULL)
    {
        if (is_dir(entry))
        {
            iterate_channel_dir(current_dir + "/" + entry->d_name + "/");
        }

        else if (!is_dot(entry->d_name))
        {
            paths.push_back(current_dir + "/" + entry->d_name);
        }
    }

    closedir(dir);
}

bool DirectoryReader::is_dir(struct dirent *entry)
{
    std::string name = entry->d_name;

    return !is_dot(name) && entry->d_type != IS_FILE;
}

bool DirectoryReader::is_dot(const std::string &name)
{
    return name == "." || name == "..";
}

std::vector<std::string> &DirectoryReader::get_paths()
{
    return paths;
}