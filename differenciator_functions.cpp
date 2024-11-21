#include"differenciator_functions.h"

diff_node_t* ctor_node(types_for_diff type, /*value_t*/int value, diff_node_t* left, diff_node_t* right)
{
    diff_node_t* node = (diff_node_t*)calloc(sizeof(diff_node_t), 1);
    
    assert(node);

    // switch(type)
    // {
    //     case OP:  node->value.op  = value.op;
    //     case VAR: node->value.var = value.var;
    //     case NUM: node->value.num = value.num;
    // }
    node->value = value;

    node->type  = type;
    node->right = right;
    node->left  = left;  

    return node; 
}
int tree_dtor(diff_node_t* root)
{
    assert(root);

    if (root->left)
    {
        tree_dtor(root->left);
    }

    if (root->right)
    {
        tree_dtor(root->right);
    }

    dtor_node(root); root = NULL;
    
    return 0;
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

int print_node_graph(diff_node_t* node, char argv[])
{
    assert(node);
    assert(argv);
    printf("%s", argv);
    FILE* file = fopen(argv, "w");
    fprintf(file, "digraph list\n{\nrankdir=HR;\n\t");

    generate_graph(node, file);

    fprintf(file, "}");
    fclose(file); file = NULL;
    system("dot -T png log_folder_differenciator//differenciator_graph.dot -o  log_folder_differenciator//differenciator_graph.png");
    return 0;
}

int generate_graph(diff_node_t* node, FILE* file)
{
    assert(node);
    assert(file);

    static int label = 0;
    
    if (node->type == NUM)
    {
        fprintf(file, "%d [shape = Mrecord; style = filled; fillcolor=\"#4682b4\"; color = \"#000000\"; fontcolor = \"#000000\"; label = \"{ NUM | value = %d | left = %p| right = %p}\"];\n\t", 
                    (int)&node->value,                                                                                                          node->value,  node->left,     node->right);
    }

    if (node->type == VAR)
    {
        fprintf(file, "%d [shape = Mrecord; style = filled; fillcolor=\"#ff7da3\"; color = \"#000000\"; fontcolor = \"#000000\"; label = \"{ VAR | value = %c | left = %p| right = %p}\"];\n\t", 
        (int)&node->value,                                                                                                                        node->value,  node->left,     node->right);
    }

    if (node->type == OP)
    {
        fprintf(file, "%d [shape = Mrecord; style = filled; fillcolor=\"#ffc765\"; color = \"#000000\"; fontcolor = \"#000000\"; label = \"{ OP | value = %c | left = %p| right = %p}\"];\n\t", 
        (int)&node->value,                                                                                                                       node->value,  node->left,     node->right);
    }

    if (label != 0)
    {
        fprintf(file, "%d -> %d [color=\"blue\"]\n\t", label, (int)&node->value);
    }

    if (node->left)
    {
        label = (int)&node->value;
        generate_graph(node->left, file);
    }

    if (node->right) 
    {
        label = (int)&node->value;
        generate_graph(node->right, file);
    }

    return 0;
}

int latex_dump(diff_node_t* node, char argv[])
{
    FILE* file = fopen(argv, "w");

    fprintf(file, "\\documentclass{article}\n\\begin{document}\n");
    fprintf(file, "$");
    generate_latex_dump(node, file);
    fprintf(file, "$\n");
    fprintf(file, "\\end{document}\n");

    fclose(file); file = NULL;
    system("pdflatex -output-directory=log_folder_differenciator\\LATEX log_folder_differenciator\\LATEX\\LATEX_dump.tex");

    return 0;
}

int generate_latex_dump(diff_node_t* node, FILE* file)
{
  switch(node->type)
  {
    case OP:

    switch(node->value)
    {
      case DIV:
        fprintf(file, "\\frac{");
        generate_latex_dump(node->left, file);
        fprintf(file, "}{");
        generate_latex_dump(node->right, file);
        fprintf(file, "}");
        break;

      case MUL:
      {
        fprintf(file, "(");
        generate_latex_dump(node->left, file);
        fprintf(file, "\\cdot");
        generate_latex_dump(node->right, file);
        fprintf(file, ")");
        break;
      }

      case ADD:
        fprintf(file, "(");
        generate_latex_dump(node->left, file);
        fprintf(file, " + ");
        generate_latex_dump(node->right, file);
        fprintf(file, ")");
        break;

      case SUB:
      {
        fprintf(file, "(");
        generate_latex_dump(node->left, file);
        fprintf(file, " - ");
        generate_latex_dump(node->right, file);
        fprintf(file, ")");
        break;
      }

      case SIN:
      {
        fprintf(file, "\\sin{");
        generate_latex_dump(node->left, file);
        fprintf(file, "}");
        break;
      }

      case COS:
      {
        fprintf(file, "\\cos{");
        generate_latex_dump(node->left, file);
        fprintf(file, "}");
        break;
      }

      case SQR:
      {
        fprintf(file, "{\\sqrt{");
        generate_latex_dump(node->left, file);
        fprintf(file, "}");
        break;
      }

      default:
        printf(RED("CRUSHIIIIIIIIIIIING"));
        break;
    }
    break;

    case NUM: fprintf(file, "%d", node->value); break;
    case VAR: fprintf(file, "%c", node->value); break;
    default:
    printf(RED("i died\n"));
  }

    return 0;
}