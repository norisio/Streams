#ifndef UTILITY_H
#define UTILITY_H

#include <iostream>
#include <tuple>

template<typename T>
std::unique_ptr<T> move_unique(T&& t) {
    return std::make_unique<T>(std::move(t));
}

template<typename Transform, typename... Arg> using ReturnType =
    decltype(std::declval<Transform>()(std::declval<Arg>()...));


template<size_t index, size_t last, typename... Args> struct PrintTuple;

template<typename... Args>
std::ostream& operator<< (std::ostream& os, const std::tuple<Args...>& tuple) {
    PrintTuple<0, std::tuple_size<std::tuple<Args...>>::value - 1, Args...>::print(os, tuple);
    return os;
}

template<size_t index, size_t last, typename... Args>
struct PrintTuple {
    static void print(std::ostream& os, const std::tuple<Args...>& tuple) {
        os << std::get<index>(tuple) << ", ";
        PrintTuple<index + 1, last, Args...>::print(os, tuple);
    }
};

template<size_t last, typename... Args>
struct PrintTuple<0, last, Args...> {
    static void print(std::ostream& os, const std::tuple<Args...>& tuple) {
        os << "(" << std::get<0>(tuple) << ", ";
        PrintTuple<1, last, Args...>::print(os, tuple);
    }
};

template<size_t index, typename... Args>
struct PrintTuple<index, index, Args...> {
    static void print(std::ostream& os, const std::tuple<Args...>& tuple) {
        os << std::get<index>(tuple) << ")";
    }
};



#endif