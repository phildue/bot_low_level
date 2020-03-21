cmake_minimum_required(VERSION 3.10)
project(gpiocpp)

set(CMAKE_CXX_STANDARD 14)
set(COMPILE_FOR_PI TRUE CACHE BOOL "Set true if compile for pi")
if(COMPILE_FOR_PI)
    set(target_sources  GpioWheel/GpioWheel.cpp)
else()
    set(target_sources GpioWheel/GpioWheelStub.cpp)
endif()
add_executable(gpiocpp main.cpp GpioWheel/GpioWheel.h ${target_sources})


if(COMPILE_FOR_PI)
    target_link_libraries(${PROJECT_NAME} -lpigpio)
endif()
