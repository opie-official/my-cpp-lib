//
// Created by Andryusha on 14.01.2026.
//

#ifndef OPIE_DECLARATIVE_LIB_LINKED_LIST_H
#define OPIE_DECLARATIVE_LIB_LINKED_LIST_H

#include <functional>
#include <initializer_list>
#include <stddef.h>

#include "interfaces/iallocator.h"
#include "interfaces/iarray.h"
#include "interfaces/ievaluatable.h"
#include "interfaces/iindexable.h"
#include "interfaces/iiterable.h"
#include "interfaces/imanipulatable.h"

namespace opie {
    template<typename T>
    struct LinkNode {
        T data;

        LinkNode(const T &data) : data(data) {
        }

        ~LinkNode() = default;
    };


    template<typename T, typename Alloc=IAllocator<T> > requires std::is_base_of_v<IAllocator<T>, Alloc>
    class LinkedList :
            public IArray<LinkNode<T> >,
            public IIterable<LinkNode<T> >,
            public IIndexable<T>,
            public IManipulatable<LinkedList<T>, T, LinkedList<T> >,
            public IEvaluatable<T, LinkedList<T>>
    {
        LinkNode<T> *root = nullptr;
        size_t _size = 0;
        Alloc alloc;
        using init = std::initializer_list<T>;

    public:
        LinkedList() = default;

        LinkedList(const init &init_);

        LinkedList(const LinkedList &other);

        LinkedList(LinkedList &&other) noexcept;

        ~LinkedList() override;

        LinkedList &operator=(const init &init_);

        LinkedList &operator=(const LinkedList &other);

        LinkedList &operator=(LinkedList &&other) noexcept;

        LinkNode<T> *data() const override;

        [[nodiscard]] size_t length() const override;

        Option<T &> operator[](size_t i) const noexcept override;

        Iterator<LinkNode<T> > begin() const override;

        Iterator<LinkNode<T> > end() const override;


        template<typename M>
        LinkedList<M> map(const std::function<M(const T &)> &cb) const {
        }

        template<typename M>
        LinkedList<M> map(const std::function<M(const T &, size_t)> &cb) const {
        }

        LinkedList<T> select(size_t from, size_t to) const override;

        void foreach(const std::function<void(const T &)> &cb) const override;

        void foreach(const std::function<void(const T &, size_t)> &cb) const override;

        LinkedList<T> filter(const std::function<bool(const T &)> &cb) const override;

        LinkedList<T> filter(const std::function<bool(const T &, size_t)> &cb) const override;

        T reduce(const std::function<T(const T &acc, const T &el)> &cb, const T &def) const override;

        T reduce(const std::function<T(const T &acc, const T &el, size_t)> &cb, const T &def) const override;

        Option<T> find(const T &el) const override;

        Option<T> find(const std::function<bool(const T &)> &cb) const override;

        Option<T> find(const std::function<bool(const T &, size_t)> &ecb) const override;

        bool contains(const T &el) const override;

        bool contains(const std::function<bool(const T &)> &cb) const override;

        bool contains(const std::function<bool(const T &, size_t)> &cb) const override;

        size_t count(const T &el) const override;

        size_t count(const std::function<bool(const T &)> &cb) const override;

        size_t count(const std::function<bool(const T &, size_t)> &cb) const override;

        LinkedList<T> & append(const T &el) override;

        LinkedList<T> & appendRange(const LinkedList<T> &arr) override;

        LinkedList<T> & removeFirst(const T &el) override;

        LinkedList<T> & removeLast(const T &el) override;

        LinkedList<T> & removeAll(const T &el) override;

        LinkedList<T> & removeByIndex(size_t i) override;

        LinkedList<T> & insert(const T &el, size_t i) override;

        LinkedList<T> & insertRange(const LinkedList<T> &arr, size_t i) override;
    };
}


#endif //OPIE_DECLARATIVE_LIB_LINKED_LIST_H
