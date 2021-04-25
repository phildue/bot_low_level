cmake_minimum_required(VERSION 3.10)
project(robopi_drivers)

set(CMAKE_CXX_STANDARD 14)
set(COMPILE_FOR_PI TRUE CACHE BOOL "Set true if compile for pi")
set(COMPILE_TESTS FALSE CACHE BOOL "Set true if to compile tests")


add_library(${PROJECT_NAME} ${target_sources}
        src/MotorLn298.h
        src/MotorVelocityControl.cpp
        src/MotorVelocityControl.h
        src/MotorLn298.cpp
        src/SonarHcsr04.h
        src/SonarHcsr04.cpp
        src/Encoder.cpp
        src/Encoder.h
        src/Gpio.cpp src/Gpio.h)

set(test_sources test/csv.cpp test/csv.h)

if(COMPILE_FOR_PI)
    target_compile_definitions(${PROJECT_NAME} PUBLIC COMPILE_FOR_PI)
endif()

target_include_directories(${PROJECT_NAME} PUBLIC src)
target_include_directories(${PROJECT_NAME} PUBLIC include)

if(COMPILE_FOR_PI)
    target_link_libraries(${PROJECT_NAME} -lpigpio)
endif()

if(COMPILE_TESTS)
    add_executable(test_motor test/test_motor.cpp ${test_sources})
    add_executable(exp_pwm_to_rad test/exp_pwm_to_rad.cpp ${test_sources})
    add_executable(test_pid test/test_pid.cpp ${test_sources})
    add_executable(test_encoder test/test_encoder.cpp ${test_sources})
    add_executable(test_velocity_measurement test/test_velocity_measurement.cpp ${test_sources})
    add_executable(test_velocity_filter test/test_velocity_filter.cpp ${test_sources})

    target_link_libraries(test_motor ${PROJECT_NAME})
    target_link_libraries(exp_pwm_to_rad ${PROJECT_NAME})
    target_link_libraries(test_pid ${PROJECT_NAME})
    find_package(Threads REQUIRED)
    target_link_libraries(test_pid Threads::Threads)
    target_link_libraries(test_encoder ${PROJECT_NAME})
    target_link_libraries(test_velocity_measurement ${PROJECT_NAME})
    target_link_libraries(test_velocity_filter ${PROJECT_NAME})

endif()


