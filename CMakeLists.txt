cmake_minimum_required(VERSION 2.6)

project(LIBKVQUEUE)

set(LIBKVQUEUE_SRC_ROOT ${CMAKE_CURRENT_SOURCE_DIR})
set(LIBKVQUEUE_BUILD_ROOT ${CMAKE_CURRENT_BINARY_DIR})
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${LIBKVQUEUE_BUILD_ROOT}/lib" )
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${LIBKVQUEUE_BUILD_ROOT}/lib" )
set(EXECUTABLE_OUTPUT_PATH         "${LIBKVQUEUE_BUILD_ROOT}/bin" )

set(CMAKE_C_FLAGS   "${CMAKE_C_FLAGS}   -Wall -pedantic -Wextra")

include_directories(${LIBKVQUEUE_SRC_ROOT})
add_subdirectory(src)
add_subdirectory(example)

find_package(GTest)
find_package(Threads)
if (GTEST_FOUND AND Threads_FOUND)
    enable_testing()
    add_subdirectory(ut)
else(GTEST_FOUND AND Threads_FOUND)
    message(STATUS "No gtest or pthreads found - test not build")
endif(GTEST_FOUND AND Threads_FOUND)

FILE( GLOB LIBKVQUEUE_HEADERS "${CMAKE_CURRENT_SOURCE_DIR}/include/*.h" )
INSTALL( FILES ${LIBKVQUEUE_HEADERS} DESTINATION include)
# uninstall target
configure_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/cmake_uninstall.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake"
    IMMEDIATE @ONLY)

add_custom_target(uninstall
    COMMAND ${CMAKE_COMMAND} -P ${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake)
