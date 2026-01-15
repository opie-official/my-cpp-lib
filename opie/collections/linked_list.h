//
// Created by Andryusha on 14.01.2026.
//

#ifndef OPIE_DECLARATIVE_LIB_LINKED_LIST_H
#define OPIE_DECLARATIVE_LIB_LINKED_LIST_H

#include <functional>
#include <initializer_list>
#include "interfaces/iarray.h"
#include "interfaces/ievaluatable.h"
#include "interfaces/iindexable.h"
#include "interfaces/iiterable.h"
#include "interfaces/imanipulatable.h"
#include <interfaces/istr.h>

namespace opie {
    template<typename T>
    struct LinkNode  /*: IIndexable<T>*/ {
        T data;
        LinkNode *next = nullptr;

        ~LinkNode() /*override*/ {
            delete next;
        }
    };


    template<typename T>
    class LinkedList :
            public IArray<LinkNode<T> >,
            public IIterable<LinkNode<T> >,
            public IIndexable<T>,
            public IManipulatable<LinkedList<T>, T, LinkedList<T> >,
            public IEvaluatable<T, LinkedList<T> >,
            public IStr {
        LinkNode<T> *root = nullptr;
        size_t _size = 0;
        using init = std::initializer_list<T>;

    public:
        LinkedList() = default;

        LinkedList(const init &init_);

        LinkedList(const LinkedList &other) = delete;

        LinkedList(LinkedList &&other) noexcept;

        ~LinkedList() override;

        LinkedList &operator=(const init &init_);

        LinkedList &operator=(const LinkedList &other) = delete;

        LinkedList &operator=(LinkedList &&other) noexcept;

        LinkNode<T> *data() const override;

        [[nodiscard]] size_t length() const override;

        Option<const T &> operator[](size_t i) const noexcept override;

        Iterator<LinkNode<T> > begin() const override;

        Iterator<LinkNode<T> > end() const override;

        // unused now
        template<typename M>
        LinkedList<M> map(const std::function<M(const T &)> &cb) const {
            LinkedList<M> res;
            auto node=root;
            while (node) {
                res.append(cb(node->data));
                node=node->next;
            }
            return res;
        }

        // unused now
        template<typename M>
        LinkedList<M> map(const std::function<M(const T &, size_t)> &cb) const {
            LinkedList<M> res;
            auto node=root;
            size_t n=0;
            while (node) {
                res.append(cb(node->data, n++));
                node=node->next;
            }
            return res;
        }

        LinkedList map(const std::function<T(const T &, size_t)> &cb) const;
        LinkedList map(const std::function<T(const T &)> &cb) const;


        Option<T &> operator[](size_t i) noexcept override;

        LinkedList<T> select(size_t from, size_t to) const override;

        void foreach(const std::function<void(const T &)> &cb) const override;

        void foreach(const std::function<void(const T &, size_t)> &cb) const override;

        LinkedList<T> filter(const std::function<bool(const T &)> &cb) const override;

        LinkedList<T> filter(const std::function<bool(const T &, size_t)> &cb) const override;

        T reduce(const std::function<T(const T &acc, const T &el)> &cb, const T &def) const override;

        T reduce(const std::function<T(const T &acc, const T &el, size_t)> &cb, const T &def) const override;

        Option<size_t> find(const T &el) const override;

        Option<size_t> find(const std::function<bool(const T &)> &cb) const override;

        Option<size_t> find(const std::function<bool(const T &, size_t)> &cb) const override;

        bool contains(const T &el) const override;

        bool contains(const std::function<bool(const T &)> &cb) const override;

        bool contains(const std::function<bool(const T &, size_t)> &cb) const override;

        size_t count(const T &el) const override;

        size_t count(const std::function<bool(const T &)> &cb) const override;

        size_t count(const std::function<bool(const T &, size_t)> &cb) const override;

        LinkedList<T> &append(const T &el) override;

        LinkedList<T> &appendRange(const LinkedList<T> &arr) override;

        LinkedList<T> &removeFirst(const T &el) override;


        LinkedList<T> &removeAll(const T &el) override;

        LinkedList<T> &removeByIndex(size_t i) override;

        LinkedList<T> &insert(const T &el, size_t i) override;

        LinkedList<T> &insertRange(const LinkedList<T> &arr, size_t i) override;


        std::string toString() const override;

        std::string toString(const std::string &sep) const override;

        std::string toStringOut() const override;
    };

    template<typename T>
    LinkedList<T>::LinkedList(const init &init_) {
        auto ptr = init_.begin();
        _size = init_.size();
        for (size_t i = 0; i < init_.size(); i++) {
            auto node = new LinkNode<T>;
            node->data = *(ptr + i);
            if (root == nullptr) {
                root = node;
            } else {
                auto cur = root;
                while (cur->next != nullptr) {
                    cur = cur->next;
                }
                cur->next = node;
            }
        }
    }


