#include"INCLUDE\\diff_reading_functions.h"
#include"INCLUDE\\differenciator_DSL.h"

static int partition_for_reading(char* buffer);

diff_node_t* ctor_node(types_for_diff type, dvalue_t value, diff_node_t* left, diff_node_t* right)
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
    
    node->type  = type;
    node->value = value;
    node->right = right;
    node->left  = left;  

    return node; 
}
int tree_dtor(diff_node_t* root)
{
    if (root == NULL)
      return 0;

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

diff_node_t* diff_reader(const char* file_name)
{
  assert(file_name);
  FILE* file = fopen(file_name, "r");
  assert(file);

  struct stat file_inf = {};
  stat(file_name, &file_inf);
  
  char* buffer = (char*)calloc((size_t)file_inf.st_size + 1, sizeof(char));
  fread(buffer, sizeof(char), (size_t)file_inf.st_size, file);

  fclose(file);

  diff_node_t* node = diff_reader_recursion(buffer);

  free(buffer); buffer = NULL;
  return node;
}

diff_node_t* diff_reader_recursion(char* buffer)
{
  assert(buffer);
  
  //printf("buffer = %s\n", buffer);
  char* operation = (char*)calloc(operation_word, 1); 
  assert(operation);
  int pc = partition_for_reading(buffer);
  
  if (pc == NOT_AN_OPERATOR_PTR)
  {
    sscanf(buffer, "(%[^)]", operation);
    printf("operation = %s\n", operation);

    char char_read = operation[0];
    dvalue_t read  = 0;
    int read_item = sscanf(operation, "%lg", &read); 
    //printf("read = %lg\n", read);
    free(operation); operation = NULL;

    if (read_item == 1)
      return _NUM(read);

    else
      return _VAR(char_read);
  }

  else
  {
    printf("left_buffer = %s\n", &buffer[1]);

    printf("right_buffer = %s\n", &buffer[pc+1]);

    sscanf(&buffer[pc], "%[^(]", operation);
    printf(RED("oper = %s\n"), operation);

    if (strcmp(operation, "+") == 0)
    {
      free(operation); operation = NULL;
      return _ADD(diff_reader_recursion(&buffer[1]), diff_reader_recursion(&buffer[pc+1]));
    }

    if (strcmp(operation, "-") == 0)
    {
      free(operation); operation = NULL;
      return _SUB(diff_reader_recursion(&buffer[1]), diff_reader_recursion(&buffer[pc+1]));
    }

    if (strcmp(operation, "*") == 0)
    {
      free(operation); operation = NULL;
      return _MUL(diff_reader_recursion(&buffer[1]), diff_reader_recursion(&buffer[pc+1]));
    }

    if (strcmp(operation, "/") == 0)
    {
      free(operation); operation = NULL;
      return _DIV(diff_reader_recursion(&buffer[1]), diff_reader_recursion(&buffer[pc+1]));
    }

    if (strcmp(operation, "^") == 0)
    {
      free(operation); operation = NULL;
      return _POW(diff_reader_recursion(&buffer[1]), diff_reader_recursion(&buffer[pc+1]));
    }

    if (strcmp(operation, "log") == 0)
    {
      free(operation); operation = NULL;
      return _LOG(diff_reader_recursion(&buffer[1]), diff_reader_recursion(&buffer[pc+3]));
    }

    if (strcmp(operation, "ln") == 0)
    {
      free(operation); operation = NULL;
      return _LN(diff_reader_recursion(&buffer[pc+2]));
    }

    if (strcmp(operation, "sqrt") == 0)
    {
      free(operation); operation = NULL;
      return _SQRT(diff_reader_recursion(&buffer[pc+4]));
    }

    if (strcmp(operation, "sin") == 0)
    {
      free(operation); operation = NULL;
      return _SIN(diff_reader_recursion(&buffer[pc+3]));
    }

    if (strcmp(operation, "cos") == 0)
    {
      free(operation); operation = NULL;
      return _COS(diff_reader_recursion(&buffer[pc+3]));
    }

    printf(RED("COMMAND HAVE NOT BEEN REGOCNISED\n"));
    printf(YELLOW("So i am returning zero-pointer\n"));
    return NULL;
  }
}

int partition_for_reading(char* buffer)
{
  assert(buffer);
  int pc = 0;
  int bracket_ct_in  = 0;
  int bracket_ct_out = 0;

  while((((bracket_ct_in - bracket_ct_out) != 1) || (bracket_ct_out == 0)) && buffer[pc] != '\0' )
  {
    if (buffer[pc] == '(')
      bracket_ct_in++;
    if (buffer[pc] == ')')
      bracket_ct_out++;
    pc++;

    if (bracket_ct_in == bracket_ct_out && (bracket_ct_in == 1))
      break;
  }

  if (bracket_ct_in == 1)// && bracket_ct_out == 1
  {
    return NOT_AN_OPERATOR_PTR;
  }

  return pc;
}