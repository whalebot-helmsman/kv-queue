#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>

#include "include/leveldb_queue.h"

struct kvqueue_leveldb_storage_s {
    leveldb_options_t*  options;
    leveldb_t*          storage;
    char*               error_message;
};

kvqueue_leveldb_storage_t* kvqueue_leveldb_storage_create()
{
    kvqueue_leveldb_storage_t* self = malloc(sizeof(kvqueue_leveldb_storage_t));
    self->options       =   NULL;
    self->storage       =   NULL;
    self->error_message =   NULL;
    return self;
}

leveldb_options_t* kvqueue_leveldb_default_options()
{
    leveldb_options_t* options  =   leveldb_options_create();
    leveldb_options_set_create_if_missing(options, 1);
    return options;
}

const char* kvqueue_leveldb_storage_open( kvqueue_leveldb_storage_t* handler
                                        , leveldb_options_t*         options
                                        , const char*                path    )
{
    char*  error_message    =   NULL;

    leveldb_options_t* opts =   options;
    if (NULL == opts) {
        handler->options    =   kvqueue_leveldb_default_options();
        opts                =   handler->options;
    }

    handler->storage    =   leveldb_open(opts, path, &handler->error_message);

    if (NULL != handler->storage) {
        return NULL;
    }

    return handler->error_message;
}

void kvqueue_leveldb_storage_close(kvqueue_leveldb_storage_t* handler)
{
    leveldb_close(handler->storage);
}

void kvqueue_leveldb_storage_destroy(kvqueue_leveldb_storage_t* handler)
{
    if (NULL != handler->error_message) {
        leveldb_free(handler->error_message);
        handler->error_message  =   NULL;
    }

    if (NULL != handler->options) {
        leveldb_options_destroy(handler->options);
        handler->options    =   NULL;
    }
    free(handler);
}
