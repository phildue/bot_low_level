#https://github.com/a9183756-gh/Arduino-CMake-Toolchain
#cmake -DCMAKE_TOOLCHAIN_FILE=/path/to/Arduino-CMake-Toolchain

project(arduino_motor_control CXX)

add_executable(${PROJECT_NAME} src/motor_control.cpp)

target_link_libraries(${PROJECT_NAME} PUBLIC robopi-drivers-lib)
target_link_arduino_libraries(${PROJECT_NAME} PRIVATE core)
target_enable_arduino_upload(${PROJECT_NAME}) # This adds a target upload-my_executable

