#include "integers.c"
#include "fixed-strings.c"
#include "hashes.c"
#include "varints.c"
#include "vardata.c"
#include "ec-keypair.c"
#include "ecdsa-sign.c"
#include "ecdsa-verify.c"

int main() {

    serialize();
    fixed();
    hashes();
    varints();
    vardata();
    keypair();
    ecdsa_sign();
    verify();

    return 0;
}