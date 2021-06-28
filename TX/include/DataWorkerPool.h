#pragma once

#include "essential.h"
#include "DataWorker.h"

class DataWorkerPool
{
private:
    std::map<DataWorker *, bool> data_workers;
    boost::asio::thread_pool thread_pool;

public:
    DataWorkerPool(int &amount_of_workers);
    ~DataWorkerPool();

    void set_workers(const std::vector<unsigned int> &ports, channel_configurations configurations);

    void start_working(std::string &data, int &file_id, int &channel_id, DataWorker *worker);
    void add_job(std::string &data, int &file_id, int &channel_id);
    DataWorker *get_first_available_worker();

    void terminate_pool();
    void delete_workers();
};