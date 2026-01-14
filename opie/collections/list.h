//
// Created by Andryusha on 11.12.2025.
//

#ifndef OPIE_DECLARATIVE_LIB_LIST_H
#define OPIE_DECLARATIVE_LIB_LIST_H
#include <functional>
#include <initializer_list>
#include <string>
#include <iostream>

#include "iterator.h"
#include "interfaces/iallocator.h"
#include "interfaces/iarray.h"
#include "interfaces/iiterable.h"
#include "types/allocator.h"
#include "types/option.h"


namespace opie {
    template<typename T, typename Alloc=Allocator<T> >
        requires std::is_base_of_v<IAllocator<T>, Alloc>
    class List : public IArray<T>, public IIterable<T> {
        T *_data = nullptr;
        size_t _size = 0;
        size_t _cap = 2;
        Alloc alloc;

        using init_ = std::initializer_list<T>;

    public:
        List() = default;

        List(const init_ &init);

        List(size_t cap);

        List(const List &other);

        List(List &&other) noexcept;

        List &operator=(const init_ &init);

        List &operator=(const List &other);

        List &operator=(List &&other) noexcept;

        Option<T &> operator[](size_t i) const;

        void set(const T &elem, size_t i);

        [[nodiscard]] T *data() const override;

        [[nodiscard]] size_t length() const override;

        [[nodiscard]] size_t capacity() const;


        List &append(const T &el);

        List &appendRange(const List<T> &el);

        List &insert(const T &elem, size_t i);

        List &insertRange(const List<T> &elem, size_t i);

        List &removeFirst(const T &elem);

        List &removeAll(const T &elem);

        List &removeByIndex(size_t i);

        List &removeFromTo(size_t start, size_t end);

        List &shrink(size_t divisor = 2);

        List &clear();

        List filter(const std::function<bool(const T &)> &cb) const;

        List filter(const std::function<bool(const T &, size_t)> &cb) const;

        Iterator<T> begin()const override;
        Iterator<T> end()const override;



        template<typename M>
        List<M> map(const std::function<M(const T &)> &cb) const {
            List<M> res(_cap);
            for (size_t i = 0; i < _size; i++) {
                res.set(cb(_data[i]), i);
            }
            return res;
        }

        template<typename M>
        List<M> map(const std::function<M(const T &, size_t)> &cb) const {
            List<M> res(_cap);
            for (size_t i = 0; i < _size; i++) {
                res.set(cb(_data[i], i));
            }
            return res;
        }

        template<typename M=T>
        M reduce(const std::function<M(const M &acc, const T &elem)> &cb) const {
            M res;
            for (size_t i = 0; i < _size; i++) {
                res = cb(res, _data[i]);
            }
            return res;
        }

        template<typename M=T>
        M reduce(const std::function<M(const M &acc, const T &elem, size_t i)> &cb) const {
            M res;
            for (size_t i = 0; i < _size; i++) {
                res = cb(res, _data[i], i);
            }
            return res;
        }

        List &filterSelf(const std::function<bool(const T &)> &cb);

        List &filterSelf(const std::function<bool(const T &, size_t)> &cb);

        List &mapSelf(const std::function<T(const T &)> &cb);

        List &mapSelf(const std::function<T(const T &, size_t)> &cb);

        Option<T &> findFirst(const std::function<bool(const T &)> &cb) const;

        Option<T &> findFirst(const std::function<bool(const T &, size_t)> &cb) const;

        Option<T &> findLast(const std::function<bool(const T &)> &cb) const;

        Option<T &> findLast(const std::function<bool(const T &, size_t)> &cb) const;

        List<T> select(size_t start, ssize_t end = -1) const;

        List<T> selectRight(size_t start, ssize_t end = -1) const;


        void foreach(const std::function<void(const T &)> &cb) const;

        void foreach(const std::function<void(const T &, size_t)> &cb) const;

        void foreach(const std::function<bool(const T &)> &cb) const;

        void foreach(const std::function<bool(const T &, size_t)> &cb) const;


        List<T> reverse() const;

        List &reverseSelf();

        bool contains(const T &elem) const;

