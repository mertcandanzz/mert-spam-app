#pragma once

#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <furi.h>
#include <furi_hal_random.h>
#include <core/core_defines.h>
#include <gui/icon.h>

typedef union BleSpamMsg BleSpamMsg;

typedef struct {
    const Icon* icon;  // Can be NULL if no custom icon
    const char* (*get_name)(const BleSpamMsg* _msg);
    void (*make_packet)(uint8_t* out_size, uint8_t** out_packet, const BleSpamMsg* _msg);
} BleSpamProtocol;
