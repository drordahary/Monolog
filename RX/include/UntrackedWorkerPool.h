#pragma once

#include "essential.h"
#include "UntrackedWorker.h"

class UntrackedWorkerPool
{
private:
    std::map<UntrackedWorker *, bool> metadata_workers;
    boost::asio::thread_pool thread_pool;

public:
    UntrackedWorkerPool(const int &amount_of_workers);
    ~UntrackedWorkerPool();

    void set_workers(const int &amount_of_workers);

    void start_working(std::string data, UntrackedWorker *worker);
    void add_job(std::string data);
    UntrackedWorker *get_first_available_worker();

    void terminate_pool();
    void delete_workers();
};