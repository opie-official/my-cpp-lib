//
// Created by Andryusha on 11.12.2025.
//

#ifndef OPIE_DECLARATIVE_LIB_DEFINES_H
#define OPIE_DECLARATIVE_LIB_DEFINES_H

#define interface struct
#define abstract
#define use(a) using namespace a
#define impl namespace opie_impl
#define panic_(message) opie_impl::panic_impl(__LINE__, __FILE__, message)
#include <iostream>


impl {

auto panic_impl(int line, const char*filename, const char*message) {
    std::cerr<<"ERROR in file "<<filename<< " at line "<< line<<"\n"<< message<<std::endl;
    std::exit(1);
}


}


#endif //OPIE_DECLARATIVE_LIB_DEFINES_H
