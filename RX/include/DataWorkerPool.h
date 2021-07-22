#pragma once

#include "essential.h"
#include "DataWorker.h"
#include "Settings.h"

class DataWorkerPool
{
private:
    std::map<DataWorker *, bool> data_workers;
    boost::asio::thread_pool thread_pool;

public:
    explicit DataWorkerPool(const int &amount_of_workers);
    ~DataWorkerPool();

    void set_workers(const int &amount_of_workers);

    void start_working(std::string &data, DataWorker *worker, const int &buffer_size);
    void add_job(std::string data, int &buffer_size);

    DataWorker *get_first_available_worker();
    static bool is_worker_available(std::pair<DataWorker *, bool> worker);

    void terminate_pool();
    void delete_workers();
};