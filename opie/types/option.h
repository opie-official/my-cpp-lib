//
// Created by Andryusha on 11.12.2025.
//

#ifndef OPIE_DECLARATIVE_LIB_OPTION_H
#define OPIE_DECLARATIVE_LIB_OPTION_H
#include <algorithm>
#include <cstdlib>


namespace opie {
    class NoneValue final {
    public:
        NoneValue() = default;
    };

    inline constexpr NoneValue none;


    template<typename T>
    class Option {
        union {
            T val;
        };

        bool has = false;

    public:
        Option() = default;

        Option(const NoneValue &_) {
        }

        Option(const T &el) {
            new(&val) T{el};
            has = true;
        }

        ~Option() = default;

        Option(const Option &other) {
            if (other.hasValue()) {
                new(&val) T{other.unwrap()};
            }
        }

        Option(Option &&other) noexcept {
            has = std::move(other.val);
            if (other.hasValue()) {
                new(&val) T{std::move(other.unwrap())};
            }
        }

        [[nodiscard]] bool hasValue() const {
            return has;
        }

        T &unwrap() const {
            if (has) {
                return val;
            }
#ifdef OPTION_ABORT
            std::abort();
#else
            std::exit(1);
#endif
        }

        operator T() const {
            return unwrap();
        }


        void unwrap(T *&ptr) const {
            if (has) {
                ptr = &val;
            } else {
                ptr = nullptr;
            }
        }
    };


    template<typename T>
    class Option<T &> {
        T *val = nullptr;

    public:
        Option() = default;

        Option(const NoneValue &_) {
        }

        Option(const T &el) {
            val = &el;
        }

        ~Option() = default;

        Option(const Option &other) {
            val = other.val;
        }

        Option(Option &&other) noexcept {
            val = other.val;
        }

        [[nodiscard]] bool hasValue() const {
            return val != nullptr;
        }

        [[nodiscard]] T &unwrap() const {
            if (val != nullptr) {
                return *val;
            }
#ifdef OPTION_ABORT
            std::abort();
#else
            std::exit(1);
#endif
        }

        void unwrap(T *&ptr) const {
            ptr = val;
        }
    };

    template<typename T>
    Option<T> Some(const T &el) {
        return Option<T>{el};
    }

    template<typename T>
    Option<T> None() {
        return Option<T>{};
    }
}


#endif //OPIE_DECLARATIVE_LIB_OPTION_H
