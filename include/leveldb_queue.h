#pragma once

#include "leveldb/c.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef enum  {
    kvqueue_queue_orders_fifo    =   2,
    kvqueue_queue_orders_lifo    =   1,
    kvqueue_queue_orders_unknown =   0,
} kvqueue_queue_orders_e;

typedef struct kvqueue_leveldb_storage_s kvqueue_leveldb_storage_t;

kvqueue_leveldb_storage_t* kvqueue_leveldb_storage_create();
leveldb_options_t* kvqueue_leveldb_default_options();
const char* kvqueue_leveldb_storage_open( kvqueue_leveldb_storage_t* handler
                                        , leveldb_options_t*         options
                                        , const char*                path    );
void kvqueue_leveldb_storage_close(kvqueue_leveldb_storage_t* handler);
void kvqueue_leveldb_storage_destroy(kvqueue_leveldb_storage_t* handler);
const char* kvqueue_leveldb_storage_queue_number( kvqueue_leveldb_storage_t* handler
                                                , uint16_t*                  queue_number );

typedef struct kvqueue_leveldb_queue_s kvqueue_leveldb_queue_t;
kvqueue_leveldb_queue_t* kvqueue_leveldb_queue_create();
void kvqueue_leveldb_queue_destroy(kvqueue_leveldb_queue_t* handler);

const char* kvqueue_leveldb_queue_attach( kvqueue_leveldb_storage_t* handler
                                        , kvqueue_leveldb_queue_t*   queue
                                        , const char*                name
                                        , kvqueue_queue_orders_e     order   );

const char* kvqueue_leveldb_queue_push( kvqueue_leveldb_queue_t*    queue
                                      , uint16_t                    priority
                                      , uint16_t                    size
                                      , const char*                 body     );

const char* kvqueue_leveldb_queue_pop( kvqueue_leveldb_queue_t* queue
                                     , uint16_t*                size
                                     , char**                   body  );
#ifdef __cplusplus
}/*extern "C"*/
#endif

