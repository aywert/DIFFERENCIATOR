#ifndef CONST_IN_DIFF
#define CONST_IN_DIFF

#include"D:\STUDYC\My_labraries\colours.h"
#include<stdio.h>
#include<assert.h>

const int operation_word = 10;
const int inf = 999999;

typedef double dvalue_t;

enum math_comands
{
    ADD = '+',
    SUB = '-',
    DIV = '/',
    MUL = '*',
    POW = '^',
    LOG = 249,
    LN  = 250,

    SQRT = 251,
    SIN = 253,
    COS = 254,
    
};

enum types_for_diff
{
    NUM = 1,
    VAR = 2,
    OP  = 3,
};

struct diff_node_t
{
    types_for_diff type;
    dvalue_t value;
    //union value_t value;
    diff_node_t* left;
    diff_node_t* right;
};

#endif