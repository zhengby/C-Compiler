#include "defs.h"
#include "data.h"
#include "decl.h"

int arithop(int token) {
    switch (token) {
    case T_PLUS:
        return A_ADD;
    case T_MINUS:
        return A_SUBTRACT;
    case T_STAR:
        return A_MULTIPLY;
    case T_SLASH:
        return A_DIVIDE;
    default:
        fprintf(stderr, "unknown token %d in arithop() on line %d\n", token, Line);
        exit(1);
    }
}

//                     EOF +   -   *   /  INTLIT
static int OpPrec[] = { 0, 10, 10, 20, 20, 0 };

static int op_precedence(int tokentype) {
    int prec = OpPrec[tokentype];
    if (prec == 0) {
        fprintf(stderr, "syntax error on line %d, token %d\n", Line, tokentype);
        exit(1);
    }
    return prec;
}


static struct ASTnode *primary(void) {
    struct ASTnode *n;
    switch (Token.token) {
    case T_INTLIT:
        n = mkastleaf(A_INTLIT, Token.intvalue);
        scan(&Token);
        return n; 
    default:
        fprintf(stderr, "syntax error on line %d\n", Line);
        exit(1);
    }
}

struct ASTnode *binexpr(int ptp) {
    struct ASTnode *n, *left, *right;
    int tokentype;

    left = primary();

    tokentype = Token.token;
    if (tokentype == T_SEMI) {
        return left;
    }

    while (op_precedence(tokentype) > ptp) {
        scan(&Token);
        right = binexpr(OpPrec[tokentype]);
        left = mkastnode(arithop(tokentype), left, right, 0);

        tokentype = Token.token;
        if (tokentype == T_SEMI) {
            return left;
        }
    }

    return left;
}