#include <stdlib.h>
#include <string.h>

#include "include/leveldb_queue.h"
#include "src/leveldb/structs.h"

kvqueue_leveldb_queue_t* kvqueue_leveldb_queue_create()
{
    kvqueue_leveldb_queue_t* self = malloc(sizeof(kvqueue_leveldb_queue_t));
    self->parent        =   NULL;
    self->name          =   NULL;
    self->error_message =   NULL;
    self->order         =   kvqueue_queue_orders_unknown;
    return self;
}

void kvqueue_leveldb_queue_destroy(kvqueue_leveldb_queue_t* handler)
{
    if (NULL != handler->error_message) {
        leveldb_free(handler->error_message);
        handler->error_message  =   NULL;
    }

    if (NULL != handler->name) {
        free(handler->name);
        handler->name   =   NULL;
    }

    free(handler);
}

const char* kvqueue_leveldb_queue_attach( kvqueue_leveldb_storage_t* handler
                                        , kvqueue_leveldb_queue_t*   queue
                                        , const char*                name
                                        , kvqueue_queue_orders_e     order   )
{
    queue->parent   =   handler;
    queue->order    =   order;
    queue->name     =   malloc(strlen(name) + 1);
    strcpy(queue->name, name);

    return NULL;
}

const char* kvqueue_leveldb_queue_push( kvqueue_leveldb_queue_t*    queue
                                      , uint16_t                    priority
                                      , uint16_t                    size
                                      , const char*                 body     )
{
    return NULL;
}

const char* kvqueue_leveldb_queue_pop( kvqueue_leveldb_queue_t* queue
                                     , uint16_t*                size
                                     , char**                   body  )
{
    return NULL;
}
