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

static int scanident(int c, char *buf, int lim) {
    int i = 0;

    while (isalpha(c) || isdigit(c) || '_' == c) {
        if (lim - 1 == i) {
            printf("identifier too long on line %d\n", Line);
            exit(1);
        } else if (i < lim - 1) {
            buf[i++] = c;
        }
        c = next();
    }

    putback(c);
    buf[i] = '\0';
    return i;
}


static int keyword(char *s) {
    switch (*s) {
        case 'p':
            if (!strcmp(s, "print")) {
                return T_PRINT;
            }
            break;
    }
    return 0;
}

int scan(struct token *t) {
    int c, tokentype;

    c = skip();

    switch (c) {
    case EOF:
        t->token = T_EOF;
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
    case ';': 
        t->token = T_SEMI;
        break;
    default:
        if (isdigit(c)) {
            t->intvalue = scanint(c);
            t->token = T_INTLIT;
            break;
        } else if (isalpha(c) || '_' == c) {
            scanident(c, Text, TEXTLEN);
            // 关键字
            if (tokentype = keyword(Text)) {
                t->token = tokentype;
                break;
            }
            // 非关键字
            printf("Unrecognis symbol %s on line %d\n", Text, Line);
            exit(1);
        }
        printf("Unrecognised character %c on line %d\n", c, Line);
        exit(1);
    }
    return 1;
}

