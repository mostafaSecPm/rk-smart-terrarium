cmake_minimum_required(VERSION 3.10)
project(ClientServer)

set(CMAKE_CXX_STANDARD 17) # Set C++ version to C++17
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Specify the include directories for headers
include_directories(include)

# Add Executable for the Client
add_executable(client src/main_client.cpp src/Client.cpp)

# Add Executable for the Server
add_executable(server src/main_server.cpp src/Server.cpp)

target_link_libraries(client ws2_32)
target_link_libraries(server ws2_32)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fpermissive")

target_link_libraries(server ws2_32 kernel32 user32 gdi32 winspool shell32 ole32 oleaut32 uuid comdlg32 advapi32)

