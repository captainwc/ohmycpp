#include "algorithm/Utils.h"
#include "common.h"

using namespace std;

int main(int argc, char const *argv[]) {
    utils::log::log(utils::log::ERROR, "%s %d", "hello", 1);
    utils::log::log(utils::log::WARN, "%s %d", "hello", 1);
    utils::log::log(utils::log::DEBUG, "%s %d", "hello", 1);

    return 0;
}