#include "../include/MetadataWorker.h"

MetadataWorker::MetadataWorker(channel_configurations configurations)
{
    this->configurations = configurations;
}

MetadataWorker::~MetadataWorker()
{
}

void MetadataWorker::enable_pool_usage(DataWorkerPool *data_pool)
{
    this->data_pool = data_pool;
}

void MetadataWorker::start_working()
{
    std::string absolute_path = configurations.channel_directory;
    dir_reader.iterate_channel_dir(absolute_path);
    std::vector<std::string> paths = dir_reader.get_paths();
}