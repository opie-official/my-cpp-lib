//
// Created by Andryusha on 12.12.2025.
//

#ifndef OPIE_DECLARATIVE_LIB_ITERATOR_H
#define OPIE_DECLARATIVE_LIB_ITERATOR_H
#include <cstddef>

#include "interfaces/iarray.h"

namespace opie {


    template<typename T>
    class Iterator {
        T*data=nullptr;
        size_t size=0;
        size_t start=0;

    public:
        Iterator(IArray<T>&arr) {
            data = arr.data();
            size = arr.length();
        }
        Iterator(T*dat, size_t siz, size_t st) {
            data = dat;
            size = siz;
            start = st;
        }


        T&operator*()const {
            return data[start];
        }

        Iterator&operator++() {
            start++;
            return *this;
        }

        T&operator[](size_t i) {
            return data[i];
        }
        bool operator==(Iterator&other) {
            return data==other.data && size==other.size && other.start==start;
        }
    };
}

#endif //OPIE_DECLARATIVE_LIB_ITERATOR_H