#include "../include/MetadataWorkerPool.h"

MetadataWorkerPool::MetadataWorkerPool(const int &amount_of_workers) : thread_pool(amount_of_workers)
{
}

MetadataWorkerPool::~MetadataWorkerPool()
{
}

void MetadataWorkerPool::set_workers(const int &amount_of_workers)
{
    for (int i = 0; i < amount_of_workers; i++)
    {
        metadata_workers.insert({new MetadataWorker(), false});
    }

    slog_info("Opened metadata worker pool");
}

void MetadataWorkerPool::start_working(std::string data, MetadataWorker *worker)
{
    worker->start_working(data);
    metadata_workers.at(worker) = false;
}

void MetadataWorkerPool::add_job(std::string data)
{
    MetadataWorker *worker = get_first_available_worker();
    boost::asio::post(thread_pool, std::bind(&MetadataWorkerPool::start_working, this, data, worker));
}

MetadataWorker *MetadataWorkerPool::get_first_available_worker()
{
    while (true)
    {
        for (auto &worker : metadata_workers)
        {
            if (!worker.second)
            {
                worker.second = true;
                return worker.first;
            }
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

void MetadataWorkerPool::terminate_pool()
{
    thread_pool.join();
    delete_workers();
}

void MetadataWorkerPool::delete_workers()
{
    for (auto &worker : metadata_workers)
    {
        delete worker.first;
    }

    metadata_workers.clear();
}