#pragma once

#include "essential.h"

class FileStream
{
private:
    FILE *file;
    static std::mutex m_lock;
    std::vector<unsigned char> buffer;

public:
    FileStream();
    ~FileStream();

    FILE *get_file();

    void create_file(const std::string &path);
    void set_file(const std::string &path);

    void set_read_buffer(const int &buffer_size);

    void write_to_file(const std::string &data, const int &offset);
    void append_to_file(const std::string &data);

    std::string read_file(const int &amount);
    int get_size();

    void close_file();
};