//
// Created by Andryusha on 02.01.2026.
//

#ifndef OPIE_DECLARATIVE_LIB_UTILS_H
#define OPIE_DECLARATIVE_LIB_UTILS_H

#include <collections/list.h>


namespace opie {
    inline List<size_t> range(size_t start) {
        List<size_t> res(start);
        for (size_t i = 0; i < start; i++) {
            res.append(i);
        }
        return res;
    }

    inline List<int> range(int start, int end) {
        if (start > end) {
            return {};
        }
        int diff = end - start;
        List<int> res(diff);
        for (int i = start; i < end; i++) {
            res.append(i);
        }
        return res;
    }

    inline List<int> range(int start, int end, int step) {
        if (start > end) {
            return {};
        }
        int diff = end - start;
        List<int> res(diff);
        for (int i = start; i + step < end; i += step) {
            res.append(i);
        }
        return res;
    }

    template<typename F>
    class defer_ final {
        F cb;
    public:
        defer_(const F &cb): cb(cb){}
        ~defer_(){cb();}
    };


    template<typename F>
    class deferList {
        std::vector<F> cb;
    public:
        deferList()=default;
        deferList&operator=(const F&f) {
            cb.push_back(f);
            return *this;
        }

        ~deferList() {
            for (const auto& i : cb) {
                i();
            }
        }
    };

    inline deferList<std::function<void()>> _defer;

#define defer _defer =

}


#endif //OPIE_DECLARATIVE_LIB_UTILS_H
