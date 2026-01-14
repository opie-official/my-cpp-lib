//
// Created by Andryusha on 14.01.2026.
//

#ifndef OPIE_DECLARATIVE_LIB_ISTR_H
#define OPIE_DECLARATIVE_LIB_ISTR_H
#include <string>

#include "defines.h"


namespace opie {

    interface IStr {
        virtual ~IStr() = default;
        virtual std::string toString()const=0;
    };
}


#endif //OPIE_DECLARATIVE_LIB_ISTR_H