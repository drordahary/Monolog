#include "../include/MetadataWorkerPool.h"

MetadataWorkerPool::MetadataWorkerPool(const int &amount_of_workers) : thread_pool(amount_of_workers)
{
}

MetadataWorkerPool::~MetadataWorkerPool()
{
}

void MetadataWorkerPool::set_workers(const int &amount_of_workers, UntrackedWorkerPool *untracked_pool)
{
    for (int i = 0; i < amount_of_workers; i++)
    {
        metadata_workers.insert({new MetadataWorker(untracked_pool), false});
    }

    slog_info("Opened metadata worker pool");
}

void MetadataWorkerPool::start_working(std::string data, MetadataWorker *worker, int buffer_size)
{
    worker->start_working(data, buffer_size);
    metadata_workers.at(worker) = false;
}

void MetadataWorkerPool::add_job(std::string data, int buffer_size)
{
    MetadataWorker *worker = get_first_available_worker();
    boost::asio::post(thread_pool, std::bind(&MetadataWorkerPool::start_working, this, data, worker, buffer_size));
}

MetadataWorker *MetadataWorkerPool::get_first_available_worker()
{
    while (true)
    {
        auto result = std::find_if(metadata_workers.begin(), metadata_workers.end(), is_worker_available);

        if (result != metadata_workers.end())
        {
            result->second = true;
            return result->first;
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

bool MetadataWorkerPool::is_worker_available(std::pair<MetadataWorker *, bool> worker)
{
    return !worker.second;
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