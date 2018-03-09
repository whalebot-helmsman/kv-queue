#include <stddef.h>

#include "include/leveldb_queue.h"

struct kvqueue_leveldb_storage_s {
};

kvqueue_leveldb_storage_t* kvqueue_leveldb_storage_open(const char* path)
{
    return NULL;
}

void kvqueue_leveldb_storage_close(kvqueue_leveldb_storage_t* storage)
{
    return;
}
