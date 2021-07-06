#pragma once

#include "essential.h"

class FileStream
{
private:
    FILE *file;

public:
    FileStream();
    ~FileStream();

    FILE *get_file();

    void create_file(const std::string &path);
    void set_file(const std::string &path);

    void write_to_file(const std::string &data, const int &offset);
    void append_to_file(const std::string &data);

    void read_file(std::string &data, const int &offset, const int &amount);

    void close_file();
};