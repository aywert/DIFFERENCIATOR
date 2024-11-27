#include"INCLUDE\\diff_derivative_functions.h"
#include"INCLUDE\\differenciator_DSL.h"

//TODO debug this thing
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
branch_status is_var_on_the_branch(diff_node_t* node)
{
  if ((node->left != NULL) && (node->right != NULL))
  {
    if (((node->type != VAR)&&(node->left->type != VAR) && (node->right->type != VAR)) && (is_var_on_the_branch(node->left) == var_not_on_the_branch) && (is_var_on_the_branch(node->right) == var_not_on_the_branch))
      return var_not_on_the_branch;
    else  
      return var_on_the_branch;
  }

  else
    return var_not_on_the_branch;
}

double_compare_status compare_double(double a, double b)
{
  if (fabs(a-b) < epsilon_for_comparing_doubles)
    return double_equal;

  if ((a-b) > 0)
    return double_bigger;

  else 
    return double_smaller;
}

// if (node == NULL)
//   printf(YELLOW("Nothing to simplify - %s"), __FUNCTION__);

void simplify_function(diff_node_t* node, dvalue_t variable)
{
  if (is_var_on_the_branch(node->left) == var_not_on_the_branch)
  {
    if (node->left)
      node->left = _NUM(calculate_value(node->left, variable));
  }

  else
  {
    simplify_function(node->left, variable);
  }

  if (is_var_on_the_branch(node->right) == var_not_on_the_branch)
  {
    if (node->right)
      node->right = _NUM(calculate_value(node->right, variable));
  }

  else
  {
    simplify_function(node->right, variable);
  }
}

diff_node_t* simple_fire(diff_node_t* node)
{
  //int error_counter = 0;
  switch((int)node->value)
  {
    case ADD:
    if (compare_double(node->left->value, 0) == double_equal)
    {
      diff_node_t* tempor_ptr = get_copy_of_node(node->right);
      tree_dtor(node->right);
      return tempor_ptr;
    }

    if (compare_double(node->right->value, 0) == double_equal)
      return get_copy_of_node(node->left);

    // node->left = simple_fire(node->left);
    // simple_fire(node->right);
    break;

    case SUB:
    if (compare_double(node->left->value, 0))
      return _MUL(_NUM(-1), get_copy_of_node(node->right));
    if (node->right->value == 0)
      return get_copy_of_node(node->left);
    break;

    case MUL:
    if (node->left->value == 0 || node->right->value == 0)
      return _NUM(0);

    if (node->right->value == 1)
      return get_copy_of_node(node->left);

    if (node->left->value == 1)
      return get_copy_of_node(node->right);

    case DIV:
    if (node->left->value == 0)
      return _NUM(0);

    if (node->right->value == 0)
      return _NUM(inf);

    if (node->right->value == 1)
      return get_copy_of_node(node->left);

    //case 

    break;
  }

    //case VAR: return variable;    break;

  return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////


dvalue_t calculate_value(diff_node_t* node, dvalue_t variable)
{
  switch(node->type)
  {

    case NUM: return node->value; break;
    case VAR: return variable;    break;

    case OP:
    printf("(int)node->value = %d\n", (int)node->value);
    printf("(int)node->value = %c\n", (char)node->value);

    switch((int)node->value)
    {
      case DIV:
      return calculate_value(node->left, variable) / calculate_value(node->right, variable);
      break;

      case MUL:
      return calculate_value(node->left, variable) * calculate_value(node->right, variable);
      break;

      case ADD:
      return calculate_value(node->left, variable) + calculate_value(node->right, variable);
      break;

      case SUB:
      return calculate_value(node->left, variable) - calculate_value(node->right, variable);
      break;

      case SIN:
      return sin(calculate_value(node->right, variable));
      break;

      case COS:
      return cos(calculate_value(node->right, variable));
      break;

      case LN:
      return log((calculate_value(node->right, variable)));
      break;

      case POW:
      return pow(calculate_value(node->left, variable), calculate_value(node->right, variable));
      break;

      case LOG:
      return log(calculate_value(node->right, variable))/log(calculate_value(node->left, variable));
      break;

      case SQRT:
      return sqrt(calculate_value(node->right, variable));
      break;

      default:
      printf(RED("COMAND_SNTX_ERROR\n"));
      return poison_colculation;
      break;
    }

    break;

    default:
    printf(RED("i died\n"));
    return poison_colculation;
  }

  return poison_colculation;
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
    switch((int)node->value)
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
        //printf("!!!!!!%d!!!!\n", get_copy_of_node(node)->left->type);
        //printf("11!!!!!!%d!!!!\n", get_copy_of_node(node)->left->value);
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