#include "../include/DataWorkerPool.h"

DataWorkerPool::DataWorkerPool()
{
    boost::asio::io_service::work work(io_service);
}

DataWorkerPool::~DataWorkerPool()
{
}

void DataWorkerPool::set_workers(int &amount_of_workers, channel_configurations configurations)
{
    for (int i = 0; i < amount_of_workers; i++)
    {
        data_workers.insert({new DataWorker(configurations), false});
        thread_pool.create_thread(boost::bind(&boost::asio::io_service::run, &io_service));
    }
}

void DataWorkerPool::start_working(std::string &data, DataWorker *worker)
{
    data_workers.at(worker) = false;
}

void DataWorkerPool::add_job(std::string &data)
{
    DataWorker *worker = get_first_available_worker();
    io_service.post(boost::bind(&DataWorkerPool::start_working, this, data, worker));
}

DataWorker *DataWorkerPool::get_first_available_worker()
{
    while (true)
    {
        for (auto &worker : data_workers)
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

void DataWorkerPool::terminate_pool()
{
    io_service.stop();
    thread_pool.join_all();

    delete_workers();
}

void DataWorkerPool::delete_workers()
{
    for (auto &worker : data_workers)
    {
        delete worker.first;
    }

    data_workers.clear();
}