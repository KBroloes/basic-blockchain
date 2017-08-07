#include "common.h"
#include "base58.h"
#include "hash.h"

int address() {
    uint8_t pub_bytes[33] = {
            0x02,
            0x0c, 0x8c, 0x6d, 0xf6, 0xc2, 0x18, 0x41, 0x6c,
            0xb8, 0x37, 0xf8, 0x6e, 0x8d, 0x4b, 0x82, 0xf8,
            0xc5, 0xb0, 0x69, 0xf6, 0x73, 0xad, 0xd5, 0xa6,
            0x6c, 0x30, 0x90, 0xb3, 0xb0, 0xb9, 0x4d, 0x8b
    };
    uint8_t address_bytes[21];
    char *address;

    const char address_exp[] = "n2sHbmWGTNxzxZpzrujoAyqxXgkTEfamQ5";

    printf("\n====== Address =====\n");

    address_bytes[0] = 0x6f; // Add testnet prefix (00 for mainnet)
    bbp_hash160(address_bytes + 1, pub_bytes, sizeof(pub_bytes)); // RIPEMD-160(SHA-256(pub))

    bbp_print_hex("Hash", address_bytes + 1, 20);
    bbp_print_hex("pub", pub_bytes, sizeof(pub_bytes));

    address = bbp_base58check(address_bytes, 21); // Encode to base58check (Hash256, append checksum, encode to base58)
    printf("Address      : %s\n", address);
    printf("Address (exp): %s\n", address_exp);
    free(address);

    return 0;
}