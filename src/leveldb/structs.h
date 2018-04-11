#pragma once

#include "leveldb/c.h"

#ifdef __cplusplus
extern "C" {
#endif

struct kvqueue_leveldb_storage_s {
    leveldb_options_t*      options;
    leveldb_t*              storage;
    char*                   error_message;
    leveldb_readoptions_t*  read_options;
    leveldb_writeoptions_t* write_options;
};

struct kvqueue_leveldb_queue_s {
    kvqueue_leveldb_storage_t*  parent;
    char*                       name;
    char*                       error_message;
    kvqueue_queue_orders_e      order;
};

#ifdef __cplusplus
}/*extern "C"*/
#endif

