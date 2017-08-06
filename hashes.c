#include "common.h"
#include "hash.h"

int hashes() {
    char message[] = "Hello Bitcoin!";
    uint16_t prefix = 0xd17f;
    uint8_t suffix = 0x8c;
    uint8_t digest[32]; // Preallocate 32 bytes for the hash

    bbp_sha256(digest, (uint8_t *)message, strlen(message)); // Calculate digest of message
    char exp_digest[] = "518ad5a375fa52f84b2b3df7933ad685eb62cf69869a96731561f94d10826b5c"; // 256-bit/32 byte SHA-256 digest

    printf("\n====== Hashes =====\n");
    bbp_print_hex("         digest", digest, sizeof(digest));
    printf("expected digest: %s\n", exp_digest);

    return 0;
}