    template<typename T>
    LinkedList<T>::LinkedList(LinkedList &&other) noexcept {
        root = other.root;
        _size=std::move(other._size);
        other.root = nullptr;
    }

    template<typename T>
    LinkedList<T>::~LinkedList() {
        delete root;
    }


    template<typename T>
    LinkedList<T> &LinkedList<T>::operator=(const init &init_) {
        delete root;
        auto ptr = init_.begin();
        _size = init_.size();
        for (size_t i = 0; i < init_.size(); i++) {
            auto node = new LinkNode<T>;
            node->data = *(ptr + i);
            if (root == nullptr) {
                root = node;
            } else {
                auto cur = root;
                while (cur->next != nullptr) {
                    cur = cur->next;
                }
                cur->next = node;
            }
        }
        return *this;
    }


    template<typename T>
    LinkedList<T> &LinkedList<T>::operator=(LinkedList &&other) noexcept {
        delete root;
        root = other.root;
        other.root = nullptr;
        return *this;
    }

    template<typename T>
    LinkNode<T> *LinkedList<T>::data() const {
        return root;
    }

    template<typename T>
    size_t LinkedList<T>::length() const {
        return _size;
    }

    template<typename T>
    Option<const T &> LinkedList<T>::operator[](size_t i) const noexcept {
        if (i >= _size || root == nullptr) {
            return none;
        }
        auto cur = root;
        for (size_t n = 0; n < i; ++n) {
            cur = cur->next;
            if (cur == nullptr) {
                return none;
            }
        }
        return cur->data;
    }

    template<typename T>
    Option<T &> LinkedList<T>::operator[](size_t i) noexcept {
        if (i >= _size || root == nullptr) {
            return none;
        }
        auto cur = root;
        for (size_t n = 0; n < i; ++n) {
            cur = cur->next;
            if (cur == nullptr) {
                return none;
            }
        }
        return cur->data;
    }

    template<typename T>
    Iterator<LinkNode<T> > LinkedList<T>::begin() const {
        return Iterator<LinkNode<T> >(root, _size + 1, 0);
    }

    template<typename T>
    Iterator<LinkNode<T> > LinkedList<T>::end() const {
        return Iterator<LinkNode<T> >(root, _size + 1, _size);
    }

    template<typename T>
    LinkedList<T> LinkedList<T>::select(size_t from, size_t to) const {
        if (from < _size && to < _size && from < to) {
            if (root==nullptr) {
                return {};
            }
            LinkedList<T> res;
            auto node=root;
            for (size_t i=0;i<from;i++) {
                if (node==nullptr) {
                    return res;
                }
                node=node->next;
            }
            for (size_t i = from; i <= to; i++) {
                if (node==nullptr) {
                    return res;
                }
                res.append(node->data);
                node=node->next;
            }
            return res;
        }
        return {};
    }

    template<typename T>
    void LinkedList<T>::foreach(const std::function<void(const T &)> &cb) const {
        auto node = root;
        while (node) {
            cb(node->data);
            node=node->next;
        }
    }

    template<typename T>
    void LinkedList<T>::foreach(const std::function<void(const T &, size_t)> &cb) const {
        size_t n = 0;
        auto node = root;
        while (node) {
            cb(node->data, n++);
            node=node->next;
        }
    }

    template<typename T>
    LinkedList<T> LinkedList<T>::filter(const std::function<bool(const T &)> &cb) const {
        LinkedList<T> res;
        auto node = root;
        while (node) {
            if (cb(node->data)) {
                res.append(node->data);
            }
            node=node->next;
        }
        return res;
    }

    template<typename T>
    LinkedList<T> LinkedList<T>::filter(const std::function<bool(const T &, size_t)> &cb) const {
        LinkedList<T> res;
        size_t n = 0;
        auto node = root;
        while (node) {
            if (cb(node->data, n++)) {
                res.append(node->data);
            }
            node=node->next;
        }
        return res;
    }

    template<typename T>
    T LinkedList<T>::reduce(const std::function<T(const T &acc, const T &el)> &cb, const T &def) const {
        T res = def;
        auto node = root;
        while (node) {
            res = cb(res, node->data);
            node = node->next;
        }
        return res;
    }

    template<typename T>
    T LinkedList<T>::reduce(const std::function<T(const T &acc, const T &el, size_t)> &cb, const T &def) const {
        T res = def;
        auto node = root;
        size_t n = 0;
        while (node) {
            res = cb(res, node->data, n++);
            node = node->next;
        }
        return res;
    }

