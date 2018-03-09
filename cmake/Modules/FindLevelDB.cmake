# - Try to find leveldb
# Once done this will define
#  LEVELDB_FOUND - System has leveldb
#  LEVELDB_INCLUDE_DIRS - The leveldb include directories
#  LEVELDB_LIBRARIES - The libraries needed to use leveldb
#  LEVELDB_DEFINITIONS - Compiler switches required for using leveldb

find_package(PkgConfig)
pkg_check_modules(PC_LEVELDB QUIET leveldb)
set(LEVELDB_DEFINITIONS ${PC_LEVELDB_CFLAGS_OTHER})

find_path(LEVELDB_INCLUDE_DIR NAMES leveldb/db.h
          HINTS ${PC_LEVELDB_INCLUDEDIR} ${PC_LEVELDB_INCLUDE_DIRS} )

find_library(LEVELDB_LIBRARY NAMES leveldb libleveldb
             HINTS ${PC_LEVELDB_LIBDIR} ${PC_LEVELDB_LIBRARY_DIRS} )

set(LEVELDB_LIBRARIES ${LEVELDB_LIBRARY})
set(LEVELDB_INCLUDE_DIRS ${LEVELDB_INCLUDE_DIR})

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(leveldb  DEFAULT_MSG
                                  LEVELDB_LIBRARY LEVELDB_INCLUDE_DIR)

mark_as_advanced(LEVELDB_INCLUDE_DIR LEVELDB_LIBRARY )
