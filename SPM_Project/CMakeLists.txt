cmake_minimum_required(VERSION 3.8)
project(Montecarlo)

set(CMAKE_CXX_STANDARD 11)

add_definitions(-Wall)
add_definitions(-O3)
add_definitions(-lpthread)
#add_definitions(-DBLOCKING_MODE)

#find_package(OpenMP)
#if (OPENMP_FOUND)
#    set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
#    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
#endif()

include_directories("source")   # FF_ROOT

FILE(GLOB_RECURSE SOURCE_FILES source/*.h source/*.cpp)
add_library(Montecarlo ${SOURCE_FILES})
target_link_libraries(Montecarlo pthread)

add_executable(test1 implement/test1.cpp)
add_dependencies(test1 Montecarlo)
target_link_libraries(test1 Montecarlo)

#add_executable(parallel implement/parallelism.cpp)
#add_dependencies(parallel SPM_Project)
#target_link_libraries(parallel SPM_Project)

add_executable(threads implement/parallelism_normal_thread.cpp)
add_dependencies(threads Montecarlo)
target_link_libraries(threads Montecarlo)

add_executable(threads_parallelism implement/parallelism_thread.cpp)
add_dependencies(threads_parallelism Montecarlo)
target_link_libraries(threads_parallelism Montecarlo)


add_executable(ff_parallelism implement/parallelism_ff.cpp)
add_dependencies(ff_parallelism Montecarlo)
target_link_libraries(ff_parallelism Montecarlo)
