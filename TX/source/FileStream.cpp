#include "../include/FileStream.h"

FileStream::FileStream()
{
    file = NULL;
}

FileStream::~FileStream()
{
    if (file != NULL)
    {
        close_file();
    }
}

void FileStream::set_file(const std::string &path, const int &buffer_size)
{
    file = fopen(path.c_str(), "rb");

    if (file == NULL)
    {
        throw(ExceptionsHandler::bad_stream_open());
    }

    fseek(file, 0, SEEK_END);
    size = ftell(file);
    fseek(file, 0, SEEK_SET);

    buffer.resize(buffer_size);
    std::fill(buffer.begin(), buffer.end(), '\0');
}

std::string FileStream::read_file(const int &amount)
{
    fread(reinterpret_cast<char *>(&buffer[0]), amount, 1, file);
    std::string data(buffer.begin(), buffer.end());

    std::fill(buffer.begin(), buffer.end(), '\0');
    return data;
}

void FileStream::close_file()
{
    if (file != NULL)
    {
        fclose(file);
        file = NULL;
    }
}

int &FileStream::get_size()
{
    return size;
}