#include"INCLUDE\\diff_reading_functions.h"
#include"INCLUDE\\diff_dump_functions.h"
#include"INCLUDE\\diff_derivative_functions.h"
#include"INCLUDE\\differenciator_DSL.h"

int main(void)
{ 
    diff_node_t* node = diff_reader(file_for_reading);
    
    diff_node_t* diffed_node = {};
    diffed_node = get_derivative_of_node(node);

    dvalue_t variable = 3;

    //simplify_function(diffed_node, variable);
    count_countable_nodes(diffed_node, variable);
    make_easy_reduction(diffed_node);

    node_dump(diffed_node);
    print_node_graph(diffed_node, file_graph_input);
    latex_dump(diffed_node, file_for_LATEX);
    tree_dtor(diffed_node);
    tree_dtor(node);

    return 0;
}
