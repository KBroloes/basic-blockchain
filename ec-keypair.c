#include "common.h"
#include "ec.h"

int keypair() {
    uint8_t priv_bytes[32] = {
            0x72, 0x22, 0x5d, 0x04, 0x0a, 0x89, 0x5f, 0x93,
            0x28, 0x71, 0xb1, 0x26, 0xc4, 0xc4, 0x5f, 0xcf,
            0xf0, 0xb6, 0x01, 0xd5, 0x84, 0x11, 0x31, 0x64,
            0xec, 0x83, 0x19, 0x0e, 0x58, 0x52, 0xdb, 0x2b
    };

    EC_KEY *key;
    uint8_t priv[32];
    uint8_t *pub;
    const BIGNUM *priv_bn;

    point_conversion_form_t conv_forms[] = {
            POINT_CONVERSION_UNCOMPRESSED,
            POINT_CONVERSION_COMPRESSED
    };
    const char *conv_forms_desc[] = {
            "uncompressed",
            "compressed"
    };
    int i;

    const char priv_exp[] = "72225d040a895f932871b126c4c45fcff0b601d584113164ec83190e5852db2b";
    const char pub_exp[2][200] = {
            "040c8c6df6c218416cb837f86e8d4b82f8c5b069f673add5a66c3090b3b0b94d8b686972711e6b16f4ce7ef16059e0df0d1e67b108d199975927bc00a7cf8c49e8",
            "020c8c6df6c218416cb837f86e8d4b82f8c5b069f673add5a66c3090b3b0b94d8b"
    };

    /* create keypair */

    key = bbp_ec_new_keypair(priv_bytes);
    if (!key) {
        puts("Unable to create keypair");
        return -1;
    }
    bbp_print_hex("priv #1   ", priv_bytes, sizeof(priv));

    /* get private key back from EC_KEY */

    priv_bn = EC_KEY_get0_private_key(key);
    if (!priv_bn) {
        puts("Unable to decode private key");
        return -1;
    }
    BN_bn2bin(priv_bn, priv);

    printf("\n====== EC Keypair =====\n");
    bbp_print_hex("priv #2   ", priv, sizeof(priv));

    printf("priv (exp): %s\n", priv_exp);

    /* get encoded public key from EC_KEY in all conversion forms */

    for (i = 0; i < sizeof(conv_forms) / sizeof(point_conversion_form_t); ++i) {
        size_t pub_len;
        uint8_t *pub_copy;

        EC_KEY_set_conv_form(key, conv_forms[i]);

        pub_len = i2o_ECPublicKey(key, NULL);
        pub = calloc(pub_len, sizeof(uint8_t));

        /* pub_copy is needed because i2o_ECPublicKey alters the input pointer */
        pub_copy = pub;
        if (i2o_ECPublicKey(key, &pub_copy) != pub_len) {
            puts("Unable to decode public key");
            return -1;
        }

        printf("conversion form: %s\n", conv_forms_desc[i]);
        bbp_print_hex("pub      ", pub, pub_len);
        printf("pub (exp): %s\n", pub_exp[i]);

        free(pub);
    }

    /* release keypair */

    EC_KEY_free(key);

    return 0;
}