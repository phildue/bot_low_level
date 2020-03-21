cmake_minimum_required(VERSION 3.10)
project(gpiocpp)

set(CMAKE_CXX_STANDARD 14)
set(GPIOCPP_COMPILE_FOR_PI TRUE CACHE BOOL "Set true if compile for pi")
set(GPIOCPP_COMPILE_TESTS FALSE CACHE BOOL "Set true if compile for pi")

if(GPIOCPP_COMPILE_FOR_PI)
    set(target_sources  src/GpioWheel/GpioWheel.cpp)
else()
    set(target_sources src/GpioWheel/GpioWheelStub.cpp)
endif()

add_library(${PROJECT_NAME} ${target_sources})
target_include_directories(${PROJECT_NAME} PUBLIC include)

if(GPIOCPP_COMPILE_FOR_PI)
    target_link_libraries(${PROJECT_NAME} -lpigpio)
endif()

if(GPIOCPP_COMPILE_TESTS)
    add_executable(test_gpiocpp test/test.cpp)
    target_link_libraries(test_gpiocpp ${PROJECT_NAME})
endif()


