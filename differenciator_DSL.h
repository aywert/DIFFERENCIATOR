#ifndef DIFFERENCATOR_DSL
#define DIFFERENCATOR_DSL

#define _VAR(x) ctor_node(VAR, x, NULL, NULL)
#define _NUM(x) ctor_node(NUM, x, NULL, NULL)

#define _DIV(L, R) ctor_node(OP, '/', L, R)
#define _MUL(L, R) ctor_node(OP, '*', L, R)
#define _ADD(L, R) ctor_node(OP, '+', L, R)
#define _SUB(L, R) ctor_node(OP, '-', L, R)

#define _SQR(L) ctor_node(OP, '^', L)
#define _SIN(L) ctor_node(OP, 's', L)
#define _COS(L) ctor_node(OP, 'c', L)

#endif