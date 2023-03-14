cmake_minimum_required(VERSION 3.11)

set(CMAKE_CXX_FLAGS "-std=c++11 -g")

project(gmshdemo)

add_executable(stl stl.cpp)
add_executable(toroid toroid.cpp)

# gmsh укажем явно (потому что он был просто распакован руками)
add_library(gmsh SHARED IMPORTED)
set_target_properties(gmsh PROPERTIES
        IMPORTED_LOCATION "/home/derevo/Projects/gmsh-4.11.1-Linux64-sdk/lib/libgmsh.so"
        INTERFACE_INCLUDE_DIRECTORIES "/home/derevo/Projects/gmsh-4.11.1-Linux64-sdk/include"
        )
set(GMSH_LIBRARY gmsh)

# Укажем библиотеки для линковки
target_link_libraries(toroid ${GMSH_LIBRARY})
target_link_libraries(stl ${GMSH_LIBRARY})

