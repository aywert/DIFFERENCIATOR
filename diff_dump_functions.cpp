#include"INCLUDE\\diff_dump_functions.h"

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

int print_node_graph(diff_node_t* node, const char* file_name)
{
    assert(node);
    assert(file_name);
    
    FILE* file = fopen(file_name, "w");
    fprintf(file, "digraph list\n{\nrankdir=HR;\n\t");

    generate_graph(node, file);

    fprintf(file, "}");
    fclose(file); file = NULL;
    system("dot -T png log_folder_differenciator//differenciator_graph.dot -o  log_folder_differenciator//differenciator_graph.png -Gcharset=latin1");
    return 0;
}

int generate_graph(diff_node_t* node, FILE* file)
{
    assert(node);
    assert(file);
    
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

    return 0;
}

int latex_dump(diff_node_t* node, const char* file_name)
{
  assert(file_name);
  assert(node);

  FILE* file = fopen(file_name, "w");

  fprintf(file, "\\documentclass{article}\n\\begin{document}\n");
  fprintf(file, "$");
  generate_latex_dump(node, file);
  fprintf(file, "$\n");
  fprintf(file, "\\end{document}\n");

  fclose(file); file = NULL;
  system("pdflatex -output-directory=log_folder_differenciator\\LATEX log_folder_differenciator\\LATEX\\LATEX_dump.tex -quiet");

  return 0;
}

int generate_latex_dump(diff_node_t* node, FILE* file)
{
  assert(node);
  assert(file);

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