#ifndef __IOMANIP_HPP__
#define __IOMANIP_HPP__

#include <iostream>
#include <type_traits>
#include <utility>
#include <cmath>
#include <string>

// ===== endm =====
inline std::ostream& endm(std::ostream& os) {
    os << "[eol]\n";
    return os;
}

// ===== sine (одиночный операнд) =====
struct sine_t { };
inline constexpr sine_t sine{};

struct sine_proxy {
    std::ostream& os;

    template <class T>
    std::ostream& operator<<(T&& v) {
        using D = std::decay_t<T>;    // избавляемся от сслыки
        if constexpr (std::is_arithmetic_v<D>) { // 
            const double r = std::sin(static_cast<double>(v));
            if (r == 0.0) os << "0.0";
            else          os << r;
        } else {
            os << "sine(" << std::forward<T>(v) << ")";
        }
        return os;
    }
};

inline sine_proxy operator<<(std::ostream& os, sine_t) { return { os }; }

// ===== add (два операнда) =====
struct add_t { };
inline constexpr add_t add{};

struct add_proxy0 {
    std::ostream& os;

    template <class A>
    struct add_proxy1 {
        std::ostream& os_;
        A a_;
        template <class B>
        std::ostream& operator<<(B&& b) {
            os_ << (a_ + std::forward<B>(b));
            return os_;
        }
    };

    template <class T>
    add_proxy1<std::decay_t<T>> operator<<(T&& a) {
        return { os, std::forward<T>(a) };
    }
};

inline add_proxy0 operator<<(std::ostream& os, add_t) { return { os }; }

#endif // __IOMANIP_HPP__
