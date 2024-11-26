#include"INCLUDE\\diff_dump_functions.h"
#include"INCLUDE\\assert_for_dump.h"

static diff_dump_status verifier_for_dump_functions(diff_node_t* node, char* file_name)
{
  if (node == NULL)
  {
    printf(RED("%s have recieved null-pointer on ") BLUE("node") RED(" and is not able to do anything with it"), __FUNCTION__);
    printf(YELLOW("Returning zero"));
    return diff_dump_failure;
  }
    
  if (file_name == NULL)
  {
    printf(RED("%s have recieved null-pointer on ") BLUE("file") RED(" and is not able to do anything with it"), __FUNCTION__);
    printf(YELLOW("Returning zero"));
    return diff_dump_failure;
  }

  return diff_dump_success;
}

diff_dump_status node_dump(diff_node_t* node)
{
  DIFF_DUMP_ASSERT(node, 1);

  printf("(");

  if (node->type == NUM)
      printf("%d", node->value);

  else
      printf("%c", node->value);

  if (node->left)  node_dump(node->left);
  if (node->right) node_dump(node->right);

  printf(")");
  
  return diff_dump_success;
}

diff_dump_status print_node_graph(diff_node_t* node, const char* file_name)
{   
  DIFF_DUMP_ASSERT(node, 1);

  FILE* file = fopen(file_name, "w");

  if (file == NULL)
  {
    fclose(file); file = NULL;
    return diff_dump_failure;
  }

  fprintf(file, "digraph list\n{\nrankdir=HR;\n\t");

  generate_graph(node, file);
  fprintf(file, "}");

  fclose(file); file = NULL;
  
  system("dot -T png " file_graph_input " -o " file_graph_output " -Gcharset=latin1");
  return diff_dump_success;
}

diff_dump_status generate_graph(diff_node_t* node, FILE* file)
{
    DIFF_DUMP_ASSERT(node, file);
    
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

    if (node->left)
    {
        fprintf(file, "%d -> %d [color=\"blue\"]\n\t", (int)&node->value, (int)&node->left->value);
        generate_graph(node->left, file);
    }

    if (node->right) 
    {
        fprintf(file, "%d -> %d [color=\"blue\"]\n\t", (int)&node->value, (int)&node->right->value);
        generate_graph(node->right, file);
    }

    return diff_dump_success;
}

diff_dump_status latex_dump(diff_node_t* node, const char* file_name)
{
  DIFF_DUMP_ASSERT(node, 1);
  FILE* file = fopen(file_name, "w");
  
  if (file == NULL)
  {
    fclose(file); file = NULL;
    return diff_dump_failure;
  }

  fprintf(file, "\\documentclass{article}\n\\begin{document}\n");
  fprintf(file, "$");
  generate_latex_dump(node, file);
  fprintf(file, "$\n");
  fprintf(file, "\\end{document}\n");

  fclose(file); file = NULL;
  system("pdflatex -output-directory=log_folder_differenciator\\LATEX log_folder_differenciator\\LATEX\\LATEX_dump.tex -quiet");

  return diff_dump_success;
}

int generate_latex_dump(diff_node_t* node, FILE* file)
{
  DIFF_DUMP_ASSERT(node, file);

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
        fprintf(file, ")");
        fprintf(file, "\\cdot");
        fprintf(file, "(");
        generate_latex_dump(node->right, file);
        fprintf(file, ")");
        break;
      }

      case ADD:
        fprintf(file, "(");
        generate_latex_dump(node->left, file);
        fprintf(file, ")");
        fprintf(file, " + ");
        fprintf(file, "(");
        generate_latex_dump(node->right, file);
        fprintf(file, ")");
        break;

      case SUB:
      {
        fprintf(file, "(");
        generate_latex_dump(node->left, file);
        fprintf(file, ")");
        fprintf(file, " - ");
        fprintf(file, "(");
        generate_latex_dump(node->right, file);
        fprintf(file, ")");
        break;
      }

      case SIN:
      {
        fprintf(file, "\\sin{(");
        generate_latex_dump(node->right, file);
        fprintf(file, ")}");
        break;
      }

      case COS:
      {
        fprintf(file, "\\cos{(");
        generate_latex_dump(node->right, file);
        fprintf(file, ")}");
        break;
      }

      case SQRT:
      {
        fprintf(file, "\\sqrt{(");
        generate_latex_dump(node->right, file);
        fprintf(file, ")}");
        break;
      }

      case POW:
      {
        fprintf(file, "(");
        generate_latex_dump(node->left, file);
        fprintf(file, ")^{(");
        generate_latex_dump(node->right, file);
        fprintf(file, ")}");
        break;
      }

      case LOG:
      {
        fprintf(file, "(\\log_{");
        generate_latex_dump(node->left, file);
        fprintf(file, "}{(");
        generate_latex_dump(node->right, file);
        fprintf(file, ")})");
        break;
      }

      case LN:
      {
        fprintf(file, "(\\ln{(");
        generate_latex_dump(node->right, file);
        fprintf(file, ")})");
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