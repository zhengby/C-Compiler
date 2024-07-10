#include "defs.h"
#include "data.h"
#include "decl.h"

void match(int t, char *what) {
    if (Token.token == t) {
        scan(&Token);
    } else {
        printf("%s expeted on line %d\n", what, Line);
        exit(1);
    }
}

void semi(void) {
    match(T_SEMI, ";");
}