#include"differenciator_functions.h"
#include"differenciator_DSL.h"

int main(int argc, char* argv[])
{
    // union value_t variable = {};
    // variable.var = 'x';
    // diff_node_t* special_node = _VAR(variable);

    diff_node_t* special_node = _DIV(_ADD(_VAR('x'), _NUM(3)), _SUB(_NUM(1000), _NUM(7)));
    
    node_dump(special_node);
    printf(GREEN("\n====================\n"));
    print_node_graph(special_node, argv[argc-2]);
    latex_dump(special_node, argv[argc-1]);
    

    tree_dtor(special_node);
    return 0;
}
