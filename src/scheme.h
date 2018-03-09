#pragma once

#include <stdint.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef enum  {
    signal_bits_meta        = 0,
    signal_bits_queue       = 1,
    signal_bits_priority    = 2,
    signal_bits_message     = 3,
} signal_bits_e;

const char* meta_key_value();
size_t meta_key_len();

extern const uint16_t  current_version;

#ifdef __cplusplus
}/*extern "C"*/
#endif

