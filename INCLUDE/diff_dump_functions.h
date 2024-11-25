#ifndef DIFF_DUMP_FUNCTION
#define DIFF_DUMP_FUNCTION

#include"const_in_diff.h"
#include<stdio.h>
#include<assert.h>
#include<stdlib.h>

int node_dump(diff_node_t* node);

int print_node_graph(diff_node_t* node, const char* file);
int generate_graph(diff_node_t* node, FILE* file);

int latex_dump(diff_node_t* node, const char* file);
int generate_latex_dump(diff_node_t* node, FILE* file);

#endif