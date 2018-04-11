#include <stdlib.h>
#include <string.h>

#include "include/leveldb_queue.h"
#include "src/leveldb/structs.h"
#include "src/scheme.h"
#include "src/errors.h"

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

const char* kvqueue_leveldb_storage_queue_number( kvqueue_leveldb_storage_t* handler
                                                , uint16_t*                  queue_number )
{
    size_t  queue_number_size   =   0;
    char*   queue_number_ptr    =   leveldb_get( handler->storage
                                               , handler->read_options
                                               , queue_num_key_value()
                                               , queue_num_key_len()
                                               , &queue_number_size
                                               , &handler->error_message );

    if (NULL != handler->error_message) {
        return handler->error_message;
    }

    if (NULL == queue_number_ptr) {
        *queue_number   =   0;
        return NULL;
    }

    if ((NULL != queue_number_ptr) && (queue_number_size != sizeof(uint16_t))) {
        leveldb_free(queue_number_ptr);
        handler->error_message = malloc(strlen(WRONG_QUEUE_NUM_SIZE_ERROR) + 1);
        strcpy(handler->error_message, WRONG_QUEUE_NUM_SIZE_ERROR);
        return handler->error_message;
    }

    if ((NULL != queue_number_ptr) && (sizeof(uint16_t) == queue_number_size)) {
        *queue_number   =   *(uint16_t*)queue_number_ptr;
        leveldb_free(queue_number_ptr);
        return NULL;
    }
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
