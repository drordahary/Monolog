#pragma once

#include "essential.h"

class DirectoryOrganizer
{
public:
    static void produce_structure(const std::string &path);
    static std::string extract_directory_structure(std::string path);
    static void make_directories(std::string path, int count);
};

size_t nth_occurrence(const std::string &str, const std::string &to_find, int nth);