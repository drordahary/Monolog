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

    while (!exiting)
    {
        dir_reader.iterate_channel_dir(absolute_path);
        fixed_paths = dir_reader.get_paths();

        dir_reader.extract_relative_paths(absolute_path);
        paths = dir_reader.get_paths();

        handle_paths();

        paths.clear();
        fixed_paths.clear();
        dir_reader.clear_paths();

        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

void MetadataWorker::handle_paths()
{
    int file_id = 0;
    int file_size = 1000;
    std::string new_path = STAGING_DIR;
    std::string move_to;

    auto fixed_paths_it = fixed_paths.begin();

    for (std::string &path : paths)
    {
        new_path += path;
        DirectoryOrganizer::produce_structure(new_path);

        if (path[path.length() - 1] != '/')
        {
            save_metadata_to_redis(file_id, path, file_size);

            move_to = new_path + dir_reader.extract_file_name(path);
            FileHandler::move_file(*fixed_paths_it, move_to);
        }

        new_path = STAGING_DIR;
        fixed_paths_it++;
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