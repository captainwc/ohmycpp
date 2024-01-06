#include "common.h"

int main() {
    int total = 1111;
    for (int i = 1; i <= total; i++) {
        utils::progressBar(i, total, "TEST");
        usleep(5000);
        if (i % 100 == 0) {
            printf("hello %d\n", i);
        }
    }
    printf("\n");
    return 0;
}