        bool contains(const std::function<bool(const T &)> &cb) const;

        bool contains(const std::function<bool(const T &, size_t)> &cb) const;

        size_t count(const T &elem) const;

        size_t count(const std::function<bool(const T &)> &cb) const;

        size_t count(const std::function<bool(const T &, size_t)> &cb) const;

        [[nodiscard]] std::string toString() const;
    };


    template<typename T, typename Alloc> requires std::is_base_of_v<IAllocator<T>, Alloc>
    List<T, Alloc>::List(const init_ &init) {
        _cap = init.size() % 2 == 0 ? init.size() : init.size() + 1;
        _data = alloc.alloc(_cap);
        for (auto it = init.begin(); it < init.end(); ++it) {
            _data[_size++] = *it;
        }
    }

    template<typename T, typename Alloc> requires std::is_base_of_v<IAllocator<T>, Alloc>
    List<T, Alloc>::List(const size_t cap) {
        _cap = cap;
        _data = alloc.alloc(_cap);
    }

    template<typename T, typename Alloc> requires std::is_base_of_v<IAllocator<T>, Alloc>
    List<T, Alloc>::List(const List &other) {
        _cap = other._cap;
        _size = other._size;
        _data = alloc.alloc(_cap);
        if (_size > 0) {
            for (size_t i = 0; i < _size; i++) {
                _data[i] = other._data[i];
            }
        }
    }

    template<typename T, typename Alloc> requires std::is_base_of_v<IAllocator<T>, Alloc>
    List<T, Alloc>::List(List &&other) noexcept {
        _cap = std::move(other._cap);
        _size = std::move(other._size);
        _data = other._data;
        other._data = nullptr;
    }

    template<typename T, typename Alloc> requires std::is_base_of_v<IAllocator<T>, Alloc>
    List<T, Alloc> &List<T, Alloc>::operator=(const init_ &init) {
        alloc.free(_data);
        _cap = init.size() % 2 == 0 ? init.size() : init.size() + 1;
        _data = alloc.alloc(_cap);
        for (auto it = init.begin(); it < init.end(); ++it) {
            _data[_size++] = *it;
        }
        return *this;
    }

    template<typename T, typename Alloc> requires std::is_base_of_v<IAllocator<T>, Alloc>
    List<T, Alloc> &List<T, Alloc>::operator=(const List &other) {
        if (this != &other) {
            alloc.free(_data);
            _cap = other._cap;
            _size = other._size;
            _data = alloc.alloc(_cap);
            if (_size > 0) {
                for (size_t i = 0; i < _size; i++) {
                    _data[i] = other._data[i];
                }
            }
        }
        return *this;
    }

    template<typename T, typename Alloc> requires std::is_base_of_v<IAllocator<T>, Alloc>
    List<T, Alloc> &List<T, Alloc>::operator=(List &&other) noexcept {
        if (this != &other) {
            alloc.free(_data);
            _cap = std::move(other._cap);
            _size = std::move(other._size);
            _data = other._data;
            other._data = nullptr;
        }
        return *this;
    }

    template<typename T, typename Alloc> requires std::is_base_of_v<IAllocator<T>, Alloc>
    Option<T &> List<T, Alloc>::operator[](size_t i) const {
        if (i < _size) {
            return _data[i];
        }
        return none;
    }

    template<typename T, typename Alloc> requires std::is_base_of_v<IAllocator<T>, Alloc>
    void List<T, Alloc>::set(const T &elem, size_t i) {
        if (i < _size) {
            _data[i] = elem;
        }
    }

    template<typename T, typename Alloc> requires std::is_base_of_v<IAllocator<T>, Alloc>
    T *List<T, Alloc>::data() const {
        return _data;
    }

    template<typename T, typename Alloc> requires std::is_base_of_v<IAllocator<T>, Alloc>
    size_t List<T, Alloc>::length() const {
        return _size;
    }

    template<typename T, typename Alloc> requires std::is_base_of_v<IAllocator<T>, Alloc>
    size_t List<T, Alloc>::capacity() const {
        return _cap;
    }

