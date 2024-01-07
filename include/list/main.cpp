#include <algorithm>

#include "ListNode.h"
#include "algorithm/Utils.h"

int main() {
    auto list = utils::list::getLinkList("1,3,2,4,5");
    utils::printer::printLinkList(list);
    auto it = list.begin();

    std::cout << (*it).val << std::endl;
    it++;
    std::cout << (*(++it)).val << std::endl;

    for (auto it = list.begin(); it != list.end(); it++) {
        std::cout << (*it).val << std::endl;
    }
}