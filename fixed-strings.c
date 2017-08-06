#include "common.h"
int fixed() {
    uint32_t n32 = 0x68f7a38b;
    char str[] = "FooBar";
    size_t str_len = 10;
    uint16_t n16 = 0xee12;

    // Find actual length and pad with difference
    size_t str_real_len = strlen(str);
    size_t str_pad_len = str_len - str_real_len;

    // Serialize to 16 byte array
    uint8_t ser[16];

    *(uint32_t *)(ser) = bbp_eint32(BBP_LITTLE, n32); // Serialize uint to little endian as usual
    memcpy(ser + 4, str, str_real_len); // memcpy to pointer from 4 bytes to eos
    if (str_pad_len > 0) {
        memset(ser + 4 + str_real_len, '\0', str_pad_len); // Pad the remaining bytes up to 10 if necessary
    }
    *(uint16_t *)(ser + 4 + str_len) = bbp_eint16(BBP_LITTLE, n16); // Serialize the remaining two bytes little endian

    char expectation[] = "8ba3f768466f6f4261720000000012ee";

    bbp_print_hex("Serialized", ser, sizeof(ser));
    printf("Expectation: %s", expectation);


    return 0;
}