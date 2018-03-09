#pragma once

#include <stdint.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

enum signal_bits_s {
    meta        = 0,
    queue       = 1,
    priority    = 2,
    message     = 3,
};

const char* meta_key_value();
size_t meta_key_len();

extern const uint16_t  current_version;

#ifdef __cplusplus
}/*extern "C"*/
#endif

