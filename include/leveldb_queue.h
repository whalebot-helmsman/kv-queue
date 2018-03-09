#pragma once

#include "leveldb/c.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct kvqueue_leveldb_storage_s kvqueue_leveldb_storage_t;

kvqueue_leveldb_storage_t* kvqueue_leveldb_storage_create();
leveldb_options_t* kvqueue_leveldb_default_options();
const char* kvqueue_leveldb_storage_open( kvqueue_leveldb_storage_t* handler
                                        , leveldb_options_t*         options
                                        , const char*                path    );
void kvqueue_leveldb_storage_close(kvqueue_leveldb_storage_t* handler);
void kvqueue_leveldb_storage_destroy(kvqueue_leveldb_storage_t* handler);

#ifdef __cplusplus
}/*extern "C"*/
#endif

