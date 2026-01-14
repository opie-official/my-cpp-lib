//
// Created by Andryusha on 14.01.2026.
//

#ifndef OPIE_DECLARATIVE_LIB_IITERABLE_H
#define OPIE_DECLARATIVE_LIB_IITERABLE_H
#include "defines.h"
#include "collections/iterator.h"


namespace opie {

    template<typename T>
    interface IIterable {
        virtual ~IIterable() = default;
        virtual Iterator<T>begin()const=0;
        virtual Iterator<T>end()const =0;
    };
}


#endif //OPIE_DECLARATIVE_LIB_IITERABLE_H