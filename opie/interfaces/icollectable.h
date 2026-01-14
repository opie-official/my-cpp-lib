//
// Created by Andryusha on 14.01.2026.
//

#ifndef OPIE_DECLARATIVE_LIB_ICOLLECTABLE_H
#define OPIE_DECLARATIVE_LIB_ICOLLECTABLE_H
#include "defines.h"

namespace opie {

    template<typename T>
    interface ICollect {
        virtual ~ICollect() = default;

        virtual T collect() const=0;
    };
}
#endif //OPIE_DECLARATIVE_LIB_ICOLLECTABLE_H