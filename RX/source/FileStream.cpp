#include "../include/FileStream.h"

std::mutex FileStream::m_lock;

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

FILE *FileStream::get_file()
{
    return file;
}

void FileStream::create_file(const std::string &path)
{
    if (file != NULL)
    {
        close_file();
    }

    file = fopen(path.c_str(), "ab");
}

void FileStream::set_file(const std::string &path)
{
    if (file != NULL)
    {
        close_file();
    }
    
    file = fopen(path.c_str(), "rb+");

    if (file == NULL)
    {
        throw(ExceptionsHandler::bad_stream_open());
    }
}

void FileStream::set_read_buffer(const int &buffer_size)
{
    buffer.resize(buffer_size);
    std::fill(buffer.begin(), buffer.end(), '\0');
}

void FileStream::write_to_file(const std::string &data, const int &offset)
{
    lseek(fileno(file), offset, SEEK_SET);
    fwrite(data.c_str(), 1, data.length(), file);
    fflush(file);
}

void FileStream::append_to_file(const std::string &data)
{
    std::lock_guard<std::mutex> lock(m_lock);
    fwrite(data.c_str(), 1, data.length(), file);
    fflush(file);
}

std::string FileStream::read_file(const int &amount)
{
    std::lock_guard<std::mutex> lock(m_lock);

    fread(reinterpret_cast<char *>(&buffer[0]), amount, 1, file);
    std::string data(buffer.begin(), buffer.end());

    std::fill(buffer.begin(), buffer.end(), '\0');
    return data;
}

int FileStream::get_size()
{
    fseek(file, 0, SEEK_END);
    int size = ftell(file);
    fseek(file, 0, SEEK_SET);

    return size;
}

void FileStream::close_file()
{
    if (file != NULL)
    {
        fclose(file);
        file = NULL;
    }
}