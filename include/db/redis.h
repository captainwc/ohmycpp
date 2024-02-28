#ifndef REDIS_WRAPPER_H
#define REDIS_WRAPPER_H

#include <hiredis/hiredis.h>

#include <iostream>
#include <string>

#include "db.h"

#define C_LOG 1

class RedisConnector : public Db {
public:
    // clang-format off
    RedisConnector() : RedisConnector(6379) {}
    RedisConnector(int port) : RedisConnector("localhost", port) {}
    RedisConnector(const std::string& hostname, int port);
    ~RedisConnector();
    // clang-format on

    void execute(const std::string& cmd);
    void lpush(const std::string& listname, const std::string& value);
    void lpop(const std::string& listname);

    const std::string getReply();

private:
    const std::string hostname_;
    int               port_;
    redisContext*     context_;
    redisReply*       reply_;
};

//==------------------implement------------------------==//
RedisConnector::RedisConnector(const std::string& hostname, int port)
    : hostname_(hostname), port_(port), reply_(nullptr) {
    auto p = redisConnect(hostname.c_str(), port);
    if (p == nullptr || p->err) {
#ifdef C_LOG
        std::cerr << "-- connect to redis failed!" << std::endl;
#endif
        context_ = nullptr;
    }
    context_ = p;
#ifdef C_LOG
    std::cout << "-- connect to redis successfully!" << std::endl;
#endif
}

RedisConnector::~RedisConnector() {
    redisFree(context_);
    delete reply_;
#ifdef C_LOG
    std::cout << "-- unconnect to redis!" << std::endl;
#endif
}

void RedisConnector::execute(const std::string& command) {
    redisReply* reply = static_cast<redisReply*>(redisCommand(context_, command.c_str()));
    if (reply == nullptr) {
#ifdef C_LOG
        std::cerr << "-- command exectuation failed!" << std::endl;
#endif
    }
    reply_ = reply;
}

const std::string RedisConnector::getReply() {
    if (reply_ == nullptr) {
        return "NIL";
    } else if (reply_->type == REDIS_REPLY_STRING) {
        return reply_->str;
    } else if (reply_->type == REDIS_REPLY_ARRAY) {
        std::string  ret;
        redisReply** p = reply_->element;
        for (int i = 0; i < reply_->elements; i++) {
            ret.append(p[i]->str).append(" ");
        }
        return ret;
    } else if (reply_->type == REDIS_REPLY_ERROR) {
        return "Error Occurred while executing the last command";
    } else {
        return "UnSupported Reply Type...";
    }
}

void RedisConnector::lpush(const std::string& listname, const std::string& value) {
    execute("LPUSH " + std::move(listname) + " " + std::move(value));
}

void RedisConnector::lpop(const std::string& listname) {
    execute("LPOP " + std::move(listname));
}

#endif  // REDIS_WRAPPER_H