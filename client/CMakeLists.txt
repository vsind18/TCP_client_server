cmake_minimum_required(VERSION 3.19)

project(client)

set(CMAKE_CXX_STANDARD 20)

add_executable(${PROJECT_NAME} client.cpp)

target_include_directories(${PROJECT_NAME}
    PUBLIC 
        networking
)

target_link_libraries(${PROJECT_NAME}
    PUBLIC
        networking
        ws2_32
)

