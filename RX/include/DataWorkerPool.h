#pragma once

#include "essential.h"
#include "DataWorker.h"

class DataWorkerPool
{
private:
    std::map<DataWorker *, bool> data_workers;
    boost::asio::thread_pool thread_pool;

public:
    DataWorkerPool(const int &amount_of_workers);
    ~DataWorkerPool();

    void set_workers(const int &amount_of_workers);

    void start_working(std::string &data, DataWorker *worker);
    void add_job(std::string data);
    DataWorker *get_first_available_worker();

    void terminate_pool();
    void delete_workers();
};