    template<typename T, typename Alloc> requires std::is_base_of_v<IAllocator<T>, Alloc>
    List<T, Alloc> &List<T, Alloc>::append(const T &el) {
        if (_size >= _cap) {
            T *old = _data;
            _data = alloc.alloc(_cap * 2);
            for (size_t i = 0; i < _size; i++) {
                _data[i] = old[i];
            }
            _cap *= 2;
            alloc.free(old);
        }
        _data[_size++] = el;
        return *this;
    }

    template<typename T, typename Alloc> requires std::is_base_of_v<IAllocator<T>, Alloc>
    List<T, Alloc> &List<T, Alloc>::appendRange(const List<T> &el) {
        if (_size + el._size >= _cap) {
            size_t new_ = _cap + el._cap;
            if (_size + el._size >= new_) {
                new_ *= 2;
            }
            T *old = _data;
            _data = alloc.alloc(new_);
            for (size_t i = 0; i < _size; i++) {
                _data[i] = old[i];
            }
            alloc.free(old);
            _cap += el._cap;
        }
        for (size_t i = 0; i < el._size; i++) {
            _data[_size++] = el._data[i];
        }

        return *this;
    }

    template<typename T, typename Alloc> requires std::is_base_of_v<IAllocator<T>, Alloc>
    List<T, Alloc> &List<T, Alloc>::insert(const T &elem, size_t i) {
        if (i >= _size) {
            return *this;
        }
        if (_size >= _cap) {
            auto old = _data;
            _data = alloc.alloc(_cap * 2);
            for (size_t j = 0; j < _size; j++) {
                _data[j] = old[j];
            }
            alloc.free(old);
            _cap *= 2;
        }
        auto new_ = alloc.alloc(_cap);
        size_t n = 0;
        size_t i_ = 0;
        _size++;
        while (n < _size) {
            if (n == i) {
                new_[n++] = elem;
            }
            new_[n++] = _data[i_++];
        }
        alloc.free(_data);
        _data = new_;
        return *this;
    }

    template<typename T, typename Alloc> requires std::is_base_of_v<IAllocator<T>, Alloc>
    List<T, Alloc> &List<T, Alloc>::insertRange(const List<T> &elem, size_t i) {
        if (i >= _size) {
            return *this;
        }
        if (_size + elem._size >= _cap + elem._cap) {
            auto old = _data;
            size_t cap = _cap * elem._cap;
            if (_size + elem._size >= cap) {
                cap *= 2;
            }
            _data = alloc.alloc(cap);
            for (size_t j = 0; j < _size; j++) {
                _data[j] = old[j];
            }
            alloc.free(old);
            _cap = cap;
        }
        auto new_ = alloc.alloc(_cap);
        size_t n = 0;
        size_t i_ = 0;
        _size++;
        while (n < _size) {
            if (n == i) {
                for (size_t _j = 0; _j < elem._size; _j++) {
                    new_[n++] = elem[_j];
                }
            }
            new_[n++] = _data[i_++];
        }
        alloc.free(_data);
        _data = new_;
        return *this;
    }

    template<typename T, typename Alloc> requires std::is_base_of_v<IAllocator<T>, Alloc>
    List<T, Alloc> &List<T, Alloc>::removeFirst(const T &elem) {
        if (!contains(elem)) {
            return *this;
        }
        bool has = false;

        auto old = _data;
        size_t n = 0;
        _data = alloc.alloc(_cap);
        for (size_t i = 0; i < _size; i++) {
            if (!has && elem == old[i]) {
                has = true;
                continue;
            }
            _data[n++] = old[i];
        }
        _size--;
        alloc.free(old);
        return *this;
    }

    template<typename T, typename Alloc> requires std::is_base_of_v<IAllocator<T>, Alloc>
    List<T, Alloc> &List<T, Alloc>::removeAll(const T &elem) {
        if (!contains(elem)) {
            return *this;
        }

        auto old = _data;
        size_t n = 0, m = 0;
        _data = alloc.alloc(_cap);
        for (size_t i = 0; i < _size; i++) {
            if (elem == old[i]) {
                m++;
                continue;
            }
            _data[n++] = old[i];
        }
        _size -= m;
        alloc.free(old);
        return *this;
    }

