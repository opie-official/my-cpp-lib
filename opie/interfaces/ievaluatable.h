//
// Created by Andryusha on 14.01.2026.
//

#ifndef OPIE_DECLARATIVE_LIB_IEVALUATABLE_H
#define OPIE_DECLARATIVE_LIB_IEVALUATABLE_H
#include <functional>

#include "defines.h"
#include <stddef.h>

#include "types/option.h"

namespace opie {
    template<typename T, typename OUT>
    interface IEvaluatable {


        virtual OUT select(size_t from, size_t to)const=0;
        virtual void foreach(const std::function<void(const T&)>&cb)const=0;
        virtual void foreach(const std::function<void(const T&, size_t)>&cb)const=0;

        virtual OUT filter(const std::function<bool(const T&)>&cb)const=0;
        virtual OUT filter(const std::function<bool(const T&, size_t)>&cb)const=0;
        virtual T reduce(const std::function<T(const T&acc, const T&el)>&cb, const T&def=T{})const=0;
        virtual T reduce(const std::function<T(const T&acc, const T&el, size_t)>&cb, const T&def=T{})const=0;

        virtual Option<T> find(const T&el)const=0;
        virtual Option<T> find(const std::function<bool(const T&)>&cb)const=0;
        virtual Option<T> find(const std::function<bool(const T&, size_t)>&ecb)const=0;

        virtual bool contains(const T&el)const=0;
        virtual bool contains(const std::function<bool(const T&)>&cb)const=0;
        virtual bool contains(const std::function<bool(const T&, size_t)>&cb)const=0;

        virtual size_t count(const T&el)const=0;
        virtual size_t count(const std::function<bool(const T&)>&cb)const=0;
        virtual size_t count(const std::function<bool(const T&, size_t)>&cb)const=0;
    };
}



#endif //OPIE_DECLARATIVE_LIB_IEVALUATABLE_H