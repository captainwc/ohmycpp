#include "lc.h"

int main() {
    auto list = getList("1,2, 3 ,4, 5");
    auto str  = list2string(list.get());
    std::cout << str << std::endl;
};
