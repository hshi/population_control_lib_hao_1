cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

project(popcontrolhao)

#For find module path
set(CMAKE_MODULE_PATH "${MODULE_EXTRA_PATH}" ${CMAKE_MODULE_PATH})

#For definitions
add_definitions(${COMPILER_EXTRA_DEF})

#For c++ flag
set(CMAKE_CXX_FLAGS "${COMPILER_EXTRA_FLAG}" ${CMAKE_CXX_FLAGS})

set(lib_all "")

#For GMP library
find_package(gmp REQUIRED)
set(lib_all ${gmp_libraries} ${lib_all})

#For Sprng library
add_definitions(-DPOINTER_SIZE=8)
find_package(sprng REQUIRED)
include_directories(${sprng_include_dirs})
set(lib_all ${sprng_libraries} ${lib_all})


#For libaray hao:mpi and randomhao
find_package(mpihao REQUIRED)
include_directories(${mpihao_include_dirs})
set(lib_all ${mpihao_libraries} ${lib_all})

find_package(randomhao REQUIRED)
include_directories(${randomhao_include_dirs})
set(lib_all ${randomhao_libraries} ${lib_all})


include_directories(inc)

add_subdirectory(inc)

add_subdirectory(src)

add_subdirectory(test)
