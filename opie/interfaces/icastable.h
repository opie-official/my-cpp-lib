//
// Created by Andryusha on 14.01.2026.
//

#ifndef OPIE_DECLARATIVE_LIB_ICASTABLE_H
#define OPIE_DECLARATIVE_LIB_ICASTABLE_H
#include "defines.h"


namespace opie {

    template<typename T>
    interface ICastable {
        virtual ~ICastable() = default;

        virtual T cast()const=0;
    };
}

#endif //OPIE_DECLARATIVE_LIB_ICASTABLE_H