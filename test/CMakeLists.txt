
cmake_minimum_required(VERSION 2.8)

project(libngram_test C CXX)

file(GLOB_RECURSE src
    ${CMAKE_CURRENT_LIST_DIR}/*.h
    ${CMAKE_CURRENT_LIST_DIR}/*.hpp

    ${CMAKE_CURRENT_LIST_DIR}/*.c
	${CMAKE_CURRENT_LIST_DIR}/*.cc
	${CMAKE_CURRENT_LIST_DIR}/*.cpp
)

add_executable(libngram_test ${src})
target_link_libraries(libngram_test 
    PRIVATE libngram)

enable_testing()

add_test(NAME libngram_test COMMAND libngram_test)
