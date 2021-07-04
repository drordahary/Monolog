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

void FileStream::set_file(const std::string &path)
{
    file = fopen(path.c_str(), "wb");

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

void FileStream::close_file()
{
    if (file != NULL)
    {
        fclose(file);
        file = NULL;
    }
}