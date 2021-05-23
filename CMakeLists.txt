cmake_minimum_required(VERSION 3.17)
project(biologyn)

set(CMAKE_CXX_STANDARD 14)

find_package(nlohmann_json 3.2.0 REQUIRED)

add_executable(main.cpp src/Flora.cpp src/Flora.h src/Environment.cpp src/Environment.h src/Living.cpp src/Living.h src/Fauna.cpp src/Fauna.h src/Chaos.cpp src/Chaos.h src/FileParser.cpp src/FileParser.h)
target_link_libraries(nlohmann_json::nlohmann_json)
