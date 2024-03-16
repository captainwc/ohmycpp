#ifndef OHMYCPP_OPTIONAL_H
#define OHMYCPP_OPTIONAL_H

#include <concepts>
#include <functional>
#include <optional>

namespace sk {
template <typename T>
class optional : public std::optional<T> {
public:
    // 使用基类的构造函数
    using std::optional<T>::optional;

    using opt_t = sk::optional<T>;

    static opt_t empty() {
        return opt_t();
    }

    static opt_t of(T value) {
        return opt_t(value);
    }

    static opt_t of_nullable(T value) {
        if (value == nullptr || value == std::nullopt) {
            return empty();
        } else {
            return opt_t(value);
        }
    }

    void if_present(std::function<void(T)> consumer) {
        if (this->has_value()) {
            consumer(this->value());
        }
    }

    template <typename R>
    opt_t map(std::function<R(T)> mapper) {
        if (this->has_value()) {
            return opt_t(mapper(this->value()));
        } else {
            return empty();
        }
    }

    template <typename R>
    sk::optional<R> flat_map(std::function<sk::optional<R>(T)> mapper) {
        if (this->has_value()) {
            return mapper(this->value());
        } else {
            return sk::optional<R>();
        }
    }

    T value_or_get(std::function<T()> supplier) {
        if (this->has_value()) {
            return this->value();
        } else {
            return supplier();
        }
    }
};

}  // namespace sk

#endif  // OHMYCPP_OPTIONAL_H