    template<typename T, typename Alloc> requires std::is_base_of_v<IAllocator<T>, Alloc>
    List<T, Alloc> &List<T, Alloc>::removeByIndex(size_t i) {
        if (i >= _size) {
            return *this;
        }

        auto old = _data;
        size_t n = 0;
        _data = alloc.alloc(_cap);
        for (size_t i_ = 0; i_ < _size; i++) {
            if (i == i_) {
                continue;
            }
            _data[n++] = old[i_];
        }
        _size--;
        alloc.free(old);
        return *this;
    }

    template<typename T, typename Alloc> requires std::is_base_of_v<IAllocator<T>, Alloc>
    List<T, Alloc> &List<T, Alloc>::removeFromTo(size_t start, size_t end) {
        if (start >= _size || end >= _size) {
            return *this;
        }
        if (start == end) {
            return removeByIndex(start);
        }
        if (start == 0 && end == _size) {
            return clear();
        }
        auto old = _data;
        _data = alloc.alloc(_cap);
        size_t n = 0, m = 0;
        for (size_t i = 0; i < _size; i++) {
            if (i >= start && i <= end) {
                m++;
                continue;
            }
            _data[n++] = old[i];
        }
        alloc.free(old);
        _size -= m;
        return *this;
    }

    template<typename T, typename Alloc> requires std::is_base_of_v<IAllocator<T>, Alloc>
    List<T, Alloc> &List<T, Alloc>::shrink(size_t divisor) {
        if (_cap / divisor > _size) {
            auto old = _data;
            size_t cap = _cap;
            while (cap / divisor > _size) {
                cap /= divisor;
            }
            _data = alloc.alloc(cap);
            for (size_t i = 0; i < _size; i++) {
                _data[i] = old[i];
            }
            alloc.free(old);
        }
        return *this;
    }

    template<typename T, typename Alloc> requires std::is_base_of_v<IAllocator<T>, Alloc>
    List<T, Alloc> &List<T, Alloc>::clear() {
        if (_data) {
            alloc.free(_data);
        }
        _size = 0;
        _cap = 2;
        return *this;
    }

    template<typename T, typename Alloc> requires std::is_base_of_v<IAllocator<T>, Alloc>
    List<T, Alloc> List<T, Alloc>::filter(const std::function<bool(const T &)> &cb) const {
        size_t c = 0;
        for (size_t i = 0; i < _size; i++) {
            if (cb(_data[i])) {
                c++;
            }
        }
        if (c == 0) {
            return {};
        }
        List result(c);
        for (size_t i = 0; i < _size; i++) {
            if (cb(_data[i])) {
                result.append(_data[i]);
            }
        }
        return result;
    }

    template<typename T, typename Alloc> requires std::is_base_of_v<IAllocator<T>, Alloc>
    List<T, Alloc> List<T, Alloc>::filter(const std::function<bool(const T &, size_t)> &cb) const {
        size_t c = 0;
        for (size_t i = 0; i < _size; i++) {
            if (cb(_data[i], i)) {
                c++;
            }
        }
        if (c == 0) {
            return {};
        }
        List result(c);
        for (size_t i = 0; i < _size; i++) {
            if (cb(_data[i], i)) {
                result.append(_data[i]);
            }
        }
        return result;
    }

    template<typename T, typename Alloc> requires std::is_base_of_v<IAllocator<T>, Alloc>
    Iterator<T> List<T, Alloc>::begin() const {
        return Iterator<T>{_data, _size+1, 0};
    }

    template<typename T, typename Alloc> requires std::is_base_of_v<IAllocator<T>, Alloc>
    Iterator<T> List<T, Alloc>::end() const {
        return Iterator<T>{_data, _size+1, _size};
    }

    template<typename T, typename Alloc> requires std::is_base_of_v<IAllocator<T>, Alloc>
    List<T, Alloc> &List<T, Alloc>::filterSelf(const std::function<bool(const T &)> &cb) {
        auto old = _data;
        _data = alloc.alloc(_cap);
        size_t n = 0, sz = 0;
        for (size_t i = 0; i < _size; i++) {
            if (cb(old[i])) {
                _data[n++] = old[i];
                sz++;
            }
        }
        _size = sz;
        alloc.free(old);
        return *this;
    }

