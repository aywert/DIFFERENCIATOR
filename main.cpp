#include"INCLUDE\\diff_reading_functions.h"
#include"INCLUDE\\diff_dump_functions.h"
#include"INCLUDE\\diff_derivative_functions.h"
#include"INCLUDE\\differenciator_DSL.h"

int main(void)
{ 
    diff_node_t* node = diff_reader(file_for_reading);
    // diff_node_t* node_1 = diff_reader(file_for_reading);
    // diff_node_t* node_2 = diff_reader(file_for_reading);
    // latex_dump(node, file_for_LATEX);
    // print_node_graph(node, file_graph_input);
    // node_1->left->value = 9999;
    // //  node_dump(node);
    // //  printf("\n");
    // node_dump(node_1);
    // printf("\n");
    // node_dump(node_2);
    // int a = compare_tree(node_1, node_2);
    
    // printf(GREEN("a = %d\n"), a);
    // node_dump(node);
    // print_node_graph(node, file_graph_input);
    // latex_dump(node, file_for_LATEX);
    diff_node_t* diffed_node = {};
    // diff_node_t* diffed_node_1 = get_derivative_of_node(node);
    diffed_node = get_derivative_of_node(get_derivative_of_node(node));

    dvalue_t variable = 3;
    // print_node_graph(diffed_node, file_graph_input);
    //count_countable_nodes(diffed_node, variable);
    simplify_function(diffed_node, variable);
    // print_node_graph(node, file_graph_input);
    // latex_dump(node, file_for_LATEX);
    // count_countable_nodes(diffed_node, variable);
    // make_easy_reduction(diffed_node);

    //node_dump(diffed_node);
    print_node_graph(diffed_node, file_graph_input);
    latex_dump(diffed_node, file_for_LATEX);
    tree_dtor(diffed_node);
    tree_dtor(node);

    return 0;
}
