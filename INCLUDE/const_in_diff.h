#ifndef CONST_IN_DIFF
#define CONST_IN_DIFF

#include"D:\STUDYC\My_labraries\colours.h"
#include<stdio.h>
#include<assert.h>

const int operation_word = 10;

enum math_comands
{
    ADD = '+',
    SUB = '-',
    DIV = '/',
    MUL = '*',
    POW = '^',

    SIN = 253,
    COS = 254,
    SQRT = 251,
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
    int value;
    //union value_t value;
    diff_node_t* left;
    diff_node_t* right;
};

#endif