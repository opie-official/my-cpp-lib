//
// Created by Andryusha on 12.12.2025.
//

#ifndef OPIE_DECLARATIVE_LIB_ALLOCATOR_H
#define OPIE_DECLARATIVE_LIB_ALLOCATOR_H
#include "interfaces/iallocator.h"


namespace opie {
    template<typename T>
    class Allocator: IAllocator<T> {
    public:
        Allocator()=default;

        T * alloc(size_t size) const override {
            return new T[size];
        }

        void free(T *ptr) const override {
            delete[] ptr;
        }
    };
}


#endif //OPIE_DECLARATIVE_LIB_ALLOCATOR_H