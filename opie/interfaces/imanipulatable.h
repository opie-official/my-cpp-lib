//
// Created by Andryusha on 14.01.2026.
//

#ifndef OPIE_DECLARATIVE_LIB_IMANIPULATABLE_H
#define OPIE_DECLARATIVE_LIB_IMANIPULATABLE_H
#include "defines.h"
#include "iarray.h"


namespace opie {
    template<typename FOR, typename T, typename ARRAY>
    interface IManipulatable {
        virtual ~IManipulatable() = default;

        virtual FOR &append(const T &el) =0;

        virtual FOR &appendRange(const ARRAY &arr) =0;

        virtual FOR &removeFirst(const T &el) =0;

        virtual FOR &removeLast(const T &el) =0;

        virtual FOR &removeAll(const T &el) =0;

        virtual FOR &removeByIndex(size_t i) =0;

        virtual FOR &insert(const T &el, size_t i) =0;

        virtual FOR &insertRange(const ARRAY &arr, size_t i) =0;
    };
}


#endif //OPIE_DECLARATIVE_LIB_IMANIPULATABLE_H
