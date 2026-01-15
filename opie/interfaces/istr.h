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
        virtual std::string toString(const std::string&sep)const=0;
        virtual std::string toStringOut()const=0;
    };

    std::ostream &operator<<(std::ostream&os, IStr&str) {
        os<<str.toStringOut();
        return os;
    }
}


#endif //OPIE_DECLARATIVE_LIB_ISTR_H