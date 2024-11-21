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

double calculate_value(diff_node_t* node, double variable)
{
  switch(node->type)
  {
    case OP:

    switch(node->value)
    {
      case DIV:
        return calculate_value(node->left, variable) / calculate_value(node->right, variable);
        break;

      case MUL:
      {
        return calculate_value(node->left, variable) * calculate_value(node->right, variable);
        break;
      }

      case ADD:
        return calculate_value(node->left, variable) + calculate_value(node->right, variable);
        break;

      case SUB:
      {
        return calculate_value(node->left, variable) - calculate_value(node->right, variable);
        break;
      }

      case SIN:
      {
        return sin(calculate_value(node->left, variable));
        break;
      }

      case COS:
      {
        return cos(calculate_value(node->left, variable));
        break;
      }

      case SQR:
      {
        return sqrt(calculate_value(node->left, variable));
        break;
      }

      default:
        printf(RED("CRUSHIIIIIIIIIIIING"));
        break;
    }
    break;

    case NUM: return node->value; break;
    case VAR: return variable;    break;

    default:
    printf(RED("i died\n"));
    return -666;
  }

  return 0;
}