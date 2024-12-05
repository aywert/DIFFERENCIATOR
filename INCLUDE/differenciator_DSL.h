
#ifndef DIFFERENCATOR_DSL
#define DIFFERENCATOR_DSL

#include"diff_reading_functions.h"

#define _VAR(x) ctor_node(VAR, (dvalue_t)x, NULL, NULL)
#define _NUM(x) ctor_node(NUM, (dvalue_t)x, NULL, NULL)

#define _DIV(L, R)  ctor_node(OP, (dvalue_t)47, L, R)
#define _MUL(L, R)  ctor_node(OP, (dvalue_t)42, L, R)
#define _ADD(L, R)  ctor_node(OP, (dvalue_t)43, L, R)
#define _SUB(L, R)  ctor_node(OP, (dvalue_t)45, L, R)
#define _POW(L, R)  ctor_node(OP, (dvalue_t)94, L, R)

#define _SIN(R)     ctor_node(OP, (dvalue_t)253, NULL, R)
#define _COS(R)     ctor_node(OP, (dvalue_t)254, NULL, R)
#define _SQRT(R)    ctor_node(OP, (dvalue_t)251, NULL, R)
#define _LOG(L, R)  ctor_node(OP, (dvalue_t)249, L, R)
#define _LN(R)      ctor_node(OP, (dvalue_t)250, NULL, R)

#endif
