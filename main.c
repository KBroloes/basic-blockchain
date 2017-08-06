#include "integers.c"
#include "fixed-strings.c"
#include "hashes.c"
#include "varints.c"
#include "vardata.c"
#include "ec-keypair.c"

int main() {

    serialize();
    fixed();
    hashes();
    varints();
    vardata();
    keypair();

    return 0;
}