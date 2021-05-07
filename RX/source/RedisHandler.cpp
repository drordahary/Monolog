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