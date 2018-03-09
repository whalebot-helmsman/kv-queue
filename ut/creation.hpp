#include <stdio.h>
#include <gtest/gtest.h>

#include "src/scheme.h"
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

TEST(CreationTest, you_cannot_open_queue_from_another_version)
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

    char*               message =   NULL;
    leveldb_options_t*  opts    =   leveldb_options_create();
    leveldb_t*          db      =   leveldb_open(opts, path, &message);
    ASSERT_TRUE(message == NULL);
    ASSERT_TRUE(db != NULL);

    uint16_t    next_version    =   current_version + 1;
    leveldb_writeoptions_t* write_opts  =   leveldb_writeoptions_create();
    leveldb_put( db
               , write_opts
               , meta_key_value()
               , meta_key_len()
               , (const char*)&next_version
               , sizeof(next_version)
               , &message );
    ASSERT_TRUE(message == NULL);

    leveldb_options_destroy(opts);
    leveldb_writeoptions_destroy(write_opts);
    leveldb_close(db);

    storage =   kvqueue_leveldb_storage_create();
    error   =   kvqueue_leveldb_storage_open( storage
                                            , NULL
                                            , path    );
    ASSERT_TRUE(error != NULL);
    kvqueue_leveldb_storage_destroy(storage);
}
