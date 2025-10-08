#ifndef __IOMANIP_HPP__
#define __IOMANIP_HPP__

#include <iostream>
#include <type_traits>
#include <utility>
#include <cmath>
#include <string>

namespace ioex {

//======================== endm ========================
inline std::ostream& endm(std::ostream& os) {
    os << "[eol]\n";
    return os;
}

//========================= sin ========================
struct sin_t { };
inline constexpr sin_t sin{};

struct sin_proxy {
    std::ostream& os;

    template <class T,
              std::enable_if_t<std::is_arithmetic_v<T>, int> = 0>
    std::ostream& operator<<(const T& value) {
        const double r = std::sin(static_cast<double>(value));
        if (r == 0.0) {
            os << "0.0";      // требование: 0 -> 0.0
        } else {
            os << r;
        }
        return os;
    }

    template <class T,
              std::enable_if_t<!std::is_arithmetic_v<T>, int> = 0>
    std::ostream& operator<<(const T& value) {
        os << "sin(" << value << ")";
        return os;
    }

    std::ostream& operator<<(const char* s) {
        os << "sin(" << s << ")";
        return os;
    }
};

inline sin_proxy operator<<(std::ostream& os, sin_t) {
    return sin_proxy{os};
}

//========================= add ========================
struct add_t { };
inline constexpr add_t add{};

struct add_proxy0 {
    std::ostream& os;

    template <class A>
    struct add_proxy1 {
        std::ostream& os_;
        A a_;
        template <class B>
        std::ostream& operator<<(const B& b) {
            os_ << (a_ + b);
            return os_;
        }
    };

    template <class T>
    add_proxy1<std::decay_t<T>> operator<<(T&& a) {
        return add_proxy1<std::decay_t<T>>{os, std::forward<T>(a)};
    }
};

inline add_proxy0 operator<<(std::ostream& os, add_t) {
    return add_proxy0{os};
}

} // namespace ioex

#endif // __IOMANIP_HPP__
