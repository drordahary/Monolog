#include "../include/DataWorker.h"

DataWorker::DataWorker(channel_configurations configurations)
{
    this->configurations = configurations;
}

DataWorker::~DataWorker()
{
}

void DataWorker::start_transmitting(const std::string &file_path)
{
    file.set_file(file_path, configurations.buffer_size);
    std::string data;

    int completed = 0;
    int size = file.get_size();
    int amount_to_read = 0;

    while (completed < size)
    {
        amount_to_read = calculate_amount_to_read(size, completed);
        data = file.read_file(amount_to_read);
        completed += amount_to_read;
    }
}

int DataWorker::calculate_amount_to_read(const int &size, const int &completed)
{
    if ((size - completed) >= (configurations.buffer_size - OVERHEAD_SIZE))
    {
        return configurations.buffer_size - OVERHEAD_SIZE;
    }

    return size - completed;
}