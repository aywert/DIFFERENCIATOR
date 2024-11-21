#include"differenciator_functions.h"

diff_node_t* ctor_node(types_for_diff type, int value, diff_node_t* left, diff_node_t* right)
{
    diff_node_t* node = (diff_node_t*)calloc(sizeof(diff_node_t), 1);
    
    assert(node);

    node->type  = type;
    node->value = value;
    node->right = right;
    node->left  = left;  

    return node; 
}

int dtor_node(diff_node_t* node_ptr)
{
    assert(node_ptr);
    free(node_ptr); 
    node_ptr = NULL;
    return 0; 
}
/*
int attach_node(diff_node_t* root, diff_node_t* node_ptr)
{
    if (compare_tree_value(root, node_ptr->value) > 0)
    {
        if (root->left == 0)
            root->left = node_ptr;
        else
        attach_node(root->left, node_ptr);

        return 0;
    }

    printf("root->value = %d\n", root->value);

    if (compare_tree_value(root, node_ptr->value) < 0)
    {
        if (root->right == 0)
            root->right = node_ptr;
        else
        attach_node(root->right, node_ptr);
        return 0;
    }

    if (compare_tree_value(root, node_ptr->value) == 0)
    {
        printf("same-value-node already exist\n");
        return 0;
    }

    return 0;
}
int compare_tree_value(diff_node_t* root, int value)
{
    return root->value - value;
}

*/

int node_dump(diff_node_t* node)
{
    assert(node);
    printf("(");

    if (node->type == NUM)
    {
        printf("%d", node->value);
    }

    else
    {
        printf("%c", node->value);
    }

    if (node->left)  node_dump(node->left);
    //else printf("()");

    if (node->right) node_dump(node->right);
    //else printf("()");

    printf(")");

    return 0;
}

// int print_node_graph(diff_node_t* node_ptr, char argv[])
// {
//     FILE* file = fopen(argv, "w");
//     fprintf(file, "digraph list\n{\nrankdir=HR;\n\t");

//     generate_graph(node_ptr, file);

//     fprintf(file, "}");
//     fclose(file); file = NULL;
//     system("dot -T png log_folder_acinator//acinator_graph.dot -o  log_folder_acinator//acinator_graph.png");
//     return 0;
// }

// int generate_graph(diff_node_t* node_ptr, FILE* file)
// {
//     static int label = 0;
    
//     fprintf(file, "%d [shape=\"rectangle\", style=\"rounded\", color=\"blue\", label = \" value = %d\n left = %p\n right = %p\"];\n\t", (int)&node_ptr->value, node_ptr->value, node_ptr->left, node_ptr->right);
//     if (label != 0)
//     {
//         fprintf(file, "%d -> %d [color=\"blue\"]\n\t", label, (int)&node_ptr->value);
//     }

//     if (node_ptr->left)
//     {
//         label = (int)&node_ptr->value;
//         generate_graph(node_ptr->left, file);
//     }

//     if (node_ptr->right) 
//     {
//         label = (int)&node_ptr->value;
//         generate_graph(node_ptr->right, file);
//     }

//     return 0;
// }