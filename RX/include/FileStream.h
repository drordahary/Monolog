#pragma once

#include "essential.h"

class FileStream
{
private:
    FILE *file;

public:
    FileStream();
    ~FileStream();

    void set_file(const std::string &path);
    void write_to_file(const std::string &data, const int &offset);

    void close_file();
};