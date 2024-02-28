#include <iostream>
#include <memory>

#include "db/redis.h"

int main() {
    RedisConnector rd;
    rd.execute("DEL list1");
    rd.lpush("list1", "hello");
    rd.lpush("list1", "world");
    rd.lpop("list1");
    rd.lpush("list1", "winter");

    std::unique_ptr<Db> p = std::make_unique<RedisConnector>();
    p->execute("LRANGE list1 0 -1");
    std::cout << p->getReply() << std::endl;
}