#include <memory>
#include <queue>
#include <vector>

#include "utils/print_utils.h"
#include "utils/string_utils.h"

class Main {
public:
    int* p;
    int  a = 888;
    int  b;

    Main() {
        print("construct");
        p    = new int(5);
        p[0] = 999;
        b    = 777;
    }

    ~Main() {
        delete p;
        print("destory");
    }
};

int main() {
    std::queue<Main*>  q;
    std::vector<Main*> vc;
    if (true) {
        Main* m = new Main();
        vc.push_back(m);
        q.push(m);
    }
    print("---");
    delete vc[0];
}