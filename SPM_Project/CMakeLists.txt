cmake_minimum_required(VERSION 3.8)
project(SPMproject)

set(CMAKE_CXX_STANDARD 14)

add_definitions(-Wall)

find_package(OpenMP)
if (OPENMP_FOUND)
    set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
endif()

include_directories("src")
FILE(GLOB_RECURSE SOURCE_FILES src/*.h src/*.cpp)
#set(SOURCE_FILES src/NeuralNetwork.cpp src/NeuralNetwork.h src/activations/Sigmoid.cpp src/activations/Sigmoid.h src/activations/ActivationFunction.h src/activations/UnitStep.cpp src/activations/UnitStep.h src/utils.h src/nnsim.cpp src/nnsim.h src/utils.cpp src/metrics/Accuracy.cpp src/metrics/Accuracy.h src/layers/HiddenLayer.cpp src/layers/HiddenLayer.h src/layers/OutputLayer.cpp src/layers/OutputLayer.h src/layers/BaseLayer.cpp src/layers/BaseLayer.h src/activations/ActivationFunction.cpp src/metrics/Metric.cpp src/metrics/Metric.h)
add_library(SPMproject ${SOURCE_FILES})
target_link_libraries(SPMproject pthread)

FILE(GLOB_RECURSE TEST_FILES test/*_unittest.cpp)
#SET(TEST_FILES test/activations/Sigmoid_unittest.cpp test/NeuralNetwork_unittest.cpp test/utils_unittest.cpp)
add_executable(unittest test/main.cpp test/lib/catch.hpp ${TEST_FILES})
add_dependencies(unittest nnsim)
target_link_libraries(unittest nnsim)

add_executable(monks example/monks.cpp)
add_dependencies(monks nnsim)
target_link_libraries(monks nnsim)

add_executable(xor example/xor.cpp)
add_dependencies(xor nnsim)
target_link_libraries(xor nnsim)

add_executable(monks-model-selection example/monks_model_selection.cpp)
add_dependencies(monks-model-selection nnsim)
target_link_libraries(monks-model-selection nnsim)

add_executable(competition example/competition.cpp)
add_dependencies(competition nnsim)
target_link_libraries(competition nnsim)

add_executable(reprocessingData_4Competition example/reprocessingData_4Competition.cpp)
add_dependencies(reprocessingData_4Competition nnsim)
target_link_libraries(reprocessingData_4Competition nnsim)

add_executable(competition-model-selection example/competition_model_selection.cpp)
add_dependencies(competition-model-selection nnsim)
target_link_libraries(competition-model-selection nnsim)
