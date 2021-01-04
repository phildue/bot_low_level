cmake_minimum_required(VERSION 3.10)
project(robopi_drivers)

set(CMAKE_CXX_STANDARD 14)
set(COMPILE_FOR_PI TRUE CACHE BOOL "Set true if compile for pi")
set(COMPILE_TESTS FALSE CACHE BOOL "Set true if to compile tests")

if(NOT COMPILE_FOR_PI)
    set(target_sources src/pigpiostub.h src/pigpiostub.cpp)
endif()

add_library(${PROJECT_NAME} ${target_sources}
        src/MotorLn298.h
        src/MotorLn298Enc.h
        src/MotorLn298.cpp
        src/SonarHcsr04.h
        src/SonarHcsr04.cpp
        src/Encoder.cpp
        src/Encoder.h
        src/PiGpio.cpp src/PiGpio.h)

if(COMPILE_FOR_PI)
    target_compile_definitions(${PROJECT_NAME} PRIVATE COMPILE_FOR_PI)
endif()

target_include_directories(${PROJECT_NAME} PUBLIC src)
target_include_directories(${PROJECT_NAME} PUBLIC include)

if(COMPILE_FOR_PI)
    target_link_libraries(${PROJECT_NAME} -lpigpio)
endif()

if(COMPILE_TESTS)
    add_executable(test_motor test/test_motor.cpp)
    add_executable(test_motor_with_encoder test/test_motor_with_encoder.cpp)
    target_link_libraries(test_motor ${PROJECT_NAME})
    target_link_libraries(test_motor_with_encoder ${PROJECT_NAME})
endif()


