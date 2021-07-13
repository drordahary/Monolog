#include "../include/MetadataWorker.h"

MetadataWorker::MetadataWorker(UntrackedWorkerPool *untracked_pool)
{
    this->untracked_pool = untracked_pool;

    redis_handler.connect_to_redis();
    redis_handler.select_database(REDIS_RX_DB);
}

MetadataWorker::~MetadataWorker()
{
}

void MetadataWorker::start_working(std::string data, const int &buffer_size)
{
    organize_metadata(data);
    save_metadata_to_redis();

    std::string file_path = std::string(FILES_DIR) + current_metadata.path;
    std::string untracked_file_path = std::string(UNTRACKED_DIR);
    untracked_file_path += std::to_string(current_metadata.channel_id);
    untracked_file_path += std::to_string(current_metadata.file_id);

    if (untracked_file_exists(untracked_file_path))
    {
        slog_trace("exists");
        std::string untracked_data = std::to_string(current_metadata.channel_id) + ",";
        untracked_data += std::to_string(current_metadata.file_id) + ",";
        untracked_data += std::to_string(current_metadata.file_size) + ",";
        untracked_data += std::to_string(buffer_size) + ",";
        untracked_data += file_path;

        DirectoryOrganizer::produce_structure(file_path);
        untracked_pool->add_job(untracked_data);
    }
}

void MetadataWorker::organize_metadata(std::string &metadata)
{
    std::stringstream metadata_stream(metadata);
    std::vector<std::string> result;
    std::string segment;

    while (std::getline(metadata_stream, segment, ','))
    {
        result.push_back(segment);
    }

    current_metadata.channel_id = std::stoi(result[0]);
    current_metadata.file_id = std::stoi(result[1]);
    current_metadata.path = result[2];
    current_metadata.file_size = std::stoi(result[3]);
}

void MetadataWorker::save_metadata_to_redis()
{
    std::string key = std::to_string(current_metadata.channel_id);
    std::pair<std::string, std::string> field;

    field.first = std::to_string(current_metadata.file_id);
    field.second = current_metadata.path + ":" +
                   std::to_string(current_metadata.file_size);

    redis_handler.save_metadata(key, field);
}

bool MetadataWorker::untracked_file_exists(const std::string &path)
{
    return access(path.c_str(), F_OK) == 0;
}