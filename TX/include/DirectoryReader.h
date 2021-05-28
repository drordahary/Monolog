#pragma once

#include "essential.h"

#define IS_FILE 0x8

class DirectoryReader
{
private:
    std::vector<std::string> paths;

public:
    DirectoryReader();
    ~DirectoryReader();

    void iterate_channel_dir(std::string current_dir);

    bool is_dir(struct dirent *entry);
    bool is_dot(const std::string &name);

    void extract_relative_paths(std::string channel_dir);
    std::string extract_file_name(const std::string &path);

    std::vector<std::string> &get_paths();
    void clear_paths();
};