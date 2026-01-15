//
// Created by Andryusha on 14.01.2026.
//

#ifndef OPIE_DECLARATIVE_LIB_INDEXABLE_H
#define OPIE_DECLARATIVE_LIB_INDEXABLE_H
#include "defines.h"
#include "types/option.h"

namespace opie {
    template<typename T>
    interface IIndexable {
        virtual ~IIndexable() = default;

        virtual Option<const T&>operator[](size_t i) const noexcept=0;
        virtual Option<T&>operator[](size_t i) noexcept=0;
    };
}



#endif //OPIE_DECLARATIVE_LIB_INDEXABLE_H