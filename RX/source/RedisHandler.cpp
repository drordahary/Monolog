#include "../include/RedisHandler.h"

RedisHandler::RedisHandler()
{
}

RedisHandler::~RedisHandler()
{
    redisFree(context);
}

void RedisHandler::connect_to_redis()
{
    context = redisConnect(redis_settings::ip.c_str(), redis_settings::port);

    if (!context)
    {
        throw(ExceptionsHandler::bad_redis_connect());
    }
}

void RedisHandler::select_database(const int &database_id)
{
    query = "select " + std::to_string(database_id);
    reply = (redisReply *)redisCommand(context, query.c_str());

    if (!reply || context->err)
    {
        throw(ExceptionsHandler::bad_redis_reply());
    }

    freeReplyObject(reply);
}

std::vector<int> RedisHandler::get_channels_ids()
{
    query = "lrange channelsIDs 0 -1";
    reply = (redisReply *)redisCommand(context, query.c_str());

    if (!reply || context->err || reply->type == REDIS_REPLY_ERROR)
    {
        throw(ExceptionsHandler::bad_redis_reply());
    }

    std::vector<int> ids;

    for (int i = 0; i < reply->elements; i++)
    {
        ids.push_back(atoi(reply->element[i]->str));
    }

    freeReplyObject(reply);
    return ids;
}

int RedisHandler::get_channels_count()
{
    query = "get channelsCount";
    reply = (redisReply *)redisCommand(context, query.c_str());

    if (!reply || context->err || reply->type != REDIS_REPLY_STRING)
    {
        throw(ExceptionsHandler::bad_redis_reply());
    }

    int count = atoi(reply->str);
    freeReplyObject(reply);

    return count;
}

std::string RedisHandler::get_configuration(const int &channel_id, const std::string &field)
{
    query = "hmget channelID:" + std::to_string(channel_id) + " " + field;
    reply = (redisReply *)redisCommand(context, query.c_str());

    if (!reply || context->err)
    {
        throw(ExceptionsHandler::bad_redis_reply());
    }

    std::string configuration = reply->element[0]->str;
    freeReplyObject(reply);

    return configuration;
}

void RedisHandler::save_metadata(std::string &key, std::pair<std::string, std::string> &field)
{
    query = "hmset channelID:" + key;
    query += " fileID:" + field.first + " " + field.second;

    reply = (redisReply *)redisCommand(context, query.c_str());

    if (!reply || context->err)
    {
        throw(ExceptionsHandler::bad_redis_reply());
    }

    freeReplyObject(reply);
}

bool RedisHandler::file_exists(const int &channel_id, const int &file_id)
{
    query = "hexists channelID:" + std::to_string(channel_id);
    query += " fileID:" + std::to_string(file_id);

    reply = (redisReply *)redisCommand(context, query.c_str());

    if (!reply || context->err || reply->type == REDIS_REPLY_ERROR)
    {
        throw(ExceptionsHandler::bad_redis_reply());
    }

    if (reply->integer == 1)
    {
        freeReplyObject(reply);
        return true;
    }

    freeReplyObject(reply);
    return false;
}

std::string RedisHandler::get_file_path(const int &channel_id, const int &file_id)
{
    query = "hmget channelID:" + std::to_string(channel_id);
    query += " fileID:" + std::to_string(file_id);

    reply = (redisReply *)redisCommand(context, query.c_str());

    if (!reply || context->err || reply->type == REDIS_REPLY_ERROR)
    {
        throw(ExceptionsHandler::bad_redis_reply());
    }

    std::string metadata = reply->element[0]->str;
    std::string path = metadata.substr(0, metadata.find(':'));

    freeReplyObject(reply);
    return path;
}

int RedisHandler::get_file_size(const int &channel_id, const int &file_id)
{
    query = "hmget channelID:" + std::to_string(channel_id);
    query += " fileID:" + std::to_string(file_id);

    reply = (redisReply *)redisCommand(context, query.c_str());

    if (!reply || context->err || reply->type == REDIS_REPLY_ERROR)
    {
        throw(ExceptionsHandler::bad_redis_reply());
    }

    std::string metadata = reply->element[0]->str;
    int file_size = std::stoi(metadata.substr(metadata.find(':') + 1));

    freeReplyObject(reply);
    return file_size;
}

int RedisHandler::get_ntp_port()
{
    query = "get ntpSocketPort";

    reply = (redisReply *)redisCommand(context, query.c_str());

    if (reply == NULL || reply->type == REDIS_REPLY_ERROR)
    {
        throw(ExceptionsHandler::bad_redis_reply());
    }

    int ntp_socket_port = atoi(reply->str);

    freeReplyObject(reply);
    return ntp_socket_port;
}