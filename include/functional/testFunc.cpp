#include <functional>
#include <iostream>

#include "optional.h"
using sk::optional;

template <typename T>
optional<T> getValue(T a) {
    if (a > 10) {
        return optional<T>::empty();
    } else {
        return optional<T>::of(a);
    }
}

int main() {
    int  a = 9;
    auto v = getValue(a);
    v.if_present([](int x) {
        printf("%d\n", x);
    });

    int y = getValue(v.value_or(12.1)).value_or_get([]() {
        return 999;
    });

    printf("%d\n", y);
}