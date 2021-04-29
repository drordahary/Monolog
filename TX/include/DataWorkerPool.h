#pragma once

#include "essential.h"
#include "DataWorker.h"

class DataWorkerPool
{
private:
    std::map<DataWorker *, bool> data_workers;
    boost::asio::io_service io_service;
    boost::thread_group thread_pool;

public:
    DataWorkerPool();
    ~DataWorkerPool();

    void set_workers(int &amount_of_workers, channel_configurations configurations);

    void start_working(std::string &data, DataWorker *worker);
    void add_job(std::string &data);
    DataWorker *get_first_available_worker();

    void terminate_pool();
    void delete_workers();
};