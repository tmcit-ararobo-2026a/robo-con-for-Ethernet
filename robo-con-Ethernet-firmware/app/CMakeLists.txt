cmake_minimum_required(VERSION 3.22)

add_library(app STATIC
    src/app.cpp
    src/robot_ethernet.cpp
)

target_include_directories(app PUBLIC
    include
)
target_compile_features(app PUBLIC cxx_std_17)

target_link_libraries(app PRIVATE wiznet_ether)
target_link_libraries(app PRIVATE stm32cubemx)