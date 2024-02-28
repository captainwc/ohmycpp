#include <iostream>

#include "db/redis.h"

int main() {
    RedisConnector rd;
    rd.execute("DEL list1");
    rd.lpush("list1", "hello");
    rd.lpush("list1", "world");
    rd.lpop("list1");
    rd.lpush("list1", "winter");

    rd.execute("LRANGE list1 0 -1");
    std::cout << rd.getReply() << std::endl;
}