cmake_minimum_required(VERSION 3.10)
project(bot_low_level)

set(COMPILE_FOR_ARDUINO FALSE CACHE BOOL "Set true if compile for pi")
set(COMPILE_FOR_PI FALSE CACHE BOOL "Set true if compile for pi")

set(COMPILE_FOR_PI TRUE CACHE BOOL "Set true if compile for pi")

add_library(${PROJECT_NAME}
        src/MotorLn298.h
        src/MotorVelocityControl.cpp
        src/MotorVelocityControl.h
        src/MotorLn298.cpp
        src/SonarHcsr04.h
        src/SonarHcsr04.cpp
        src/Encoder.cpp
        src/Encoder.h
        #src/Gpio.cpp
        src/System.h
        src/types.h)


if(COMPILE_FOR_PI)
    message(STATUS "Compiling for PI")
    target_compile_definitions(${PROJECT_NAME} PUBLI COMPILE_FOR_PI=1)
    target_link_libraries(${PROJECT_NAME} -lpigpio)
endif()
if(COMPILE_FOR_ARDUINO)
    message(STATUS "Compiling for Arduino")
    target_compile_definitions(${PROJECT_NAME} PUBLIC COMPILE_FOR_ARDUINO=1)
endif()

target_include_directories(${PROJECT_NAME} PUBLIC src)
target_include_directories(${PROJECT_NAME} PUBLIC include)

if(COMPILE_TESTS)

add_subdirectory(test)
endif()

