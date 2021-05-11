#include "../include/MetadataWorker.h"

MetadataWorker::MetadataWorker(channel_configurations configurations, int channel_id)
{
    this->configurations = configurations;
    this->channel_id = channel_id;
    redis_handler.connect_to_redis();
    redis_handler.select_database(REDIS_TX_DB);
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

    dir_reader.extract_relative_paths(absolute_path);
    std::vector<std::string> paths = dir_reader.get_paths();

    int file_id = 0;
    int file_size = 1000;

    for (std::string &path : paths)
    {
        save_metadata_to_redis(file_id, path, file_size);
        file_id++;
    }
}

void MetadataWorker::save_metadata_to_redis(int &file_id, std::string &path, int &file_size)
{
    std::string key = std::to_string(channel_id);

    std::pair<std::string, std::string> field;
    field.first = std::to_string(file_id);
    field.second = path + ":" + std::to_string(file_size);

    redis_handler.save_metadata(key, field);
}