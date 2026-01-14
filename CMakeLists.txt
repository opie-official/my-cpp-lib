cmake_minimum_required(VERSION 4.0)
project(opie_declarative_lib)

set(CMAKE_CXX_STANDARD 26)

add_executable(opie_declarative_lib main.cpp
        opie/collections/list.h
        opie/defines.h
        opie/interfaces/iarray.h
        opie/types/option.h
        opie/collections/slice.h
        opie/collections/iterator.h
        opie/types/allocator.h
        opie/interfaces/iallocator.h
        opie/utils.h
        opie/collections/array.h
        opie/interfaces/iiterable.h)



target_include_directories(opie_declarative_lib PRIVATE
    ./opie
)