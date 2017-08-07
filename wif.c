#include "common.h"
#include "base58.h"
#include "hash.h"

int wif() {
    uint8_t priv_bytes[32] = {
            0x72, 0x22, 0x5d, 0x04, 0x0a, 0x89, 0x5f, 0x93,
            0x28, 0x71, 0xb1, 0x26, 0xc4, 0xc4, 0x5f, 0xcf,
            0xf0, 0xb6, 0x01, 0xd5, 0x84, 0x11, 0x31, 0x64,
            0xec, 0x83, 0x19, 0x0e, 0x58, 0x52, 0xdb, 0x2b
    };
    uint8_t wif_bytes[34];
    char *wif;

    const char wif_exp[] = "cRQZeSxDgzDKzLmaPtJPQ4Q725TsvyNMAFTXeG8QGryqx6QdBA8B";

    /* */
    printf("\n====== Wallet Import Format (WIF) =====\n");

    bbp_print_hex("priv", priv_bytes, sizeof(priv_bytes));

    wif_bytes[0] = 0xef; // Testnet version indicator
    memcpy(wif_bytes + 1, priv_bytes, 32);
    wif_bytes[33] = 0x01; // Uses compressed public key

    wif = bbp_base58check(wif_bytes, 34); // Encode to base58check (Hash256, append checksum, encode to base58)
    printf("WIF      : %s\n", wif);
    printf("WIF (exp): %s\n", wif_exp);
    free(wif);

    return 0;
}