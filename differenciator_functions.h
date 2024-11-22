#ifndef DIFF_FUNC
#define DIFF_FUNC

#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include"D:\STUDYC\My_labraries\colours.h"
#include<string.h>
#include<math.h>

const int size_limit = 500;
const int operation_word = 10;

enum types_for_diff
{
    NUM = 1,
    VAR = 2,
    OP  = 3,
};

enum math_comands
{
    ADD = '+',
    SUB = '-',
    DIV = '/',
    MUL = '*',

    SIN = 253,
    COS = 254,
    SQR = 251,
};

// union value_t
// {
//     char* op;
//     int  num;
//     char var; 
// };

struct diff_node_t
{
    types_for_diff type;
    int value;
    //union value_t value;
    diff_node_t* left;
    diff_node_t* right;
};

diff_node_t* ctor_node(types_for_diff type, /*union value_t*/ int value, diff_node_t* left, diff_node_t* right);
int tree_dtor(diff_node_t* root);
int dtor_node(diff_node_t* node_ptr);
int node_dump(diff_node_t* node);

diff_node_t* diff_reader(char argv[]);
diff_node_t* diff_reader_recursion(char* buffer);

double calculate_value(diff_node_t* node, double variable);

int latex_dump(diff_node_t* node, char argv[]);
int generate_latex_dump(diff_node_t* node, FILE* file);

int print_node_graph(diff_node_t* node, char argv[]);
int generate_graph(diff_node_t* node, FILE* file);

#endif