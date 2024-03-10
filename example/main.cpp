#include <concepts>
#include <functional>
#include <iostream>

template <typename Fn, typename Rt, typename Arg>
concept UnaryFunction = std::is_invocable_v<Fn, Arg> && std::same_as<Rt, std::invoke_result_t<Fn, Arg>>;

template <typename Fn, typename Rt, typename Arg>
    requires UnaryFunction<Fn, Rt, Arg>
Rt foo(Fn fn, Arg arg) {
    return std::invoke(fn, arg);
}

int main() {
    std::function<int(int)> f = [](int x) {
        return x * x;
    };

    int x = foo<std::function<int(int)>, int>(f, 12);
    int y = foo<std::function<int(int)>, int, int>(f, 13);

    std::cout << x << y << std::endl;
}