#include "common.h"
#include "ec.h"
#include "hash.h"

int verify() {
    uint8_t pub_bytes[33] = {
            0x02, 0x0c, 0x8c, 0x6d, 0xf6, 0xc2, 0x18, 0x41,
            0x6c, 0xb8, 0x37, 0xf8, 0x6e, 0x8d, 0x4b, 0x82,
            0xf8, 0xc5, 0xb0, 0x69, 0xf6, 0x73, 0xad, 0xd5,
            0xa6, 0x6c, 0x30, 0x90, 0xb3, 0xb0, 0xb9, 0x4d,
            0x8b
    };
    uint8_t der_bytes[] = {
            0x30, 0x44,
            0x02, 0x20,
            0x49, 0x11, 0x36, 0x39, 0x09, 0xd5, 0x8b, 0xee,
            0xae, 0x0e, 0xe8, 0x76, 0x4f, 0x96, 0x20, 0x3a,
            0xdc, 0xd8, 0xdc, 0x52, 0x6e, 0xdd, 0x40, 0x97,
            0xe2, 0xd2, 0x95, 0x73, 0xeb, 0x27, 0x0c, 0x7d,
            0x02, 0x20,
            0x62, 0xa8, 0x12, 0xfb, 0x02, 0x31, 0xf3, 0x9d,
            0x0a, 0x14, 0x60, 0x71, 0x3e, 0xbd, 0x4e, 0xa8,
            0x21, 0xd7, 0x86, 0xb9, 0xbb, 0xa9, 0x8c, 0xbf,
            0x00, 0xb6, 0xea, 0x2b, 0xd8, 0xc6, 0xef, 0xc4,
            0x00, 0x00
    };
    const char message[] = "This is a very confidential message\n";

    EC_KEY *key;
    const uint8_t *der_bytes_copy;
    ECDSA_SIG *signature;
    uint8_t digest[32];
    int verified;

    const char *r_exp = "B92CAE5E4C9AFA1238A3AF7F5F4849EDFEFBD7910480717F97D404CC521626F5";
    const char *s_exp = "4E8D1718C909AAB25A72AF2AB63F5C2438A602FA922FC55146FCB2B8AA3BED21";
    const char *digest_exp = "4554813e91f3d5be790c7c608f80b2b00f3ea77512d49039e9e3dc45f89e2f01";

    /* */

    key = bbp_ec_new_pubkey(pub_bytes, sizeof(pub_bytes));
    if (!key) {
        puts("Unable to create keypair");
        return -1;
    }

    der_bytes_copy = der_bytes;
    signature = d2i_ECDSA_SIG(NULL, &der_bytes_copy, sizeof(der_bytes));
    printf("\n====== ECDSA Verify =====\n");
    printf("r      : %s\n", BN_bn2hex(signature->r));
    printf("r (exp): %s\n", r_exp);
    printf("s      : %s\n", BN_bn2hex(signature->s));
    printf("s (exp): %s\n", s_exp);

    bbp_sha256(digest, (uint8_t *)message, strlen(message));
    bbp_print_hex("digest      ", digest, 32);
    printf("digest (exp): %s\n", digest_exp);
    verified = ECDSA_do_verify(digest, sizeof(digest), signature, key);

    switch (verified) {
        case 1:
            puts("verified");
            break;
        case 0:
            puts("not verified");
            break;
        case -1:
            puts("library error");
            break;
    }

    ECDSA_SIG_free(signature);
    EC_KEY_free(key);

    return 0;
}