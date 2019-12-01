cmake_minimum_required(VERSION 3.5)

# Set the project name
project (ngram_cli C CXX)

file(GLOB_RECURSE src
    ${CMAKE_CURRENT_LIST_DIR}/*.h
    ${CMAKE_CURRENT_LIST_DIR}/*.c
	${CMAKE_CURRENT_LIST_DIR}/*.cc
	${CMAKE_CURRENT_LIST_DIR}/*.cpp
)

# Add an executable for testing purpose
add_executable(ngram ${src})

target_link_libraries(ngram
    PUBLIC libngram
)

cotire(ngram)
