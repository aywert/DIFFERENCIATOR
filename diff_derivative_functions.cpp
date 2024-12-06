#include"INCLUDE\\diff_derivative_functions.h"
#include"INCLUDE\\differenciator_DSL.h"
#include"INCLUDE\\diff_dump_functions.h"

static void get_variable_for_tailor(dvalue_t* variable);
static void get_degree_for_tailor(int* degree);


int counter_of_changes = 0;

void get_analitics(const char* file_name, const char* file_LATEX_dump, const char* output_directory)
{
  printf("Let me see what we've got here\n");
  printf("...\n");
  diff_node_t* node = diff_reader(file_name);
  printf("Interesting\n");
  printf("Please enter point around which you wnat we to analyse your function more closely: ");
  
  dvalue_t variable = 0;
  get_variable_for_tailor(&variable);
  printf("Please enter to which extent you want we to analize your function: ");
  int degree = 0;
  get_degree_for_tailor(&degree);

  dvalue_t* derivative_value_buffer = (dvalue_t*)calloc(degree + 2, sizeof(dvalue_t));
  assert(derivative_value_buffer);

  diff_node_t* init_function = node;
  simplify_function(node, variable); // simplification in case i am given bad input function

  diff_node_t* diffed_function = get_derivative_of_node(node);
  simplify_function(diffed_function, variable);
  derivative_value_buffer[0] = calculate_value(init_function, variable);
  derivative_value_buffer[1] = calculate_value(diffed_function, variable);
  node = diffed_function;
  
  if (degree >= 2)
  {
    for (int index = 2; index <= degree; index++)
    {
      diff_node_t* tempor_ptr = get_derivative_of_node(node);
      simplify_function(tempor_ptr, variable);
      derivative_value_buffer[index] = calculate_value(tempor_ptr, variable);
      if (node != diffed_function)
        tree_dtor(node);
      node = tempor_ptr;
    }

    tree_dtor(node);
  }

  for (int i = 0; i <= degree; i++)
  {
    printf(BLUE("Diffed_%d") " = %lg\n", i, derivative_value_buffer[i]);
  }

  analitical_latex_dump(init_function, diffed_function, derivative_value_buffer, degree, variable, file_LATEX_dump, output_directory);

  tree_dtor(init_function); init_function = NULL;
  tree_dtor(diffed_function); diffed_function = NULL;

  free(derivative_value_buffer); derivative_value_buffer = NULL;
}

static void get_variable_for_tailor(dvalue_t* variable)
{
   while (true)
  {
    if (scanf("%lg", variable) == 1)
      break;
    while(getchar()!= '\n');
    printf("Sorry, could recognize input information\n Please Try again\n");
  }

  printf(GREEN("Successfully scanned\n"));
}

static void get_degree_for_tailor(int* degree)
{
  while (true)
  {
    if (scanf("%d", degree) == 1)
      break;
    while(getchar()!= '\n');
    printf(YELLOW("Sorry, could recognize input information\n Please Try again\n"));
  }

  printf(GREEN("Successfully scanned\n"));
}

branch_status is_var_on_the_branch(const diff_node_t* node)
{
  if (node == NULL)
    return var_not_on_the_branch;

  else if(node->type == VAR)
    return var_on_the_branch;

  else if ((node->right != NULL) && node->left == NULL)
    return is_var_on_the_branch(node->right);
    
  else if ((node->left != NULL)  && node->right == NULL)
    return is_var_on_the_branch(node->left);
      
  else if ((node->left != NULL)  && (node->right != NULL))
  {
    if ((node->left->type  != VAR)  && 
        (node->right->type != VAR) && 
        (is_var_on_the_branch(node->left)  == var_not_on_the_branch) && 
        (is_var_on_the_branch(node->right) == var_not_on_the_branch))
      return var_not_on_the_branch;
    else  
      return var_on_the_branch;
  }

  else
    return var_not_on_the_branch;
}

double_compare_status compare_double(const double a, const double b)
{
  if (fabs(a-b) < epsilon_for_comparing_doubles)
    return double_equal;

  if ((a-b) > 0)
    return double_bigger;

  else 
    return double_smaller;
}

void simplify_function(diff_node_t* node, const dvalue_t variable)
{
  while(true)
  {
    counter_of_changes = 0;
    count_countable_nodes(node, variable);
    make_easy_reduction(node);
    printf("counter_of_changes = %d\n", counter_of_changes);
    if (counter_of_changes == 0)
      break;
  }
  diff_node_t* node_1 = ctor_node(OP, (dvalue_t)869, node, NULL);
  //count_countable_nodes(node_1, variable);
  make_easy_reduction(node_1);
  dtor_node(node_1);
}

