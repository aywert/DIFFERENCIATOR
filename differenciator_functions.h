#include<stdio.h>
#include<stdlib.h>
#include<assert.h>

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
    diff_node_t* left;
    diff_node_t* right;
};

diff_node_t* ctor_node(types_for_diff type, int value, diff_node_t* left, diff_node_t* right);
int dtor_node(diff_node_t* node_ptr);
int node_dump(diff_node_t* node);
