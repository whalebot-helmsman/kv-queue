#pragma once

#ifdef __cplusplus
extern "C" {
#endif

typedef struct kvqueue_leveldb_storage_s kvqueue_leveldb_storage_t;

kvqueue_leveldb_storage_t* kvqueue_leveldb_storage_open(const char* path);
void kvqueue_leveldb_storage_close(kvqueue_leveldb_storage_t* storage);

#ifdef __cplusplus
}/*extern "C"*/
#endif

