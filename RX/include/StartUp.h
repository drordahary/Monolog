#pragma once

#include "essential.h"
#include "Settings.h"
#include "Group.h"
#include "GroupFactory.h"
#include "Ports.h"
#include "DataWorkerPool.h"
#include "MetadataWorkerPool.h"
#include "UntrackedWorkerPool.h"
#include "TimeWorker.h"

namespace pool_settings
{
    const int data_pool_size = 20;
    const int metadata_pool_size = 5;
    const int untracked_pool_size = 5;
}

class StartUp
{
private:
    Settings settings;
    std::vector<Group *> groups;
    Ports ports;
    DataWorkerPool *data_pool;
    MetadataWorkerPool *metadata_pool;
    UntrackedWorkerPool *untracked_pool;

    TimeWorker *time_worker;
    boost::thread *ntp_thread;

public:
    StartUp();
    ~StartUp();

    void set_infrastructure();
    void set_ports();
    void set_pools();
    void set_groups();
    void set_ntp();

    void terminate_now();
};