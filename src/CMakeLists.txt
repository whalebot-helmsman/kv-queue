set(TITLE kvqueue)

find_package(LevelDB REQUIRED)

set( CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c99" )

include_directories( ${LEVELDB_INCLUDE_DIRS} )
set( SOURCES leveldb/queue.c )

add_library(${TITLE} STATIC ${SOURCES})
INSTALL( TARGETS ${TITLE} DESTINATION lib )
target_link_libraries( ${TITLE} ${LEVELDB_LIBRARIES}
                                ${SNAPPY_LIBRARIES}  )

