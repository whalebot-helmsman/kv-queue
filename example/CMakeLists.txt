set(TITLE example)

find_package(cmdline REQUIRED)

set( CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c99" )
set(SOURCES example.c)
include_directories( ${CMDLINE_INCLUDE_DIRS} )

add_executable(${TITLE} ${SOURCES})
target_link_libraries( ${TITLE} kvqueue
                                ${CMDLINE_LIBRARIES})
