#pragma once

#include "essential.h"
#include "MetadataWorker.h"

class MetadataWorkerPool
{
private:
    std::map<MetadataWorker *, bool> metadata_workers;
    boost::asio::io_service io_service;
    boost::thread_group thread_pool;

public:
    MetadataWorkerPool();
    ~MetadataWorkerPool();

    void set_workers(const int &amount_of_workers);

    void start_working(std::string &data, MetadataWorker *worker);
    void add_job(std::string &data);
    MetadataWorker *get_first_available_worker();

    void terminate_pool();
    void delete_workers();
};