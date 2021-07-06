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

FILE *FileStream::get_file()
{
    return file;
}

void FileStream::create_file(const std::string &path)
{
    file = fopen(path.c_str(), "ab");
}

void FileStream::set_file(const std::string &path)
{
    file = fopen(path.c_str(), "rb+");

    if (file == NULL)
    {
        throw(ExceptionsHandler::bad_stream_open());
    }
}

void FileStream::write_to_file(const std::string &data, const int &offset)
{
    lseek(fileno(file), offset, SEEK_SET);
    fwrite(data.c_str(), 1, data.length(), file);
    fflush(file);
}

void FileStream::append_to_file(const std::string &data)
{
    fwrite(data.c_str(), 1, data.length(), file);
    fflush(file);
}

void FileStream::read_file(std::string &data, const int &offset, const int &amount)
{
    lseek(fileno(file), offset, SEEK_SET);
    fread(&data[0], 1, amount, file);
}

void FileStream::close_file()
{
    if (file != NULL)
    {
        fclose(file);
        file = NULL;
    }
}