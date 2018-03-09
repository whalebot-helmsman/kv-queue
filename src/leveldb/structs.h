#include "leveldb/c.h"

struct kvqueue_leveldb_storage_s {
    leveldb_options_t*      options;
    leveldb_t*              storage;
    char*                   error_message;
    leveldb_readoptions_t*  read_options;
    leveldb_writeoptions_t* write_options;
};

