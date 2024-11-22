#include"differenciator_functions.h"
#include"differenciator_DSL.h"

static int partition_for_reading(char* buffer);

diff_node_t* ctor_node(types_for_diff type, /*value_t*/int value, diff_node_t* left, diff_node_t* right)
{
    assert(type);

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

diff_node_t* diff_reader(char argv[])
{
  assert(argv);
  FILE* file = fopen(argv, "r");

  char buffer[size_limit]={};
  fread(buffer, sizeof(char), size_limit, file);

  fclose(file);
  

  diff_node_t* node = diff_reader_recursion(buffer);
  
  
  
  return node;
}

diff_node_t* diff_reader_recursion(char* buffer)
{
  assert(buffer);
  
  printf("buffer = %s\n", buffer);

  char* oper = (char*)calloc(operation_word, 1);
  assert(oper);
  int pc = partition_for_reading(buffer);
  
  if (pc < 0)
  {
    sscanf(buffer, "(%[^)]", oper);
    printf("oper = %s\n", oper);
    char char_read = oper[0];
    int int_read = 0;
    int read_item = sscanf(oper, "%d", &int_read);

    free(oper); oper = NULL;

    if (read_item == 1)
    { 
      return _NUM(int_read);
    }

    else
    {
      return _VAR(char_read);
    }
    // printf("\nread_item = %d\n", read_item);
    // printf("oper_n = %d\n", oper_n);
    // printf(GREEN("oper = %s"), oper);
  }

  else
  {
   
    char left_buffer[size_limit]  = {};
    char right_buffer[size_limit] = {};
  

    for (int i = 1; i < pc; i++)
    {
      left_buffer[i-1] = buffer[i];
      //printf("i am okey\n");
      //printf("%c", left_buffer[i]);
    }
    printf("left_buffer = %s\n", left_buffer);

    //printf("\n");

    //printf("\n");

    int i = pc + 1;
    while(buffer[i+1] != '\0')
    {
      //printf("i am okey2\n");
      right_buffer[i-pc-1] = buffer[i];
      //printf("%c", right_buffer[i]);
      i++;
    }
    printf("right_buffer = %s\n", right_buffer);
    //printf("\n");

    // printf(RED("\nleft_buffer = %s\n"), left_buffer);
    // printf(RED("right_buffer = %s\n"), right_buffer);
    
    sscanf(&buffer[pc], "%[^(]", oper);
    printf(RED("oper = %s\n"), oper);
    
    if (strcmp(oper, "+") == 0)
    {
      free(oper); oper = NULL;
      return _ADD(diff_reader_recursion(left_buffer), diff_reader_recursion(right_buffer));
    }

    if (strcmp(oper, "-") == 0)
    {
      free(oper); oper = NULL;
      return _SUB(diff_reader_recursion(left_buffer), diff_reader_recursion(right_buffer));
    }

    if (strcmp(oper, "*") == 0)
    {
      free(oper); oper = NULL;
      return _MUL(diff_reader_recursion(left_buffer), diff_reader_recursion(right_buffer));
    }

    if (strcmp(oper, "/") == 0)
    {
      free(oper); oper = NULL;
      return _DIV(diff_reader_recursion(left_buffer), diff_reader_recursion(right_buffer));
    }

    printf(RED("SOMETHING TERRIBLE HEPPENED\n"));
    return 0;
  }
}

int partition_for_reading(char* buffer)
{
  assert(buffer);
  int pc = 0;
  int bracket_ct_in  = 0;
  int bracket_ct_out = 0;

  while((((bracket_ct_in - bracket_ct_out) != 1) || (bracket_ct_out == 0))&&buffer[pc] != '\0')
  {
    //printf("%c", buffer[pc]);
    if (buffer[pc] == '(')
      bracket_ct_in++;
    if (buffer[pc] == ')')
      bracket_ct_out++;
    pc++;
  }

  if (bracket_ct_in == 1 && bracket_ct_out == 1)
  {
    printf("partition\n");
    return -1;
  }

  return pc;
}