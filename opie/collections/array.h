//
// Created by Andryusha on 14.01.2026.
//

#ifndef OPIE_DECLARATIVE_LIB_ARRAY_H
#define OPIE_DECLARATIVE_LIB_ARRAY_H
#include <array>
#include <initializer_list>
#include <stddef.h>

#include "iterator.h"
#include "interfaces/iarray.h"
#include "interfaces/iiterable.h"
#include "types/option.h"

namespace opie {
    template<typename T, size_t N>
    class Array: public IArray<T>, public IIterable<T> {
        T _data[N];
    public:
        Array() = default;

        Array(const std::initializer_list<T> &init);

        Array(const T (&other)[N]);

        Array(const Array &other);

        Array(Array &&other) noexcept;

        ~Array() override= default;

        Array &operator=(std::initializer_list<T>&init);
        Array &operator=(const T (&other)[N]);
        Array&operator=(const Array&other);
        Array&operator=(Array&&other)noexcept;

        Option<T> operator[](size_t i);

        T * data() const override;

        [[nodiscard]] size_t length() const override;

        Iterator<T> begin() const override;

        Iterator<T> end() const override;


    };

    template<typename T, size_t N>
    Array<T, N>::Array(const std::initializer_list<T> &init) {
        if (N<=init.size()) {
            auto ptr = init.begin();
            for (size_t i=0;i<N;i++) {
                _data[i]=*(ptr+i);
            }
        }else {
            auto ptr = init.begin();
            for (size_t i=0;i<init.size();i++) {
                _data[i]=*(ptr+i);
            }
        }
    }

    template<typename T, size_t N>
    Array<T, N>::Array(const T(&other)[N]) {
        for (size_t i=0;i<N;i++) {
            _data[i]=other[i];
        }
    }

    template<typename T, size_t N>
    Array<T, N>::Array(const Array &other) {
        for (size_t i=0;i<N;i++) {
            _data[i]=other._data[i];
        }
    }

    template<typename T, size_t N>
    Array<T, N>::Array(Array &&other) noexcept {
        for (size_t i=0;i<N;i++) {
            _data[i]=std::move(other._data[i]);
        }
    }

    template<typename T, size_t N>
    Array<T, N> & Array<T, N>::operator=(std::initializer_list<T> &init) {
        if (N<=init.size()) {
            auto ptr = init.begin();
            for (size_t i=0;i<N;i++) {
                _data[i]=*(ptr+i);
            }
        }else {
            auto ptr = init.begin();
            for (size_t i=0;i<init.size();i++) {
                _data[i]=*(ptr+i);
            }
        }
        return *this;
    }

    template<typename T, size_t N>
    Array<T, N> & Array<T, N>::operator=(const T(&other)[N]) {
        for (size_t i=0;i<N;i++) {
            _data[i]=other[i];
        }
        return *this;
    }

    template<typename T, size_t N>
    Array<T, N> & Array<T, N>::operator=(const Array &other) {
        for (size_t i=0;i<N;i++) {
            _data[i]=other._data[i];
        }
        return*this;
    }

    template<typename T, size_t N>
    Array<T, N> & Array<T, N>::operator=(Array &&other) noexcept {
        for (size_t i=0;i<N;i++) {
            _data[i]=std::move(other._data[i]);
        }
        return*this;
    }

    template<typename T, size_t N>
    Option<T> Array<T, N>::operator[](size_t i) {
        if (i<N) {
            return _data[i];
        }
        return none;
    }

    template<typename T, size_t N>
    T * Array<T, N>::data() const {
        return _data;
    }

    template<typename T, size_t N>
    size_t Array<T, N>::length() const {
        return N;
    }

    template<typename T, size_t N>
    Iterator<T> Array<T, N>::begin() const {
        return Iterator<T>{_data, N+1, 0};
    }

    template<typename T, size_t N>
    Iterator<T> Array<T, N>::end() const {
        return Iterator<T>{_data, N+1, N};
    }
}

#endif //OPIE_DECLARATIVE_LIB_ARRAY_H
