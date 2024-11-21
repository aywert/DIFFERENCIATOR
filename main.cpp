#include"differenciator_functions.h"

int main(void)
{
    diff_node_t* node_7 = ctor_node(NUM, 1000, 0, 0);
    diff_node_t* node_6 = ctor_node(NUM, 7, 0, 0);
    diff_node_t* node_5 = ctor_node(NUM, 3, 0, 0);
    diff_node_t* node_4 = ctor_node(VAR, 'x', 0, 0);
    diff_node_t* node_2 = ctor_node(OP, '+', node_4, node_5);
    diff_node_t* node_3 = ctor_node(OP, '-', node_7, node_6);
    diff_node_t* node_1 = ctor_node(OP, '/', node_2, node_3);

    node_dump(node_1);

    return 0;
}
