cmake_minimum_required(VERSION 2.8)

set(CMAKE_CXX_FLAGS "-std=c++11 ${CMAKE_CXX_FLAGS}")

add_executable(pwm_control src/pwm_control.cpp)
add_executable(pwm_servo src/pwm_servo.cpp)
add_executable(pwm_servo4 src/pwm_servo4.cpp)

add_dependencies(pwm_control sysfspwm)

include_directories(${PROJECT_BINARY_DIR}/../lib/src/)


target_link_libraries(pwm_control sysfspwm)
target_link_libraries(pwm_servo sysfspwm)
target_link_libraries(pwm_servo4)
