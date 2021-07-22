#include "../include/UntrackedWorkerPool.h"

UntrackedWorkerPool::UntrackedWorkerPool(const int &amount_of_workers) : thread_pool(amount_of_workers)
{
}

UntrackedWorkerPool::~UntrackedWorkerPool()
{
}

void UntrackedWorkerPool::set_workers(const int &amount_of_workers)
{
    for (int i = 0; i < amount_of_workers; i++)
    {
        untracked_workers.insert({new UntrackedWorker(), false});
    }

    slog_info("Opened untracked worker pool");
}

void UntrackedWorkerPool::start_working(std::string data, UntrackedWorker *worker)
{
    worker->start_working(data);
    untracked_workers.at(worker) = false;
}

void UntrackedWorkerPool::add_job(std::string data)
{
    UntrackedWorker *worker = get_first_available_worker();
    boost::asio::post(thread_pool, std::bind(&UntrackedWorkerPool::start_working, this, data, worker));
}

UntrackedWorker *UntrackedWorkerPool::get_first_available_worker()
{
    while (true)
    {
        auto result = std::find_if(untracked_workers.begin(), untracked_workers.end(), is_worker_available);

        if (result != untracked_workers.end())
        {
            result->second = true;
            return result->first;
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

bool UntrackedWorkerPool::is_worker_available(std::pair<UntrackedWorker *, bool> worker)
{
    return !worker.second;
}

void UntrackedWorkerPool::terminate_pool()
{
    thread_pool.join();
    delete_workers();
}

void UntrackedWorkerPool::delete_workers()
{
    for (auto &worker : untracked_workers)
    {
        delete worker.first;
    }

    untracked_workers.clear();
}