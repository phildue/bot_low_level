project(robopi-drivers-lib)

set(COMPILE_FOR_PI TRUE CACHE BOOL "Set true if compile for pi")

add_library(${PROJECT_NAME}
        include/robopi_drivers/robopi_drivers.h
        src/MotorLn298.h
        src/MotorVelocityControl.cpp
        src/MotorVelocityControl.h
        src/MotorLn298.cpp
        src/SonarHcsr04.h
        src/SonarHcsr04.cpp
        src/Encoder.cpp
        src/Encoder.h
        src/Gpio.cpp src/Gpio.h)


if(COMPILE_FOR_PI)
    target_compile_definitions(${PROJECT_NAME} PUBLIC COMPILE_FOR_PI)
    target_link_libraries(${PROJECT_NAME} -lpigpio)
endif()

target_include_directories(${PROJECT_NAME} PUBLIC src)
target_include_directories(${PROJECT_NAME} PUBLIC include)

