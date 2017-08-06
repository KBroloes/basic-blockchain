#include "integers.c"
#include "fixed-strings.c"
#include "hashes.c"
#include "varints.c"
#include "vardata.c"

int main() {

    serialize();
    fixed();
    hashes();
    varints();
    vardata();

    return 0;
}