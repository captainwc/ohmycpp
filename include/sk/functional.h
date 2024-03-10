#ifndef OHMYCPP_FUNCTIONAL_H
#define OHMYCPP_FUNCTIONAL_H

#include <concepts>
#include <functional>

namespace sk {

template <typename Fn, typename Arg>
concept Consumer = std::is_invocable_v<Fn, Arg> && std::same_as<void, std::invoke_result_t<Fn, Arg>>;

template <typename Fn, typename Rt, typename Arg>
concept UnaryFunction = std::is_invocable_v<Fn, Arg> && std::same_as<Rt, std::invoke_result<Fn, Arg>>;

// demo usage
template <typename Fn, typename Rt, typename Arg>
    requires UnaryFunction<Fn, Rt, Arg>
Rt foo(Fn fn, Arg arg) {
    return std::invoke(fn, arg);
}

}  // namespace sk

#endif  // OHMYCPP_FUNCTIONAL_H
