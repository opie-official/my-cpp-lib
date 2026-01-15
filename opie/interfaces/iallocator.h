//
// Created by Andryusha on 12.12.2025.
//

#ifndef OPIE_DECLARATIVE_LIB_IALLOCATOR_H
#define OPIE_DECLARATIVE_LIB_IALLOCATOR_H
#include "defines.h"
#include <cstddef>

namespace opie {
    template<typename T>
    interface IAllocator {
        virtual ~IAllocator() = default;
        virtual T* alloc(size_t size)const =0;

        virtual void free(T*ptr)const=0;
    };
}


#endif //OPIE_DECLARATIVE_LIB_IALLOCATOR_H
