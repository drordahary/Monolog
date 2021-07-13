#pragma once

#include "essential.h"
#include "FileStream.h"
#include "DataWorker.h"

typedef struct untracked_file
{
    int channel_id;
    int file_id;
    int file_size;
    int buffer_size;
    std::string path;

} untracked_file;

class UntrackedWorker
{
private:
    untracked_file file;

public:
    UntrackedWorker();
    ~UntrackedWorker();

    void start_working(std::string &data);
    void organize_data(std::string &data);
    void restore_file();
};