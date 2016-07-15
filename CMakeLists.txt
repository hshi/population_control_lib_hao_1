cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

project(popcontrolhao)

#For find module path
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "~/lib/Modules")

#For definitions
add_definitions(${COMPILER_EXTRA_DEF})

#For c++ flag
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

include_directories(inc)

#For library
set(lib_all "")

   #For GMP library
   find_package(gmp REQUIRED)
   set(lib_all ${gmp_libraries} ${lib_all})
   
   #For Sprng library
   find_package(sprng REQUIRED)
   add_definitions(${sprng_definitions})
   include_directories(${sprng_include_dirs})
   set(lib_all ${sprng_libraries} ${lib_all})
   
   #For library hao:mpi randomhao
   find_package(libhao0 REQUIRED)
   include_directories(${libhao0_include_dirs})
   set(lib_all ${mpihao_libraries} ${randomhao_libraries} ${lib_all})

add_subdirectory(inc)

add_subdirectory(src)

add_subdirectory(test)
