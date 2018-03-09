#include <stdio.h>
#include <stdlib.h>

#include "include/leveldb_queue.h"

int main(int argc, char** argv)
{
    kvqueue_leveldb_storage_t*  storage =   kvqueue_leveldb_storage_create();
    leveldb_options_t*          options =   kvqueue_leveldb_default_options();

    const char*                 error   =   kvqueue_leveldb_storage_open( storage
                                                                        , options
                                                                        , "/home/hotdox/run/kvqueue/2018-03-09/" );
    if (NULL != error) {
        fprintf(stderr, error);
        leveldb_options_destroy(options);
        kvqueue_leveldb_storage_destroy(storage);
        return EXIT_FAILURE;
    }

    kvqueue_leveldb_storage_close(storage);
    kvqueue_leveldb_storage_destroy(storage);
    leveldb_options_destroy(options);
    return EXIT_SUCCESS;
}
