#include "integers.c"
#include "fixed-strings.c"
#include "hashes.c"
#include "varints.c"

int main() {

    serialize();
    fixed();
    hashes();
    varints();

    return 0;
}