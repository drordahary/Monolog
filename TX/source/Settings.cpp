#include "../include/Settings.h"

Settings::Settings()
{
    redis_handler.connect_to_redis();
    redis_handler.select_database(REDIS_DB_ID);
}

Settings::~Settings()
{
}

void Settings::set_logger()
{
    slog_init("logfile", SLOG_FLAGS_ALL, 1);

    SLogConfig slgCfg;

    slgCfg.eColorFormat = SLOG_COLOR_FULL;

    strncpy(slgCfg.sFileName, "logfile", 256);
    strncpy(slgCfg.sFilePath, "../logs/", 256);

    slgCfg.nTraceTid = 1;
    slgCfg.nToScreen = 0;
    slgCfg.nToFile = 1;
    slgCfg.nFlush = 0;
    slgCfg.nFlags = SLOG_FLAGS_ALL;

    slog_config_set(&slgCfg);

    slog_info("Successfully initialized the logger");
}

void Settings::fetch_configurations()
{
    int channels_count = redis_handler.get_channels_count();
    std::string configuration;

    std::vector<std::string> results;
    std::vector<std::vector<std::string>> all_channels_results;
    std::vector<std::string> fields =
        {
            "srcIP",
            "dstIP",
            "path",
            "portOffset",
            "portsPerChannel",
            "timesToSend",
            "bufferSize"};

    for (int i = 0; i < channels_count; i++)
    {
        for (int j = 0; j < fields.size(); j++)
        {
            configuration = redis_handler.get_configuration(i, fields.at(j));
            results.push_back(configuration);
        }

        all_channels_results.push_back(results);
        results.clear();
        organize_results(all_channels_results.at(i));
    }

    slog_info("Fetched all the results from Redis");
}

void Settings::organize_results(const std::vector<std::string> &results)
{
    channel_configurations configurations;

    configurations.source_ip = results[0];
    configurations.destination_ip = results[1];
    configurations.channel_directory = results[2];
    configurations.port_offset = std::stoi(results[3]);
    configurations.ports_per_channel = std::stoi(results[4]);
    configurations.times_to_send = std::stoi(results[5]);
    configurations.buffer_size = std::stoi(results[6]);

    channels.push_back(configurations);
}