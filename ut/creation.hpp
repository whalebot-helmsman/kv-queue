#include <stdio.h>
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

TEST(CreationTest, you_create_storage_in_tmp_dir)
{
    const char* path = "/tmp/myqueue";
    std::string command("rm -rf ");
    command += path;

    system(command.c_str());

    kvqueue_leveldb_storage_t*  storage =   kvqueue_leveldb_storage_create();
    const char*                 error   =   kvqueue_leveldb_storage_open( storage
                                                                        , NULL
                                                                        , path    );
    ASSERT_STREQ(error, NULL);
    kvqueue_leveldb_storage_close(storage);
    kvqueue_leveldb_storage_destroy(storage);

    system(command.c_str());
}
