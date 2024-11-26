#include"INCLUDE\\diff_reading_functions.h"
#include"INCLUDE\\diff_dump_functions.h"
#include"INCLUDE\\diff_derivative_functions.h"
#include"INCLUDE\\differenciator_DSL.h"

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
    
    node_dump(node);
    printf(GREEN("\n====================\n"));
    
    // latex_dump(node, file_for_LATEX);
    // print_node_graph(node, file_for_graph);
                // printf("Please enter value of variable x:");
                // double variable = 0;
                // scanf("%lg", &variable);
                // double answer = calculate_value(node, variable);
                // printf("%lg\n", answer);
    diff_node_t* diffed_node = {};
    diffed_node = get_derivative_of_node(node);
    latex_dump(diffed_node, file_for_LATEX);
    print_node_graph(diffed_node, file_graph_input);

    // printf("%s", __FUNCTION__);
    // printf("what above is me!\n");
    // printf("^ = %d\n", '^');
    tree_dtor(node);
    tree_dtor(diffed_node);

    return 0;
}
