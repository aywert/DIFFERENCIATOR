#ifndef DIFFERENCATOR_DSL
#define DIFFERENCATOR_DSL

#include"diff_reading_functions.h"

#define _VAR(x) ctor_node(VAR, x, NULL, NULL)
#define _NUM(x) ctor_node(NUM, x, NULL, NULL)

#define _DIV(L, R) ctor_node(OP, '/', L, R)
#define _MUL(L, R) ctor_node(OP, '*', L, R)
#define _ADD(L, R) ctor_node(OP, '+', L, R)
#define _SUB(L, R) ctor_node(OP, '-', L, R)
#define _POW(L, R) ctor_node(OP, '^', L, R)

#define _SIN(R) ctor_node(OP, 253, NULL, R)
#define _COS(R) ctor_node(OP, 254, NULL, R)
#define _SQRT(R) ctor_node(OP, 251, NULL, R)

#endif