    template<typename T>
    Option<size_t> LinkedList<T>::find(const T &el) const {
        auto node = root;

        size_t n = 0;
        while (node) {
            if (node->data == el) {
                return n;
            }
            n++;
            node = node->next;
        }
        return none;
    }

    template<typename T>
    Option<size_t> LinkedList<T>::find(const std::function<bool(const T &)> &cb) const {
        auto node = root;
        size_t n = 0;
        while (node) {
            if (cb(node->data)) {
                return n;
            }
            n++;
            node = node->next;
        }
        return none;
    }

    template<typename T>
    Option<size_t> LinkedList<T>::find(const std::function<bool(const T &, size_t)> &cb) const {
        auto node = root;
        size_t n = 0;
        while (node) {
            if (cb(node->data, n)) {
                return n;
            }
            n++;
            node = node->next;
        }
        return none;
    }

    template<typename T>
    bool LinkedList<T>::contains(const T &el) const {
        auto node = root;
        while (node) {
            if (node->data==el) {
                return true;
            }
            node=node->next;
        }
        return false;
    }

    template<typename T>
    bool LinkedList<T>::contains(const std::function<bool(const T &)> &cb) const {
        auto node = root;
        while (node) {
            if (cb(node->data)) {
                return true;
            }
            node=node->next;
        }
        return false;
    }

    template<typename T>
    bool LinkedList<T>::contains(const std::function<bool(const T &, size_t)> &cb) const {
        auto node = root;
        size_t n = 0;
        while (node) {
            if (cb(node->data, n++)) {
                return true;
            }
            node=node->next;
        }
        return false;
    }

    template<typename T>
    size_t LinkedList<T>::count(const T &el) const {
        auto node = root;
        size_t res = 0;
        while (node) {
            if (node->data==el) {
                res++;
            }
            node=node->next;
        }
        return res;
    }

    template<typename T>
    size_t LinkedList<T>::count(const std::function<bool(const T &)> &cb) const {
        auto node = root;
        size_t res = 0;
        while (node) {
            if (cb(node->data)) {
                res++;
            }
            node=node->next;
        }
        return res;
    }

    template<typename T>
    size_t LinkedList<T>::count(const std::function<bool(const T &, size_t)> &cb) const {
        auto node = root;
        size_t res = 0;
        size_t n = 0;
        while (node) {
            if (cb(node->data, n++)) {
                res++;
            }
            node=node->next;
        }
        return res;
    }

    template<typename T>
    LinkedList<T> &LinkedList<T>::append(const T &el) {
        if (root == nullptr) {
            root = new LinkNode<T>;
            root->data = el;
            _size++;
            return *this;
        }
        auto node = root;
        while (node->next != nullptr) {
            node = node->next;
        }
        auto temp = new LinkNode<T>;
        temp->data = el;
        node->next = temp;
        _size++;
        return *this;
    }

    template<typename T>
    LinkedList<T> &LinkedList<T>::appendRange(const LinkedList<T> &arr) {
        if (arr.length() == 0) {
            return *this;
        }
        if (root == nullptr) {
            auto temp = new LinkNode<T>;
            temp->data = arr[0].unwrap();
            root = temp;
            _size++;
            auto node = root;
            for (size_t i = 1; i < arr.length(); i++) {
                auto temp_ = new LinkNode<T>;
                temp_->data = arr[i].unwrap();
                node->next = temp_;
                node = node->next;
                _size++;
            }
            return *this;
        }
        auto node = root;
        while (node->next != nullptr) {
            node = node->next;
        }
        for (size_t i = 0; i < arr.length(); i++) {
            auto temp = new LinkNode<T>;
            temp->data = arr[i].unwrap();
            node->next = temp;
            node = node->next;
            _size++;
        }
        return *this;
    }

    template<typename T>
    LinkedList<T> &LinkedList<T>::removeFirst(const T &el) {
        if (root==nullptr) {
            return *this;
        }
        if (root->data==el) {
            auto victim = root;
            root = root->next;
            victim->next = nullptr;
            delete victim;
            --_size;
            return *this;
        }
        auto prev = root;
        auto node = root->next;
        while (node && node->data != el) {
            prev = node;
            node = node->next;
        }
        if (node) {
            prev->next = node->next;
            node->next = nullptr;
            delete node;
            --_size;
        }
        return *this;
    }

    template<typename T>
LinkedList<T>& LinkedList<T>::removeAll(const T& el) {
        while (root && root->data == el) {
            auto victim = root;
            root = root->next;
            victim->next = nullptr;
            delete victim;
            --_size;
        }

        if (!root) return *this;
        auto prev = root;
        auto node = root->next;

        while (node) {
            if (node->data == el) {
                prev->next = node->next;
                node->next = nullptr;
                delete node;
                node = prev->next;
                --_size;
            } else {
                prev = node;
                node = node->next;
            }
        }

        return *this;
    }

