#include"differenciator_functions.h"
#include"differenciator_DSL.h"

int main(int argc, char* argv[])
{
    // union value_t variable = {};
    // variable.var = 'x';
    // diff_node_t* special_node = _VAR(variable);

    diff_node_t* special_node = _DIV(_ADD(_VAR('z'), _NUM(88)), _SUB(_NUM(8888), _NUM(88)));
    
    node_dump(special_node);
    printf(GREEN("\n====================\n"));
    print_node_graph(special_node, argv[argc-3]);

    latex_dump(special_node, argv[argc-2]);
    
    diff_node_t* node = diff_reader(argv[argc-1]);
    node_dump(node);
    
    printf("\n\n251 in char is :%d\n\n", '^');

    printf("Please enter value of variable x:");
    double variable = 0;
    scanf("%lg", &variable);
    double answer = calculate_value(special_node, variable);
    printf("%lg", answer);
    tree_dtor(special_node);
    return 0;
}
