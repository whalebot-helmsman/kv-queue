#include "src/scheme.h"

const uint16_t  current_version = 1;

const char* meta_key_value()
{
    return "\0met";
}

size_t meta_key_len()
{
    return 4;
}

const char* queue_num_key_value()
{
    return "\0que";
}

size_t queue_num_key_len()
{
    return 4;
}

