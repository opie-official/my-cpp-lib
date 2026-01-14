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

        Array &operator=(std::initializer_list<T>&cb);
        Array &operator=(const T (&other)[N]);
        Array&operator=(const Array&other);
        Array&operator=(Array&&other)noexcept;

        Option<T> operator[](size_t i);

        T * data() const override;

        [[nodiscard]] size_t length() const override;

        Iterator<T> begin() const override;

        Iterator<T> end() const override;

    };
}

#endif //OPIE_DECLARATIVE_LIB_ARRAY_H
