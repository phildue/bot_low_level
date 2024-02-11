
set(test_sources csv.h csv.cpp)

add_executable(test_motor test_motor.cpp ${test_sources})
add_executable(exp_pwm_to_rad exp_pwm_to_rad.cpp ${test_sources})
add_executable(test_pid test_pid.cpp ${test_sources})
add_executable(test_encoder test_encoder.cpp ${test_sources})
add_executable(test_velocity_measurement test_velocity_measurement.cpp ${test_sources})
add_executable(test_velocity_filter test_velocity_filter.cpp ${test_sources})

target_link_libraries(test_motor bot_low_level)
target_link_libraries(exp_pwm_to_rad bot_low_level)
target_link_libraries(test_pid bot_low_level)
find_package(Threads REQUIRED)
target_link_libraries(test_pid Threads::Threads)
target_link_libraries(test_encoder bot_low_level)
target_link_libraries(test_velocity_measurement bot_low_level)
target_link_libraries(test_velocity_filter bot_low_level)
