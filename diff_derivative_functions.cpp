#include"INCLUDE\\diff_derivative_functions.h"
#include"INCLUDE\\differenciator_DSL.h"

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

      case SQRT:
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

// diff_node_t* get_derivative_of_function(diff_node_t* root)
// {

// }
diff_node_t* get_copy_of_node(diff_node_t* node)
{
    if (node == NULL)
        return NULL;
    return ctor_node(node->type, node->value, get_copy_of_node(node->left), get_copy_of_node(node->right));
}

diff_node_t* get_derivative_of_node(diff_node_t* node)
{
  assert(node);

//   diff_node_t* node_left_copy  = get_copy_of_node(node->left);
//   diff_node_t* node_right_copy = get_copy_of_node(node->right);

  switch(node->type)
  {
    case VAR:
      return ctor_node(NUM, 1, NULL, NULL);
    break;

    case NUM:
      return ctor_node(NUM, 0, NULL, NULL);
    break;

    case OP:
      switch(node->value)
        {
          case DIV:
            return _DIV(_SUB(_MUL(get_derivative_of_node(node->left), get_copy_of_node(node->right)), _MUL(get_copy_of_node(node->left), get_derivative_of_node(node->right))), 
                                                          _MUL(get_copy_of_node(node->right), get_copy_of_node(node->right))); 
          break;
          
          case MUL:
            return _ADD(_MUL(get_derivative_of_node(node->left), get_copy_of_node(node->right)), _MUL(get_copy_of_node(node->left), get_derivative_of_node(node->right)));
          break;
          
          case ADD:
            return _ADD(get_derivative_of_node(node->left), get_derivative_of_node(node->right));  
          break;

          case SUB:
            return _SUB(get_derivative_of_node(node->left), get_derivative_of_node(node->right));
          break;

          case SIN:
            return _MUL(_COS(get_copy_of_node(node)->right), get_derivative_of_node(node->right));
          break;

          case COS:
            return _MUL(_MUL(_NUM(-1), _SIN(get_copy_of_node(node)->right)), get_derivative_of_node(node->right));
          break;

          case SQRT:
            return _MUL(_DIV(_NUM(1), _MUL(_NUM(2), get_copy_of_node(node))), get_derivative_of_node(node->right));
          break;

          case LN:
            return _MUL(_DIV(_NUM(1), get_copy_of_node(node->right)), get_derivative_of_node(node->right));
          break;

          case LOG:
            return _MUL(_DIV(_NUM(1), _MUL(_LN(get_copy_of_node(node->left)), get_copy_of_node(node->right))), get_derivative_of_node(node->right));
          break;

          case POW:
            printf("!!!!!!%d!!!!\n", get_copy_of_node(node)->left->type);
            printf("11!!!!!!%d!!!!\n", get_copy_of_node(node)->left->value);
            return  _MUL(get_copy_of_node(node), get_derivative_of_node(_MUL(_LN(get_copy_of_node(node->left)), get_copy_of_node(node->right))));
          break;

          default:
            printf(RED("FUNCTION_RECOGNITION_ERROR\n"));
          break;
    }

    break;

    default:
    printf(RED("TYPE_FORMATION_ERROR\n"));
  }

  return NULL;
}