    template<typename T, typename Alloc> requires std::is_base_of_v<IAllocator<T>, Alloc>
    List<T, Alloc> &List<T, Alloc>::filterSelf(const std::function<bool(const T &, size_t)> &cb) {
        auto old = _data;
        _data = alloc.alloc(_cap);
        size_t n = 0, sz = 0;
        for (size_t i = 0; i < _size; i++) {
            if (cb(old[i], i)) {
                _data[n++] = old[i];
                sz++;
            }
        }
        _size = sz;
        alloc.free(old);
        return *this;
    }

    template<typename T, typename Alloc> requires std::is_base_of_v<IAllocator<T>, Alloc>
    List<T, Alloc> &List<T, Alloc>::mapSelf(const std::function<T(const T &)> &cb) {
        auto old = _data;
        _data = alloc.alloc(_cap);
        for (size_t i = 0; i < _size; i++) {
            _data[i] = cb(old[i]);
        }
        alloc.free(old);
        return *this;
    }

    template<typename T, typename Alloc> requires std::is_base_of_v<IAllocator<T>, Alloc>
    List<T, Alloc> &List<T, Alloc>::mapSelf(const std::function<T(const T &, size_t)> &cb) {
        auto old = _data;
        _data = alloc.alloc(_cap);
        for (size_t i = 0; i < _size; i++) {
            _data[i] = cb(old[i], i);
        }
        alloc.free(old);
        return *this;
    }

    template<typename T, typename Alloc> requires std::is_base_of_v<IAllocator<T>, Alloc>
    Option<T &> List<T, Alloc>::findFirst(const std::function<bool(const T &)> &cb) const {
        for (size_t i = 0; i < _size; i++) {
            if (cb(_data[i])) {
                return _data[i];
            }
        }
        return none;
    }

    template<typename T, typename Alloc> requires std::is_base_of_v<IAllocator<T>, Alloc>
    Option<T &> List<T, Alloc>::findFirst(const std::function<bool(const T &, size_t)> &cb) const {
        for (size_t i = 0; i < _size; i++) {
            if (cb(_data[i], i)) {
                return _data[i];
            }
        }
        return none;
    }

    template<typename T, typename Alloc> requires std::is_base_of_v<IAllocator<T>, Alloc>
    Option<T &> List<T, Alloc>::findLast(const std::function<bool(const T &)> &cb) const {
        for (size_t i = _size; i-- > 0;) {
            if (cb(_data[i])) {
                return _data[i];
            }
        }
        return none;
    }

    template<typename T, typename Alloc> requires std::is_base_of_v<IAllocator<T>, Alloc>
    Option<T &> List<T, Alloc>::findLast(const std::function<bool(const T &, size_t)> &cb) const {
        for (size_t i = _size; i-- > 0;) {
            if (cb(_data[i], i)) {
                return _data[i];
            }
        }
        return none;
    }

    template<typename T, typename Alloc> requires std::is_base_of_v<IAllocator<T>, Alloc>
    List<T> List<T, Alloc>::select(size_t start, ssize_t end) const {
        if (start >= _size || end >= _size) {
            return {};
        }
        size_t diff = start < end ? end - start : start - end;
        List result(diff);
        for (size_t i = start; i <= end; i++) {
            result.append(_data[i]);
        }
        return result;
    }

    template<typename T, typename Alloc> requires std::is_base_of_v<IAllocator<T>, Alloc>
    List<T> List<T, Alloc>::selectRight(size_t start, ssize_t end) const {
        return {};
    }

    template<typename T, typename Alloc> requires std::is_base_of_v<IAllocator<T>, Alloc>
    void List<T, Alloc>::foreach(const std::function<void(const T &)> &cb) const {
        for (size_t i = 0; i < _size; i++) {
            cb(_data[i]);
        }
    }

    template<typename T, typename Alloc> requires std::is_base_of_v<IAllocator<T>, Alloc>
    void List<T, Alloc>::foreach(const std::function<void(const T &, size_t)> &cb) const {
        for (size_t i = 0; i < _size; i++) {
            cb(_data[i], i);
        }
    }

