#include "../include/MetadataWorkerPool.h"

MetadataWorkerPool::MetadataWorkerPool()
{
    boost::asio::io_service::work work(io_service);
}

MetadataWorkerPool::~MetadataWorkerPool()
{
}

void MetadataWorkerPool::set_workers(const int &amount_of_workers)
{
    for (int i = 0; i < amount_of_workers; i++)
    {
        metadata_workers.insert({new MetadataWorker(), false});
        thread_pool.create_thread(boost::bind(&boost::asio::io_service::run, &io_service));
    }

    slog_info("Opened metadata worker pool");
}

void MetadataWorkerPool::start_working(std::string &data, MetadataWorker *worker)
{
    metadata_workers.at(worker) = false;
}

void MetadataWorkerPool::add_job(std::string &data)
{
    MetadataWorker *worker = get_first_available_worker();
    io_service.post(boost::bind(&MetadataWorkerPool::start_working, this, data, worker));
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
    io_service.stop();
    thread_pool.join_all();

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