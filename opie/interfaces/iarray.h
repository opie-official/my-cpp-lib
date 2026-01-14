//
// Created by Andryusha on 11.12.2025.
//

#ifndef OPIE_DECLARATIVE_LIB_IARRAY_H
#define OPIE_DECLARATIVE_LIB_IARRAY_H
#include "defines.h"
#include <cstddef>

namespace opie {
    template<typename T>
    interface IArray {
        virtual ~IArray() = default;

        virtual T*data()const=0;
        [[nodiscard]] virtual size_t length()const=0;

    };
}


#endif //OPIE_DECLARATIVE_LIB_IARRAY_H