    template<typename T, typename Alloc> requires std::is_base_of_v<IAllocator<T>, Alloc>
    void List<T, Alloc>::foreach(const std::function<bool(const T &)> &cb) const {
        for (size_t i = 0; i < _size; i++) {
            if (!cb(_data[i])) {
                break;
            }
        }
    }

    template<typename T, typename Alloc> requires std::is_base_of_v<IAllocator<T>, Alloc>
    void List<T, Alloc>::foreach(const std::function<bool(const T &, size_t)> &cb) const {
        for (size_t i = 0; i < _size; i++) {
            if (!cb(_data[i], i)) {
                break;
            }
        }
    }

    template<typename T, typename Alloc> requires std::is_base_of_v<IAllocator<T>, Alloc>
    List<T> List<T, Alloc>::reverse() const {
        List result(_cap);
        for (size_t i = _size - 1; i-- > 0;) {
            result.append(_data[i]);
        }
        return result;
    }

    template<typename T, typename Alloc> requires std::is_base_of_v<IAllocator<T>, Alloc>
    List<T, Alloc> &List<T, Alloc>::reverseSelf() {
        size_t n = _size - 1;
        auto old = _data;
        _data = alloc.alloc(_cap);
        for (size_t i = 0; i < _size; i++) {
            _data[n--] = old[i];
        }
        alloc.free(old);
        return *this;
    }

    template<typename T, typename Alloc> requires std::is_base_of_v<IAllocator<T>, Alloc>
    bool List<T, Alloc>::contains(const T &elem) const {
        for (size_t i = 0; i < _size; i++) {
            if (elem == _data[i]) {
                return true;
            }
        }
        return false;
    }

    template<typename T, typename Alloc> requires std::is_base_of_v<IAllocator<T>, Alloc>
    bool List<T, Alloc>::contains(const std::function<bool(const T &)> &cb) const {
        for (size_t i = 0; i < _size; i++) {
            if (elem(_data[i])) {
                return true;
            }
        }
        return false;
    }

    template<typename T, typename Alloc> requires std::is_base_of_v<IAllocator<T>, Alloc>
    bool List<T, Alloc>::contains(const std::function<bool(const T &, size_t)> &cb) const {
        for (size_t i = 0; i < _size; i++) {
            if (elem(_data[i], i)) {
                return true;
            }
        }
        return false;
    }

    template<typename T, typename Alloc> requires std::is_base_of_v<IAllocator<T>, Alloc>
    size_t List<T, Alloc>::count(const T &elem) const {
        size_t c = 0;
        for (size_t i = 0; i < _size; i++) {
            if (elem == _data[i]) {
                c++;
            }
        }
        return c;
    }

    template<typename T, typename Alloc> requires std::is_base_of_v<IAllocator<T>, Alloc>
    size_t List<T, Alloc>::count(const std::function<bool(const T &)> &cb) const {
        size_t c = 0;
        for (size_t i = 0; i < _size; i++) {
            if (elem(_data[i])) {
                c++;
            }
        }
        return c;
    }

    template<typename T, typename Alloc> requires std::is_base_of_v<IAllocator<T>, Alloc>
    size_t List<T, Alloc>::count(const std::function<bool(const T &, size_t)> &cb) const {
        size_t c = 0;
        for (size_t i = 0; i < _size; i++) {
            if (elem(_data[i], i)) {
                c++;
            }
        }
        return c;
    }

    template<typename T, typename Alloc> requires std::is_base_of_v<IAllocator<T>, Alloc>
    std::string List<T, Alloc>::toString() const {
        return "";
    }


    template<typename T, typename Alloc> requires std::is_base_of_v<IAllocator<T>, Alloc>
    std::ostream &operator<<(std::ostream &os, List<T, Alloc> &ls) {
        os << "[ ";
        for (size_t i = 0; i < ls.length() - 1; i++) {
            os << ls.data()[i] << ", ";
        }
        os << ls.data()[ls.length() - 1] << " ]";
        return os;
    }
}


#endif //OPIE_DECLARATIVE_LIB_LIST_H
