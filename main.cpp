#include <collections/list.h>
#include <utils.h>

#include "collections/slice.h"
using namespace opie;


void do_(const Slice<int> &a) {
    for (auto &i: a) {
        std::cout << i << std::endl;
    }
}


int main() {
    List a{1, 2, 3, 4, 5, 6, 7, 8, 9, 0};


    do_(a);


    int p[] = {1, 2, 3, 4};

    std::cout<<std::endl;

    do_(p);
}
