cmake_minimum_required(VERSION 3.20)

project(DirectedGraphExample LANGUAGES CXX)

# Set the C++ standard to C++20
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Enable modules support (depends on your compiler, GCC 11+, Clang 13+, MSVC 19.30+)
if(NOT MSVC)
    add_compile_options(-fmodules-ts)
endif()

# Create a library target for the graph module
add_library(directed_graph_to_dot STATIC directed_graph_to_dot.cpp directed_graph.cpp graph_node.cpp)

# Ensure the library is compiled with modules support
if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU" OR CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    target_compile_options(directed_graph_to_dot PRIVATE -fmodules-ts)
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    target_compile_options(directed_graph_to_dot PRIVATE /std:c++20)
endif()

# Create an executable target for the test program
add_executable(test_executable test.cpp)

# Link the directed graph library to the test executable
target_link_libraries(test_executable PRIVATE directed_graph_to_dot)

# Include directories for the project
target_include_directories(directed_graph_to_dot PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(test_executable PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# Optionally, set up precompiled headers for faster compilation (if supported by your compiler)
# target_precompile_headers(directed_graph_to_dot PRIVATE <header_name>)
