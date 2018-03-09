#include <gtest/gtest.h>

#include "include/leveldb_queue.h"

TEST(CreationTest, you_cannot_create_storage_in_root_dir)
{
    const char* path = "/root/myqueue";
    kvqueue_leveldb_storage_t*  storage =   kvqueue_leveldb_storage_create();
    const char*                 error   =   kvqueue_leveldb_storage_open( storage
                                                                        , NULL
                                                                        , path    );
    ASSERT_STRNE(error, NULL);
    kvqueue_leveldb_storage_destroy(storage);
}
