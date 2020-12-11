cmake_minimum_required(VERSION 3.10)
project(pi_ln298n)

set(CMAKE_CXX_STANDARD 14)
set(COMPILE_FOR_PI TRUE CACHE BOOL "Set true if compile for pi")
set(COMPILE_TESTS FALSE CACHE BOOL "Set true if to compile tests")

if(NOT COMPILE_FOR_PI)
    set(target_sources src/pigpiostub.h src/pigpiostub.cpp)
endif()

add_library(${PROJECT_NAME} ${target_sources}
        src/MotorLn298.h
        src/MotorLn298.cpp
        src/SonarHcr04.h
        src/SonarHcr04.cpp
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
    add_executable(test_sonar test/test_sonar.cpp)
    target_link_libraries(test_motor ${PROJECT_NAME})
    target_link_libraries(test_sonar ${PROJECT_NAME})
endif()


