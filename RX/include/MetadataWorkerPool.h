#pragma once

#include "essential.h"
#include "MetadataWorker.h"

class MetadataWorkerPool
{
private:
    std::map<MetadataWorker *, bool> metadata_workers;
    boost::asio::thread_pool thread_pool;

public:
    explicit MetadataWorkerPool(const int &amount_of_workers);
    ~MetadataWorkerPool();

    void set_workers(const int &amount_of_workers, UntrackedWorkerPool *untracked_pool);

    void start_working(std::string data, MetadataWorker *worker, int buffer_size);
    void add_job(std::string data, int buffer_size);

    MetadataWorker *get_first_available_worker();
    static bool is_worker_available(std::pair<MetadataWorker *, bool> worker);

    void terminate_pool();
    void delete_workers();
};