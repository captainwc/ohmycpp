#ifndef REDIS_WRAPPER_H
#define REDIS_WRAPPER_H

#include <hiredis/hiredis.h>

#include <iostream>
#include <string>

#include "db.h"
#include "log/log.h"

class RedisConnector : public Db {
public:
    // clang-format off
    RedisConnector() : RedisConnector(6379) {}
    explicit RedisConnector(int port) : RedisConnector("localhost", port) {}
    RedisConnector(const std::string& hostname, int port);
    ~RedisConnector() override;
    // clang-format on

    void execute(const std::string& command) override;
    void lpush(const std::string& listname, const std::string& value);
    void lpop(const std::string& listname);

    const std::string getReply() override;

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
        CONSOLE->error("connect to redis failed!");
        context_ = nullptr;
    }
    context_ = p;
    CONSOLE->info("connect to redis successfully!");
}

RedisConnector::~RedisConnector() {
    redisFree(context_);
    delete reply_;
    CONSOLE->info("unconnect to redis!");
}

void RedisConnector::execute(const std::string& command) {
    auto reply = static_cast<redisReply*>(redisCommand(context_, command.c_str()));
    if (reply == nullptr) {
        CONSOLE->error("command exectuation failed!");
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
    execute("LPUSH " + listname + " " + value);
}

void RedisConnector::lpop(const std::string& listname) {
    execute("LPOP " + listname);
}

#endif  // REDIS_WRAPPER_H