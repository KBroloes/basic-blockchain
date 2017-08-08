#include "integers.c"
#include "fixed-strings.c"
#include "hashes.c"
#include "varints.c"
#include "vardata.c"
#include "ec-keypair.c"
#include "ecdsa-sign.c"
#include "ecdsa-verify.c"
#include "base58check.c"
#include "wif.c"
#include "address.c"
#include "tx-build.c"
#include "tx-sign.c"
#include "tx-pack.c"

int main() {

    serialize();
    fixed();
    hashes();
    varints();
    vardata();
    keypair();
    ecdsa_sign();
    verify();
    base58check();
    wif();
    address();
    tx_build();
    tx_sign();
    tx_pack();

    return 0;
}