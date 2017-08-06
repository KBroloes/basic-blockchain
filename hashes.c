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
    bbp_print_hex("single hash digest", digest, sizeof(digest));
    printf("   expected digest: %s\n", exp_digest);

    bbp_sha256(digest, digest, 32); // Double-hashing - a mystery of the bitcoin impl.
    memcpy(exp_digest, "90986ea4e28b847cc7f9beba87ea81b221ca6eaf9828a8b04c290c21d891bcda", 64); // assign new expected value.

    printf("\n");
    bbp_print_hex("double hash digest", digest, sizeof(digest));
    printf("   expected digest: %s\n", exp_digest);

    //Prepare 35 bytes for serialization
    uint8_t ser[35];

    *(uint16_t *)(ser) = bbp_eint16(BBP_LITTLE, prefix);
    memcpy(ser + 2, digest, 32);
    *(ser + 2 + 32) = suffix;

    char exp_ser[] = "7fd190986ea4e28b847cc7f9beba87ea81b221ca6eaf9828a8b04c290c21d891bcda8c";

    printf("\n");
    bbp_print_hex("serialization", ser, sizeof(ser));
    printf(" expected ser: %s\n", exp_ser);

    return 0;
}