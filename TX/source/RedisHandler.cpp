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

void RedisHandler::save_metadata(const std::string &key, const std::pair<std::string, std::string> &field)
{
    std::string channel_key = "channelID:" + key;

    if (!key_hash_exists(channel_key))
    {
        handle_new_channel_hash(channel_key);
    }

    reply = (redisReply *)redisCommand(context, "hmset channelID:%s fileID:%s %s",
                                       key.c_str(), field.first.c_str(), field.second.c_str());

    if (!reply || context->err)
    {
        throw(ExceptionsHandler::bad_redis_reply());
    }

    freeReplyObject(reply);
    increment_file_id(channel_key);
}

bool RedisHandler::key_hash_exists(const std::string &key)
{
    query = "hgetall " + key;
    reply = (redisReply *)redisCommand(context, query.c_str());

    if (reply->type == REDIS_REPLY_ERROR)
    {
        throw(ExceptionsHandler::bad_redis_reply());
    }

    if (reply->type == REDIS_REPLY_ARRAY && reply->elements == 0)
    {
        freeReplyObject(reply);
        return false;
    }

    freeReplyObject(reply);
    return true;
}

int RedisHandler::get_last_file_id(const std::string &key)
{
    query = "hmget " + key + " lastFileID";
    reply = (redisReply *)redisCommand(context, query.c_str());

    if (!reply || context->err)
    {
        throw(ExceptionsHandler::bad_redis_reply());
    }

    int file_id = atoi(reply->element[0]->str);

    freeReplyObject(reply);
    return file_id;
}

void RedisHandler::handle_new_channel_hash(const std::string &key)
{
    query = "hmset " + key;
    query += " lastFileID 0";

    reply = (redisReply *)redisCommand(context, query.c_str());

    if (reply == NULL || reply->type == REDIS_REPLY_ERROR)
    {
        throw(ExceptionsHandler::bad_redis_reply());
    }

    freeReplyObject(reply);
}

void RedisHandler::increment_file_id(const std::string &key)
{
    query = "hincrby " + key + " lastFileID 1";

    reply = (redisReply *)redisCommand(context, query.c_str());

    if (reply == NULL || reply->type == REDIS_REPLY_ERROR)
    {
        throw(ExceptionsHandler::bad_redis_reply());
    }

    freeReplyObject(reply);
}

std::string RedisHandler::get_ntp_ip()
{
    query = "get ntpSocketIP";

    reply = (redisReply *)redisCommand(context, query.c_str());

    if (reply == NULL || reply->type == REDIS_REPLY_ERROR)
    {
        throw(ExceptionsHandler::bad_redis_reply());
    }

    std::string ntp_socket_ip = reply->str;

    freeReplyObject(reply);
    return ntp_socket_ip;
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