set(TITLE kvqueue)

set( CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c99" )
set( SOURCES leveldb/queue.c )

add_library(${TITLE} STATIC ${SOURCES})
INSTALL( TARGETS ${TITLE} DESTINATION lib )
