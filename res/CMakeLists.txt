message(STATUS "Using local raw sample data.")
configure_file(sample.txt "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/sample.txt" COPYONLY)
