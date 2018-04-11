#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>

#include "include/leveldb_queue.h"
#include "src/leveldb/structs.h"
#include "src/scheme.h"

const char* kvqueue_leveldb_storage_check_version(kvqueue_leveldb_storage_t* handler)
{
    const char* WRONG_SIZE_ERROR    =   "Wrong size of meta value";
    const char* WRONG_VERSION_ERROR =   "Wrong version of storage file";

    size_t  version_size    =   0;
    char*   version         =   leveldb_get( handler->storage
                                           , handler->read_options
                                           , meta_key_value()
                                           , meta_key_len()
                                           , &version_size
                                           , &handler->error_message );

    if (NULL != handler->error_message) {
        return handler->error_message;
    }

    if ((NULL != version) && (sizeof(uint16_t) != version_size)) {
        leveldb_free(version);
        handler->error_message = malloc(strlen(WRONG_SIZE_ERROR) + 1);
        strcpy(handler->error_message, WRONG_SIZE_ERROR);
        return handler->error_message;
    }

    if ((NULL != version) && (sizeof(uint16_t) == version_size) && (current_version != *(uint16_t*)(version))) {
        leveldb_free(version);
        handler->error_message = malloc(strlen(WRONG_VERSION_ERROR) + 1);
        strcpy(handler->error_message, WRONG_VERSION_ERROR);
        return handler->error_message;
    }

    if ((NULL != version) && (sizeof(uint16_t) == version_size) && (current_version == *(uint16_t*)(version))) {
        leveldb_free(version);
        return NULL;
    }

    leveldb_put( handler->storage
               , handler->write_options
               , meta_key_value()
               , meta_key_len()
               , (const char*)&current_version
               , sizeof(current_version)
               , &handler->error_message );

    return handler->error_message;
}

kvqueue_leveldb_storage_t* kvqueue_leveldb_storage_create()
{
    kvqueue_leveldb_storage_t* self = malloc(sizeof(kvqueue_leveldb_storage_t));
    self->options       =   NULL;
    self->storage       =   NULL;
    self->error_message =   NULL;
    self->write_options =   NULL;
    self->read_options  =   NULL;
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
    leveldb_options_t* opts =   options;
    if (NULL == opts) {
        handler->options    =   kvqueue_leveldb_default_options();
        opts                =   handler->options;
    }

    handler->storage    =   leveldb_open(opts, path, &handler->error_message);

    if (NULL == handler->storage) {
        return handler->error_message;
    }

    handler->read_options   =   leveldb_readoptions_create();
    handler->write_options  =   leveldb_writeoptions_create();

    const char* error   =   kvqueue_leveldb_storage_check_version(handler);
    if (NULL == error) {
        return NULL;
    }

    kvqueue_leveldb_storage_close(handler);
    return error;
}

void kvqueue_leveldb_storage_close(kvqueue_leveldb_storage_t* handler)
{
    leveldb_close(handler->storage);
}

void kvqueue_leveldb_storage_destroy(kvqueue_leveldb_storage_t* handler)
{
    if (NULL != handler->read_options) {
        leveldb_readoptions_destroy(handler->read_options);
        handler->read_options   =   NULL;
    }

    if (NULL != handler->write_options) {
        leveldb_writeoptions_destroy(handler->write_options);
        handler->write_options  =   NULL;
    }

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
