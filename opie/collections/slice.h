//
// Created by Andryusha on 12.12.2025.
//

#ifndef OPIE_DECLARATIVE_LIB_SLICE_H
#define OPIE_DECLARATIVE_LIB_SLICE_H
#include <stddef.h>

#include "interfaces/iarray.h"
#include "interfaces/iiterable.h"
#include "types/option.h"


namespace opie {
    template<typename T>
    class Slice: public IIterable<T>{
        T *data = nullptr;
        size_t size = 0;
        size_t start = 0;

    public:
        Slice(IArray<T> &arr) {
            data = arr.data();
            size = arr.length();
        }

        Slice(T *dat, size_t _size, size_t _start = 0) {
            data = dat;
            size = _size;
            start = _start;
        }

        template<size_t N>
        Slice(T (&dat)[N]) {
            data = dat;
            size = N;
        }

        Slice(const Slice&)=delete;

        Option<T> operator[](size_t i) {
            if (i + start < size) {
                return data[i + start];
            }
            return none;
        }

        T *getData() const {
            return data;
        }

        size_t length() const {
            return size;
        }

        size_t getStart() const {
            return start;
        }

        Iterator<T> begin() const override{
            return Iterator<T>{data, size + 1, start};
        }

        Iterator<T> end() const override{
            return Iterator<T>{data, size + 1, size};
        }
    };
}


#endif //OPIE_DECLARATIVE_LIB_SLICE_H
