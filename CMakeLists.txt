cmake_minimum_required(VERSION 4.1.0)

project(Sandbox VERSION 0.1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_subdirectory(Salt/)

add_executable(Sandbox
	SandBox.cpp
)

target_link_libraries(Sandbox PUBLIC Salt)