    template<typename T>
    LinkedList<T> &LinkedList<T>::removeByIndex(size_t i) {
        if (root == nullptr) {
            return *this;
        }
        if (i == 0) {
            auto temp = root;
            root = root->next;
            temp->next = nullptr;
            delete temp;
            _size--;
            return *this;
        }
        auto node = root;
        auto prev = root;
        size_t n = 0;
        while (i != n && node->next != nullptr) {
            prev = node;
            node = node->next;
            n++;
        }
        if (n == i) {
            auto temp = node->next;
            node->next = nullptr;
            prev->next = temp;
            delete node->next;
            _size--;
        }
        return *this;
    }

    template<typename T>
    LinkedList<T> &LinkedList<T>::insert(const T &el, size_t i) {
        return *this;
    }

    template<typename T>
    LinkedList<T> &LinkedList<T>::insertRange(const LinkedList<T> &arr, size_t i) {
        return *this;
    }

    template<typename T>
    std::string LinkedList<T>::toString() const {
        if constexpr (std::is_fundamental_v<T>) {
            if constexpr (std::is_pointer_v<T>) {
                std::string res;
                auto node = root;
                for (size_t i = 0; i < _size; i++) {
                    if (node==nullptr) {
                        break;
                    }
                    res += std::to_string(*(node->data));
                    node=node->next;
                }
                return res;
            } else if constexpr (std::is_same_v<T, std::string>) {
                std::string res;
                auto node = root;
                for (size_t i = 0; i < _size; i++) {
                    if (node==nullptr) {
                        break;
                    }
                    res +=node->data;
                    node=node->next;
                }
                return res;
            } else if constexpr (std::is_enum_v<T>) {
                // nothing
                return "";
            } else {
                std::string res;
                auto node = root;
                for (size_t i = 0; i < _size; i++) {
                    if (node==nullptr) {
                        break;
                    }
                    res += std::to_string(node->data);
                    node=node->next;
                }
                return res;
            }
        } else if constexpr (std::is_base_of_v<IStr, T>) {
            std::string res;
            auto node = root;
            for (size_t i = 0; i < _size; i++) {
                if (node==nullptr) {
                    break;
                }
                res += std::to_string(node->data.toString());
                node=node->next;
            }
            return res;
        } else {
            return "";
        }
    }

    template<typename T>
    std::string LinkedList<T>::toString(const std::string &sep) const {
        if constexpr (std::is_fundamental_v<T>) {
            if constexpr (std::is_pointer_v<T>) {
                std::string res;
                auto node=root;
                for (size_t i = 0; i < _size - 1; i++) {
                    if (node==nullptr) {
                        break;
                    }
                    res += std::to_string(*node->data) + sep;
                    node=node->next;
                }
                if (node) {
                    res += std::to_string(*node->data);
                }
                return res;
            } else if constexpr (std::is_same_v<T, std::string>) {
                std::string res;
                auto node=root;
                for (size_t i = 0; i < _size - 1; i++) {
                    if (node==nullptr) {
                        break;
                    }
                    res += node->data + sep;
                    node=node->next;
                }
                if (node) {
                    res +=node->data;
                }
                return res;
            } else if constexpr (std::is_enum_v<T>) {
                // nothing
                return sep;
            } else {
                std::string res;
                auto node=root;
                for (size_t i = 0; i < _size - 1; i++) {
                    if (node==nullptr) {
                        break;
                    }
                    res += std::to_string(node->data) + sep;
                    node=node->next;
                }
                if (node) {
                    res += std::to_string(node->data);
                }
                return res;
            }
        } else if constexpr (std::is_base_of_v<IStr, T>) {
            std::string res;
            auto node=root;
            for (size_t i = 0; i < _size - 1; i++) {
                if (node==nullptr) {
                    break;
                }
                res += std::to_string(node->data.toString()) + sep;
                node=node->next;
            }
            if (node) {
                res += std::to_string(node->data.toString());
            }
            return res;
        } else {
            return sep;
        }
    }

    template<typename T>
    std::string LinkedList<T>::toStringOut() const {
        return "[ "+toString(", ")+" ]";
    }


    template<typename T>
    LinkedList<T> LinkedList<T>::map(const std::function<T(const T &, size_t)> &cb) const {
        LinkedList res;
        auto node=root;
        size_t n=0;
        while (node) {
            res.append(cb(node->data, n++));
            node=node->next;
        }
        return res;
    }

    template<typename T>
    LinkedList<T> LinkedList<T>::map(const std::function<T(const T &)> &cb) const {
        LinkedList res;
        auto node=root;
        while (node) {
            res.append(cb(node->data));
            node=node->next;
        }
        return res;
    }
}


#endif //OPIE_DECLARATIVE_LIB_LINKED_LIST_H
