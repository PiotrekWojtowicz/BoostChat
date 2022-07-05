#Project details
cmake_minimum_required(VERSION 3.22)
project(untitled)

#Setting cmake standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#Boost config section
include_directories("/home/user_me/Sys_Builds/boost_1_79_0/")
find_package(Boost COMPONENTS thread REQUIRED)

#Adding exec
add_executable(
        ${PROJECT_NAME}
        main.cpp
)

target_link_libraries(
        ${PROJECT_NAME}
        Boost::thread
)
