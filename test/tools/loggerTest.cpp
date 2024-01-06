#include "algorithm/Utils.h"
#include "common.h"

using namespace std;

int main(int argc, char const *argv[]) {
    utils::log::logWithPos(utils::log::ERROR, __FILE__, __FUNCTION__, __LINE__, "%s %d", "hello", 1);
    LOG(utils::log::WARN, "%s %d", "hello", 1);
    ERROR("%s %d", "hello", 2);
    WARN("%s %d", "hello", 2);
    DEBUG("%s %d", "hello", 2);
    // utils::log::log(utils::log::DEBUG, "%s %d", "hello", 1);

    return 0;
}