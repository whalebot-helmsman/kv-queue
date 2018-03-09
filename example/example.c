#include <stdio.h>
#include <stdlib.h>

#include <cmdline_utils.h>
#include <cmdline_struct.h>

#include "include/leveldb_queue.h"

int main(int argc, char** argv)
{
    cmdline_option_parser_iface_t*  parser  =   cmdline_option_parser_iface_construct();
    parser->set_program_description(parser, "program to demonstrate libkvqueue abilities");
    parser->set_program_example(parser, parser->format(parser, "%s <path>", argv[0]));
    parser->add_help_flag(parser, 'h');

    parser->set_free_params_description(parser, "path to directory with queue");
    parser->set_free_params_requirement(parser, parser->REQUIRED);

    parser->full_parse(parser, argc, argv);
    cmdline_option_parser_free_params_iterator_t    iter    =   parser->free_params_begin(parser);
    const char*                                     path    =   *iter;
    parser->destruct(parser);


    kvqueue_leveldb_storage_t*  storage =   kvqueue_leveldb_storage_create();
    leveldb_options_t*          options =   kvqueue_leveldb_default_options();

    const char*                 error   =   kvqueue_leveldb_storage_open( storage
                                                                        , options
                                                                        , path    );
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
