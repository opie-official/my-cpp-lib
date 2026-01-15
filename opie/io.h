//
// Created by Andryusha on 15.01.2026.
//

#ifndef OPIE_DECLARATIVE_LIB_IO_H
#define OPIE_DECLARATIVE_LIB_IO_H
#include <iostream>


namespace opie::io {
    inline void print() {
    }

    template<typename T>
    void print(const T &el) {
        std::cout << el;
    }

    inline void print(const std::string &el) {
        std::cout << el;
    }

    template<typename T, typename... Args>
    void print(const T &el, const Args &... args) {
        print(el);
        std::cout << " ";
        print(args...);
    }

    template<typename T>
    void print(T &el) {
        std::cout << el;
    }


    template<typename T, typename... Args>
    void print(T &el, Args &... args) {
        print(el);
        std::cout << " ";
        print(args...);
    }

    inline void println() {
        std::cout << std::endl;
    }

    template<typename T, typename... Args>
    void println(const T &el, const Args &... args) {
        print(el);
        std::cout << " ";
        print(args...);
        std::cout << std::endl;
    }

    template<typename T>
    void println(const T &el) {
        std::cout << el << std::endl;
    }

    template<typename T, typename... Args>
    void println(T &el, Args &... args) {
        print(el);
        std::cout << " ";
        print(args...);
        std::cout << std::endl;
    }

    template<typename T>
    void println(T &el) {
        std::cout << el << std::endl;
    }
}

#endif //OPIE_DECLARATIVE_LIB_IO_H
