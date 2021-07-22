#include "../include/DirectoryOrganizer.h"

void DirectoryOrganizer::produce_structure(const std::string &path)
{
    std::string new_path = extract_directory_structure(path);
    make_directories(new_path, 1);
}

std::string DirectoryOrganizer::extract_directory_structure(std::string path)
{
    size_t position = path.find_last_of('/');
    return path.substr(0, position + 1);
}

void DirectoryOrganizer::make_directories(std::string path, int count)
{
    size_t position = nth_occurrence(path, "/", count) + 1;

    if (position == 0)
    {
        return;
    }

    mkdir(path.substr(0, position).c_str(), 0777);
    make_directories(path, ++count);
}

size_t nth_occurrence(const std::string &str, const std::string &to_find, int nth)
{
    size_t position = 0;
    int count = 0;

    while (count != nth)
    {
        position += 1;
        position = str.find(to_find, position);

        if (position == std::string::npos)
        {
            return -1;
        }

        count++;
    }

    return position;
}