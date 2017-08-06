#include "common.h"

int vardata() {
    uint8_t bytes[] = {
            0xfd, 0x0a, 0x00, 0xe3,
            0x03, 0x41, 0x8b, 0xa6,
            0x20, 0xe1, 0xb7, 0x83,
            0x60
    };
    size_t len;
    size_t varlen;
    uint8_t data[100] = { 0 };

    len = bbp_varint_get(bytes, &varlen); // fd reads int16. 0x000a = 10, meaning 10 bytes of data.
    memcpy(data, bytes + varlen, len); // varlen = 3, len = 10

    char expected[] = "e303418ba620e1b78360";

    printf("\n====== Vardata =====\n");
    bbp_print_hex(" Decoded", data, 10);
    printf("Expected: %s", expected);

    return 0;
}