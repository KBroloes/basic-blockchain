#include "common.h"
#include "ec.h"
#include "hash.h"

int uint2int() {

}

int ecdsa_sign() {
    uint8_t priv_bytes[32] = {
            0x72, 0x22, 0x5d, 0x04, 0x0a, 0x89, 0x5f, 0x93,
            0x28, 0x71, 0xb1, 0x26, 0xc4, 0xc4, 0x5f, 0xcf,
            0xf0, 0xb6, 0x01, 0xd5, 0x84, 0x11, 0x31, 0x64,
            0xec, 0x83, 0x19, 0x0e, 0x58, 0x52, 0xdb, 0x2b
    };
    const char message[] = "This is a very confidential message\n";

    EC_KEY *key;
    uint8_t digest[32];
    ECDSA_SIG *signature;
    uint8_t *der, *der_copy;
    size_t der_len;

    const char digest_exp[] = "4554813e91f3d5be790c7c608f80b2b00f3ea77512d49039e9e3dc45f89e2f01";

    /* */

    key = bbp_ec_new_keypair(priv_bytes);
    if (!key) {
        puts("Unable to create keypair");
        return -1;
    }

    bbp_sha256(digest, (uint8_t *)message, strlen(message));

    printf("\n====== ECDSA Sign =====\n");
    bbp_print_hex("digest      ", digest, 32);
    printf("digest (exp): %s\n", digest_exp);

    signature = ECDSA_do_sign(digest, sizeof(digest), key);
    printf("r: %s\n", BN_bn2hex(signature->r));
    printf("s: %s\n", BN_bn2hex(signature->s));

    der_len = ECDSA_size(key);
    der = calloc(der_len, sizeof(uint8_t));
    der_copy = der;
    i2d_ECDSA_SIG(signature, &der_copy);
    bbp_print_hex("DER-encoded", der, der_len);

    // Pretty printing:
    uint8_t type[2];
    int type_bytes = 2;
    int block_size = 32;
    uint8_t r[block_size];
    uint8_t s[block_size];

    memcpy(type, der, type_bytes);

    // Determine if the r length is 0x022100 or 0x0220
    int r_len_bytes = 2;
    if(der[type_bytes + r_len_bytes] == 0x00) {
        r_len_bytes = 3;
    }
    uint8_t r_length[r_len_bytes]; // Declare r_length
    memcpy(r_length, der + type_bytes, r_len_bytes); // Register it

    // Fast forward the type, and the length for r
    memcpy(r, der + type_bytes + r_len_bytes, block_size);

    // Determine if the s length is 0x022100 or 0x0220
    int s_len_bytes = 2;
    if(der[type_bytes + r_len_bytes + block_size + s_len_bytes] == 0x00) {
        s_len_bytes = 3;
    }
    uint8_t s_length[s_len_bytes]; // Declare s_length
    memcpy(s_length, der + type_bytes + r_len_bytes + block_size, s_len_bytes); // Register it

    // Fast forward the first component blocks, and the length
    memcpy(s, der + type_bytes + r_len_bytes + block_size + s_len_bytes, block_size);

    printf("=== DER components ===\n");
    bbp_print_hex("DER type component", type, sizeof(type));
    printf("== r ==\n");
    bbp_print_hex("DER r length component", r_length, sizeof(r_length));
    bbp_print_hex("DER r component", r, sizeof(r));
    printf("== s ==\n");
    bbp_print_hex("DER s length component", s_length, sizeof(s_length));
    bbp_print_hex("DER s component", s, sizeof(s));


    free(der);
    ECDSA_SIG_free(signature);
    EC_KEY_free(key);

    return 0;
}