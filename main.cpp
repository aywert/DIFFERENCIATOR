#include"differenciator_functions.h"
#include"differenciator_DSL.h"

int main(void)
{
    // union value_t variable = {};
    // variable.var = 'x';
    // diff_node_t* special_node = _VAR(variable);

    //diff_node_t* special_node = _DIV(_ADD(_VAR('z'), _NUM(88)), _SUB(_NUM(8888), _NUM(88)));
    
    // node_dump(special_node);
    // printf(GREEN("\n====================\n"));
    // print_node_graph(special_node, argv[argc-3]);

    
    
    diff_node_t* node = diff_reader(file_for_reading);
    latex_dump(node, file_for_LATEX);
    node_dump(node);
    printf(GREEN("\n====================\n"));
    print_node_graph(node, file_for_graph);

    printf("Please enter value of variable x:");
    double variable = 0;
    scanf("%lg", &variable);
    double answer = calculate_value(node, variable);
    printf("%lg", answer);
    tree_dtor(node);
    return 0;
}
