#ifndef OHMYCPP_OPT_WRAPPER_H
#define OHMYCPP_OPT_WRAPPER_H

#include <functional>
#include <optional>

namespace sk {
template <typename T>
class opt_wrapper {
private:
    std::optional<T> opt_;

public:
    explicit opt_wrapper(T&& elem) {
        opt_ = std::make_optional<T>(std::forward<T>(elem));
    }

    explicit opt_wrapper(std::optional<T>& opt) : opt_(opt) {
    }

    explicit opt_wrapper(std::optional<T>&& opt) : opt_(opt) {
    }

    auto value() {
        return opt_.value();
    }

    auto value_or(T&& t) {
        return opt_.value_or(t);
    }

    constexpr bool has_value() {
        return opt_.has_value();
    }

    template <typename Consumer>
        requires std::invocable<Consumer, T> && std::same_as<void, std::invoke_result_t<Consumer, T>>
    void if_present(Consumer&& consumer) {
        if (has_value()) {
            return std::invoke(consumer, this->value());
        }
    }
};

}  // namespace sk

#endif  // OHMYCPP_OPT_WRAPPER_H
