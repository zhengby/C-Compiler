#include "defs.h"
#include "data.h"
#include "decl.h"

static int next(void) {
    int c;

    if (Putback) {
        c = Putback;
        Putback = 0;
        return c;
    }

    c = fgetc(Infile);
    if ('\n' == c) {
        Line++;
    }

    return c;
}

static void putback(int c) {
    Putback = c;
}

static int skip(void) {
    int c;

    c = next();

    while (' ' == c || '\t' == c || '\n' == c || '\r' == c || '\f' == c) {
        c = next();
    }
    return c;
}

static int chrops(char *s, int c) {
    char *p;

    p = strchr(s, c);
    return p ? p - s : -1;
}

static int scanint(int c) {
    int k = 0;
    int val = 0;

    // 114
    while ((k = chrops("0123456789", c)) >= 0) {
        val = val * 10 + k;
        c = next();
    }

    putback(c);
    return val;
}


int scan(struct token *t) {
    int c;

    c = skip();

    switch (c) {
    case EOF:
        return 0;
    case '+': 
        t->token = T_PLUS;
        break;
    case '-': 
        t->token = T_MINUS;
        break;
    case '*': 
        t->token = T_STAR;
        break;
    case '/': 
        t->token = T_SLASH;
        break;
    default:
        if (isdigit(c)) {
            t->intvalue = scanint(c);
            t->token = T_INTLIT;
            break;
        }
        printf("Unrecognised character %c on line %d\n", c, Line);
        exit(1);
    }

    return 1;
}

