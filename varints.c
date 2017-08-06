#include "common.h"
#include "varint.h"

typedef struct {
    uint16_t fixed1;
    uint64_t var2;
    uint32_t fixed3;
    uint8_t fixed4;
} foo_t;

int varints() {
    uint8_t bytes[] = {
            0x13, 0x9c,
            0xfd, 0x7d, 0x80,
            0x44, 0x6b, 0xa2, 0x20,
            0xcc
    };

    foo_t decoded;
    size_t varlen;

    foo_t exp;
    exp.fixed1 = 0x9c13;
    exp.var2 = 0x807d;
    exp.fixed3 = 0x20a26b44;
    exp.fixed4 = 0xcc;

    // Varints can be up to 64 bytes long, and contain information about their length in the first byte. fd(16), fe(32), ff(64).
    decoded.fixed1 = bbp_eint16(BBP_LITTLE, *(uint16_t *)bytes); // int16, 9c13, 2 bytes
    decoded.var2 = bbp_varint_get(bytes + 2, &varlen); // Skip 2, encounter fd (varint16), read following 807d. varlen = 3 bytes
    decoded.fixed3 = bbp_eint32(BBP_LITTLE, *(uint32_t *)(bytes + 2 + varlen)); // int32, 202a6b44
    decoded.fixed4 = *(bytes + 2 + varlen + 4); // int8, cc

    printf("\n====== Varints =====\n");
    printf(" Decoded fixed1: %x\n", decoded.fixed1);
    printf("Expected fixed1: %x\n\n", exp.fixed1);
    printf(" Decoded var2: %llx\n", decoded.var2);
    printf("Expected var2: %llx\n\n", exp.var2);
    printf(" Decoded fixed3: %x\n", decoded.fixed3);
    printf("Expected fixed3: %x\n\n", exp.fixed3);
    printf(" Decoded fixed4: %x\n", decoded.fixed4);
    printf("Expected fixed4: %x\n", exp.fixed4);

    return 0;
}