#include"INCLUDE\\diff_derivative_functions.h"
#include"INCLUDE\\differenciator_DSL.h"
#include"INCLUDE\\diff_dump_functions.h"

//TODO debug this thing
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
branch_status is_var_on_the_branch(diff_node_t* node)
{
  if (node == NULL)
    return var_not_on_the_branch;

  if(node->type == VAR)
      return var_on_the_branch;

  if ((node->right != NULL) && node->left == NULL)
    return is_var_on_the_branch(node->right);
    
  if ((node->left != NULL)  && node->right == NULL)
    return is_var_on_the_branch(node->left);
      
  if ((node->left != NULL)  && (node->right != NULL))
  {
    if (((node->left->type != VAR) && (node->right->type != VAR)) && (is_var_on_the_branch(node->left) == var_not_on_the_branch) && (is_var_on_the_branch(node->right) == var_not_on_the_branch))
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

void simplify_function(diff_node_t* node, dvalue_t variable)
{
  diff_node_t* prev_node = NULL;

  while(1)
  {
    prev_node = get_copy_of_node(node);
    count_countable_nodes(node, variable);
    make_easy_reduction(node);

    if (compare_tree(prev_node, node) == equal_trees)
      break;
  }
}

compare_tree_status compare_tree(diff_node_t* root_1, diff_node_t* root_2)
{
  if (compare_double(root_1->value, root_2->value) == double_equal)
  {
    if (root_1->left != NULL && root_2->left != NULL)
      return compare_tree(root_1->left, root_2->left);
    else  

    if (root_1->right != NULL && root_2->right != NULL)
    {
      return compare_tree(root_1->right, root_2->right);
    }
    return equal_trees;
  }
  else
    return different_trees;
}

void make_easy_reduction(diff_node_t* node)
{

  if ((node->left != NULL) && (int)node->left->type == OP) 
  {
    simple_fire(node->left);
    make_easy_reduction(node->left);
  }

  if ((node->right != NULL) && (int)node->right->type == OP) 
  {
    simple_fire(node->right);
    make_easy_reduction(node->right);
  }
}

void count_countable_nodes(diff_node_t* node, dvalue_t variable)
{ 
  if (is_var_on_the_branch(node->left) == var_not_on_the_branch)
  {
    if (node->left)
    {
      dvalue_t result = calculate_value(node->left, variable);
      tree_dtor(node->left);
      node->left = _NUM(result);
    }
  }

  else
  {
    count_countable_nodes(node->left, variable);
    //simple_fire(node->left);
  }

  if (is_var_on_the_branch(node->right) == var_not_on_the_branch)
  {
    if (node->right)
    {
      dvalue_t result = calculate_value(node->right, variable);
      tree_dtor(node->right);
      node->right = _NUM(result);
    }
  }

  else
  {
    count_countable_nodes(node->right, variable);
    //simple_fire(node);
  }
}

void replace_node(diff_node_t* node_to_replace, diff_node_t* new_node)
{
  node_to_replace->type  = new_node->type; 
  node_to_replace->value = new_node->value;
  
  diff_node_t* tempor_right = new_node->right;
  diff_node_t* tempor_left  = new_node->left;

  dtor_node(node_to_replace->left);
  dtor_node(node_to_replace->right);

  node_to_replace->right = tempor_right;
  node_to_replace->left  = tempor_left;  
}

// int reform_function(diff_node_t* node)
// {
//   if ()
//   //simple_fire(node);
// }



simplify_status simple_fire(diff_node_t* node)
{
  //int error_counter = 0;
  if (node == NULL)
    return cant_be_simplified;
  
  if (node->type != OP)
    return TYPE_ERROR_SMPLF;

  switch((int)node->value)
  {
    case ADD:
    if (node->left->type == NUM && compare_double(node->left->value, 0) == double_equal)
    {
      node_dump(node);
      replace_node(node, node->right); 
      //printf("i'm alive?");
      printf("\n");
      node_dump(node);
      return cant_be_simplified;
      //printf("i'm alive?");
    }

    if (node->right->type == NUM && compare_double(node->right->value, 0) == double_equal)
      replace_node(node, node->left);
    break;

    case SUB:
    if (node->left->type == NUM && compare_double(node->left->value, 0) == double_equal)
    {
      node->value = MUL;
      node->left->value = -1;
    }

    if (node->right->type == NUM && compare_double(node->right->value, 0) == double_equal)
    {
      replace_node(node, node->left);
    }
    break;

    case MUL:
    if ((node->left->type == NUM && (compare_double(node->left->value, 0) == double_equal)) || (node->right->type == NUM && (compare_double(node->right->value, 0) == double_equal)))
    {
      node->type  = NUM; 
      node->value = 0;
      tree_dtor(node->left);  node->left = NULL;
      tree_dtor(node->right); node->right = NULL;
      return cant_be_simplified;
    }

    if (node->left->type == NUM && compare_double(node->left->value, 1) == double_equal)
    {
      replace_node(node, node->right);
      return cant_be_simplified;
    }
    
    if (node->right->type == NUM && compare_double(node->right->value, 1) == double_equal)
    {
      replace_node(node, node->left);
      return cant_be_simplified;
    }

    break;

    case DIV:
    if (node->left->type == NUM && compare_double(node->left->value, 0) == double_equal)
    {
      node->type  = NUM; 
      node->value = 0;
      tree_dtor(node->left);  node->left = NULL;
      tree_dtor(node->right); node->right = NULL;
      return cant_be_simplified;
    } 
    break;

    case POW:
    if (node->left->type == NUM && compare_double(node->left->value, 0) == double_equal)
    {
      node->type  = NUM; 
      node->value = 0;
      tree_dtor(node->left); node->left = NULL;
      tree_dtor(node->right); node->right = NULL;

      return cant_be_simplified;
    } 

    if (node->left->type == NUM && compare_double(node->left->value, 1) == double_equal)
    {
      node->type  = NUM; 
      node->value = 1;
      tree_dtor(node->left);  node->left = NULL;
      tree_dtor(node->right); node->right = NULL;
      return cant_be_simplified;
    } 

    if (node->right->type == NUM && compare_double(node->right->value, 0) == double_equal)
    {
      node->type  = NUM; 
      node->value = 1;
      tree_dtor(node->left);  node->left = NULL;
      tree_dtor(node->right); node->right = NULL;
  
      return cant_be_simplified;
    } 

    if (node->right->type == NUM && compare_double(node->right->value, 1) == double_equal)
    {
      replace_node(node, node->left);
      return cant_be_simplified;
    } 

    break;

    case SIN:
    case COS:
    case LN:
    case LOG:
    case SQRT:
    case VAR:
    case NUM:
    break;

    default:
    printf(RED("SYNTEX_ERROR - %c\n"), (char)node->value);
    break;
    
  }

    //case VAR: return variable;    break;
  return cant_be_simplified;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////


dvalue_t calculate_value(diff_node_t* node, dvalue_t variable)
{
  if (node == NULL)
    return poison_calculation;
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
      printf("ln counted %lg", log((calculate_value(node->right, variable))));
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
      return poison_calculation;
      break;
    }

    break;

    default:
    printf(RED("SNTX_TYPE_ERROR_IN_CNTR\n"));
    return poison_calculation;
  }

  return poison_calculation;
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