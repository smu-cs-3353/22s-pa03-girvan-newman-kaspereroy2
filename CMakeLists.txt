# Version Requirement
cmake_minimum_required(VERSION 3.15)

# Project Name
project(22s-pa03-girvan-newman-kaspereroy2)

# Executable
add_executable(22s-pa03-girvan-newman-kaspereroy2 src/main.cpp src/GraphHandler.h)

# Configure Files
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/data DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

# Boost Basic Settings
set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)

# Finds Boost Packages (Minimum 1.71.0 Requirement, Will Output)
find_package(Boost 1.71.0 REQUIRED COMPONENTS graph system filesystem)
message(STATUS "Boost version: ${Boost_VERSION}")

# Linking Correct Libraries (In Find Package) (Must End File)
target_link_libraries(22s-pa03-girvan-newman-kaspereroy2
        PUBLIC Boost::graph
        PUBLIC Boost::system
        PUBLIC Boost::filesystem)