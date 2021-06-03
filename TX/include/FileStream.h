#pragma once

#include "essential.h"

class FileStream
{
private:
    FILE* file;
    int size;
    std::vector<unsigned char> buffer;

public:
    FileStream();
    ~FileStream();

    void set_file(const std::string &path, const int &buffer_size);
    std::string read_file(const int &amount);

    void close_file();

    int &get_size();
};