void make_easy_reduction(diff_node_t* node)
{
  // if (node->type == OP)
  // {
  //   make_easy_reduction(node);
  //   if (node->left != NULL && node->left->type == OP && simple_fire(node->left) == can_be_simplified) counter_of_changes++;
  //   if (node->right != NULL && node->right->type == OP && simple_fire(node->right) == can_be_simplified) counter_of_changes++;
  // }
  if (node == NULL)
    return;

  // simple_fire (node);

  if ((node->left != NULL) && (int)node->left->type == OP) 
  {
    if (simple_fire(node->left) == can_be_simplified) 
    {
      counter_of_changes++;
    }
    make_easy_reduction(node->left);
  }

  if ((node->right != NULL) && (int)node->right->type == OP) 
  {
    if (simple_fire(node->right) == can_be_simplified)
    {
      counter_of_changes++;
    }
    make_easy_reduction(node->right);
  }
}

void count_countable_nodes(diff_node_t* node, const dvalue_t variable)
{ 
  if (node == NULL)
    return;
  
  if (is_var_on_the_branch(node) == var_not_on_the_branch)
  {
    if (node->type == OP)
    {
      counter_of_changes++;
      dvalue_t result = calculate_value(node, variable);
      node->type = NUM;
      node->value = result;
      tree_dtor(node->left); node->left = NULL;
      tree_dtor(node->right);node->right = NULL;
    }
  }
  else
  {
    if (node->left)  count_countable_nodes(node->left, variable);
    if (node->right) count_countable_nodes(node->right, variable);
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

simplify_status simple_fire(diff_node_t* node)
{
  if (node == NULL)
    return TYPE_ERROR_SMPLF;
  
  if (node->type != OP)
    return TYPE_ERROR_SMPLF;

  switch((int)node->value)
  {
    case ADD:
    if (node->left->type == NUM && compare_double(node->left->value, 0) == double_equal)
    {
      replace_node(node, node->right); 
      return can_be_simplified;
    }

    if (node->right->type == NUM && compare_double(node->right->value, 0) == double_equal)
    {
      replace_node(node, node->left);
      return can_be_simplified;
    }
    
    break;

    case SUB:
    if (node->left->type == NUM && compare_double(node->left->value, 0) == double_equal)
    {
      node->value = MUL;
      node->left->value = -1;
      return can_be_simplified;
    }

    if (node->right->type == NUM && compare_double(node->right->value, 0) == double_equal)
    {
      replace_node(node, node->left);
      return can_be_simplified;
    }

    break;

    case MUL:
    if ((node->left->type == NUM  && (compare_double(node->left->value, 0) == double_equal)) || 
        (node->right->type == NUM && (compare_double(node->right->value, 0) == double_equal)))
    {
      node->type  = NUM; 
      node->value = 0;
      tree_dtor(node->left);  node->left = NULL;
      tree_dtor(node->right); node->right = NULL;
      return can_be_simplified;
    }

    if (node->left->type == NUM && compare_double(node->left->value, 1) == double_equal)
    {
      replace_node(node, node->right);
      return can_be_simplified;
    }
    
    if (node->right->type == NUM && compare_double(node->right->value, 1) == double_equal)
    {
      printf(GREEN("something\n"));
      replace_node(node, node->left);
      return can_be_simplified;
    }

    break;

    case DIV:
    if (node->left->type == NUM && compare_double(node->left->value, 0) == double_equal)
    {
      node->type  = NUM; 
      node->value = 0;
      tree_dtor(node->left);  node->left = NULL;
      tree_dtor(node->right); node->right = NULL;
      return can_be_simplified;
    } 
    break;

    case POW:
    if (node->left->type == NUM && compare_double(node->left->value, 0) == double_equal)
    {
      node->type  = NUM; 
      node->value = 0;
      tree_dtor(node->left); node->left = NULL;
      tree_dtor(node->right); node->right = NULL;

      return can_be_simplified;
    } 

    if (node->left->type == NUM && compare_double(node->left->value, 1) == double_equal)
    {
      node->type  = NUM; 
      node->value = 1;
      tree_dtor(node->left);  node->left = NULL;
      tree_dtor(node->right); node->right = NULL;
      return can_be_simplified;
    } 

    if (node->right->type == NUM && compare_double(node->right->value, 0) == double_equal)
    {
      node->type  = NUM; 
      node->value = 1;
      tree_dtor(node->left);  node->left = NULL;
      tree_dtor(node->right); node->right = NULL;
  
      return can_be_simplified;
    } 

    if (node->right->type == NUM && compare_double(node->right->value, 1) == double_equal)
    {
      replace_node(node, node->left);
      return can_be_simplified;
    } 

    break;

    case SIN:
    case COS:
    case LN:
    case LOG:
    case SQRT:
    case VAR:
    case NUM:
    return cant_be_simplified;

    default:
    printf(RED("SYNTEX_ERROR - %c\n"), (char)node->value);
    return cant_be_simplified;
    
  }

    //case VAR: return variable;    break;
  return cant_be_simplified;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////


dvalue_t calculate_value(const diff_node_t* node, const dvalue_t variable)
{
  if (node == NULL)
    return poison_calculation;

  switch(node->type)
  {

    case NUM: return node->value;
    case VAR: return variable;    

    case OP:
    // printf("(int)node->value = %d\n", (int)node->value);
    // printf("(int)node->value = %c\n", (char)node->value);
    // printf("(int)node->left->value = %d\n", (int)node->left->value);
    // printf("(int)node->left->value = %d\n", (int)node->right->value);

    switch((int)node->value)
    {
      case DIV:
      return calculate_value(node->left, variable) / calculate_value(node->right, variable);

      case MUL:
      return calculate_value(node->left, variable) * calculate_value(node->right, variable);

      case ADD:
      return calculate_value(node->left, variable) + calculate_value(node->right, variable);

      case SUB:
      return calculate_value(node->left, variable) - calculate_value(node->right, variable);

      case SIN:
      return sin(calculate_value(node->right, variable));

      case COS:
      return cos(calculate_value(node->right, variable));

      case LN:
      printf("ln counted %lg", log((calculate_value(node->right, variable))));
      return log((calculate_value(node->right, variable)));

      case POW:
      return pow(calculate_value(node->left, variable), calculate_value(node->right, variable));

      case LOG:
      return log(calculate_value(node->right, variable))/log(calculate_value(node->left, variable));

      case SQRT:
      return sqrt(calculate_value(node->right, variable));

      default:
      printf(RED("COMAND_SNTX_ERROR\n"));
      return poison_calculation;
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
diff_node_t* get_copy_of_node(const diff_node_t* node)
{
  if (node == NULL)
      return NULL;
  return ctor_node(node->type, node->value, get_copy_of_node(node->left), get_copy_of_node(node->right));
}

diff_node_t* get_derivative_of_node(const diff_node_t* node)
{
  assert(node);

//   diff_node_t* node_left_copy  = get_copy_of_node(node->left);
//   diff_node_t* node_right_copy = get_copy_of_node(node->right);

  switch(node->type)
  {
    case VAR:
    return _NUM(1);
    break;

    case NUM:
    return _NUM(0);
    break;

    case OP:
    switch((int)node->value)
    {
      case DIV:
      return _DIV(_SUB(_MUL(get_derivative_of_node(node->left), get_copy_of_node(node->right)), _MUL(get_copy_of_node(node->left), get_derivative_of_node(node->right))), 
                  _MUL(get_copy_of_node(node->right), get_copy_of_node(node->right))); 
      
      case MUL:
      return _ADD(_MUL(get_derivative_of_node(node->left), get_copy_of_node(node->right)), _MUL(get_copy_of_node(node->left), get_derivative_of_node(node->right)));
      
      case ADD:
      return _ADD(get_derivative_of_node(node->left), get_derivative_of_node(node->right));  

      case SUB:
      return _SUB(get_derivative_of_node(node->left), get_derivative_of_node(node->right));

      case SIN:
      return _MUL(_COS(get_copy_of_node(node)->right), get_derivative_of_node(node->right));

      case COS:
      return _MUL(_MUL(_NUM(-1), _SIN(get_copy_of_node(node)->right)), get_derivative_of_node(node->right));

      case SQRT:
      return _MUL(_DIV(_NUM(1), _MUL(_NUM(2), get_copy_of_node(node))), get_derivative_of_node(node->right));

      case LN:
      return _MUL(_DIV(_NUM(1), get_copy_of_node(node->right)), get_derivative_of_node(node->right));

      case LOG:
      return _MUL(_DIV(_NUM(1), _MUL(_LN(get_copy_of_node(node->left)), get_copy_of_node(node->right))), get_derivative_of_node(node->right));

      case POW:
        //printf("!!!!!!%d!!!!\n", get_copy_of_node(node)->left->type);
        //printf("11!!!!!!%d!!!!\n", get_copy_of_node(node)->left->value);
      return  _MUL(get_copy_of_node(node), get_derivative_of_node(_MUL(_LN(get_copy_of_node(node->left)), get_copy_of_node(node->right))));

      default:
        printf(RED("FUNCTION_RECOGNITION_ERROR\n"));
      break;
    }

    break;

    default:
    printf(RED("TYPE_FORMATION_ERROR\n"));
    break;
  }

  return NULL;
}

