cmake_minimum_required(VERSION 3.19)

project(TCP_client_server)
set(CMAKE_CXX_STANDARD 20)

add_subdirectory(client)
add_subdirectory(server)
add_subdirectory(networking)