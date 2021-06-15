#include "../include/DataWorkerPool.h"

DataWorkerPool::DataWorkerPool(int &amount_of_workers) : thread_pool(amount_of_workers)
{
}

DataWorkerPool::~DataWorkerPool()
{
}

void DataWorkerPool::set_workers(const std::vector<unsigned int> &ports, channel_configurations configurations)
{
    for (int i = 0; i < ports.size(); i++)
    {
        data_workers.insert({new DataWorker(configurations, ports.at(i)), false});
    }
}

void DataWorkerPool::start_working(std::string &data, DataWorker *worker)
{
    worker->start_transmitting(data);
    data_workers.at(worker) = false;
}

void DataWorkerPool::add_job(std::string &data)
{
    DataWorker *worker = get_first_available_worker();
    boost::asio::post(thread_pool, std::bind(&DataWorkerPool::start_working, this, data, worker));
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
    thread_pool.join();
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