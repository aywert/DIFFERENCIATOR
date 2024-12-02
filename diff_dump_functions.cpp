#include"INCLUDE\\diff_dump_functions.h"
#include"INCLUDE\\diff_reading_functions.h"
#include"INCLUDE\\assert_for_dump.h"

static diff_dump_status verifier_for_dump_functions(diff_node_t* node, char* file_name)
{
  if (node == NULL)
  {
    printf(RED("%s have recieved null-pointer on ") BLUE("node") RED(" and is not able to do anything with it\n"), __FUNCTION__);
    printf(YELLOW("Returning zero\n"));
    return diff_dump_failure;
  }
    
  if (file_name == NULL)
  {
    printf(RED("%s have recieved null-pointer on ") BLUE("file") RED(" and is not able to do anything with it\n"), __FUNCTION__);
    printf(YELLOW("Returning zero\n"));
    return diff_dump_failure;
  }

  return diff_dump_success;
}

diff_dump_status node_dump(diff_node_t* node)
{
  DIFF_DUMP_ASSERT(node, 1);

  printf("(");

  if (node->type == NUM)
      printf("%lg", node->value);

  else
      printf("%c", (char)node->value);

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
        fprintf(file, "%d [shape = Mrecord; style = filled; fillcolor=\"#4682b4\"; color = \"#000000\"; fontcolor = \"#000000\"; label = \"{ NUM | value = %lg | left = %p| right = %p}\"];\n\t", 
                    (int)&node->value,                                                                                                          node->value,  node->left,     node->right);
    }

    if (node->type == VAR)
    {
        fprintf(file, "%d [shape = Mrecord; style = filled; fillcolor=\"#ff7da3\"; color = \"#000000\"; fontcolor = \"#000000\"; label = \"{ VAR | value = %c | left = %p| right = %p}\"];\n\t", 
        (int)&node->value,                                                                                                                        (char)node->value,  node->left,     node->right);
    }

    if (node->type == OP)
    {
        fprintf(file, "%d [shape = Mrecord; style = filled; fillcolor=\"#ffc765\"; color = \"#000000\"; fontcolor = \"#000000\"; label = \"{ OP | value = %c | left = %p| right = %p}\"];\n\t", 
        (int)&node->value,                                                                                                                       (char)node->value,  node->left,     node->right);
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

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

diff_dump_status analitical_latex_dump(diff_node_t* node, diff_node_t* diffed_node, dvalue_t* derivative_value_buffer, int degree, dvalue_t variable, const char* file_name)
{
  DIFF_DUMP_ASSERT(node, 1);
  FILE* file = fopen(file_name, "w");
  
  if (file == NULL)
  {
    fclose(file); file = NULL;
    return diff_dump_failure;
  }

  fprintf(file, "\\documentclass{article}\n");

  fprintf(file, 
  "\\usepackage{multirow}\n"
  "\\usepackage{wrapfig}\n"
  "\\usepackage[T2A]{fontenc}\n"
  "\\usepackage[utf8]{inputenc}\n"
  "\\usepackage[english,russian]{babel}\n"
  "\\usepackage{graphicx}\n"
  "\\usepackage{todonotes}\n"

  "\\usepackage{amsmath,amsfonts,amssymb,amsthm,mathtools}\n" 
  "\\usepackage{hyperref}\n"
  "\\usepackage{pgfplots}\n"
  "\\pgfplotsset{compat=1.9}\n");
    
  // \\begin{titlepage}\n 
    fprintf(file, 
  "\\begin{document}\n\\begin{center}\n"
  "{\\large МОСКОВСКИЙ ФИЗИКО-ТЕХНИЧЕСКИЙ ИНСТИТУТ (НАЦИОНАЛЬНЫЙ ИССЛЕДОВАТЕЛЬСКИЙ УНИВЕРСИТЕТ)}\n"
  "\\end{center}\n"
  "\\begin{center}\n"
  "{\\largeФизтех-школа Радиотехники и компьютерных технологий}\n"
  "\\end{center}\n"
  "\\vspace{3.5cm}\n"
  "\\vspace{0.1cm}\n"
  "{\\huge\n"
  "\\begin{center}\n"
  "{\\bf Дифференциальная работа 3.3.3}\\\n"
  "\\end{center}\n"
  "}\n"
  "\\vspace{5cm}\n"
  "{\\LARGE Авторы:\\\\ Мовсесян Михаил \\\\\n"
  "\\vspace{0.2cm}\n"
  "Б01-403}\n"
  "\\end{flushright}\n"
  "\\vspace{1.5cm}\n"
  "\\begin{center}\n"
  "Долгопрудный 2024\n"
  "\\end{center}\n"
  "\\end{titlepage}");

  fprintf(file, 
  "\\begin{flushleft}\n"
  "Рассмотрим функцию f(x) = $");
  diff_dump_status status = generate_latex_dump(node, file);
  fprintf(file, "$ \\\\ \n");
  fprintf(file, 
  "Ее график имеет вид: \\\\\\\\ \n"
  /*"\\vspace{1.5см}\n"*/);
  fprintf(file, 
  "\\begin{centering}"
  "\\begin{tikzpicture}\n"
  "\\begin{axis}[\n");
 
  fprintf(file,
  "xlabel = {$x$},\n"
  "ylabel = {$f(x)$},\n"
  "width  = 450,\n"
  "height = 450,\n"
  "minor tick num = 2\n"
  "]\n"
  "\\addplot[blue, samples = 1000] {");
  generate_latex_function(node, file);
  fprintf(file,"}; \\\\\\\\ \n"
  //"\\addplot[red, samples = 1000] {sin(deg(-x))};\n"
  "\\end{axis}\n"
  "\\end{tikzpicture}\n");

  fprintf(file, 
  "\\begin{flushleft}\n"
  "Её производная $f^{\\prime}(x) = ");
  status = generate_latex_dump(diffed_node, file);
  fprintf(file, "$ \\\\ \n");
  fprintf(file, 
  "Ее график имеет вид: \\\\\\\\ \n"
  /*"\\vspace{1.5см}\n"*/);
  fprintf(file, 
  "\\begin{centering}"
  "\\begin{tikzpicture}\n"
  "\\begin{axis}[\n");
 
  fprintf(file,
  "xlabel = {$x$},\n"
  "ylabel = {$f(x)$},\n"
  "width  = 450,\n"
  "height = 450,\n"
  "minor tick num = 2\n"
  "]\n"
  "\\addplot[blue, samples = 1000] {");
  generate_latex_function(diffed_node, file);
  fprintf(file,"};\n"
  
  "\\end{axis}\n"
  "\\end{tikzpicture}\n");

  fprintf(file, "Проведем более детальный анализ функции $f(x)$ в точке x = %lg:", variable);

  fprintf(file, "$$f(x) = %lg", derivative_value_buffer[0]);
  for (int index = 1; index <= degree; index++)
  {
    fputs(" + ", file);
    fprintf(file, "\\frac{%lg}{%d!} \\cdot (x - %lg)^{%d}", derivative_value_buffer[index], index, variable, index);
  }
  fprintf(file, " + o((x - %lg)^{%d})", variable, degree);

  fprintf(file, "\\end{document}\n");
  tree_dtor(node);
  fclose(file); file = NULL;

  if (status == diff_dump_failure)
    return diff_dump_failure;

  system("pdflatex -output-directory=log_folder_differenciator\\LATEX log_folder_differenciator\\LATEX\\LATEX_dump.tex -quiet");
  return diff_dump_success;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

diff_dump_status latex_dump(diff_node_t* node, const char* file_name)
{
  DIFF_DUMP_ASSERT(node, 1);
  FILE* file = fopen(file_name, "w");
  
  if (file == NULL)
  {
    fclose(file); file = NULL;
    return diff_dump_failure;
  }

  fprintf(file, "\\documentclass{article}\n");
  fprintf(file, "$");
  diff_dump_status status = generate_latex_dump(node, file);
  fprintf(file, "$\n");

  fprintf(file, "\\end{document}\n");

  fclose(file); file = NULL;

  if (status == diff_dump_failure)
    return diff_dump_failure;

  system("pdflatex -output-directory=log_folder_differenciator\\LATEX log_folder_differenciator\\LATEX\\LATEX_dump.tex -quiet");
  return diff_dump_success;
}

diff_dump_status generate_latex_function(diff_node_t* node, FILE* file)
{
  DIFF_DUMP_ASSERT(node, file);
  switch(node->type)
  {
    case OP:

    switch((int)node->value)
    {
      case DIV:
      {
        fprintf(file, "(");
        generate_latex_function(node->left, file);
        fprintf(file, "/");
        generate_latex_function(node->right, file);
        fprintf(file, ")");
        break;
      }

      case MUL:
      {
        fprintf(file, "(");
        generate_latex_function(node->left, file);
        fprintf(file, ")");
        fprintf(file, "*");
        fprintf(file, "(");
        generate_latex_function(node->right, file);
        fprintf(file, ")");
        break;
      }

      case ADD:
      {
        fprintf(file, "(");
        generate_latex_function(node->left, file);
        fprintf(file, ")");
        fprintf(file, " + ");
        fprintf(file, "(");
        generate_latex_function(node->right, file);
        fprintf(file, ")");
        break;
      }

      case SUB:
      {
        fprintf(file, "(");
        generate_latex_function(node->left, file);
        fprintf(file, ")");
        fprintf(file, " - ");
        fprintf(file, "(");
        generate_latex_function(node->right, file);
        fprintf(file, ")");
        break;
      }

      case SIN:
      {
        fprintf(file, "sin(deg(");
        generate_latex_function(node->right, file);
        fprintf(file, "))");
        break;
      }

      case COS:
      {
        fprintf(file, "cos(deg(");
        generate_latex_function(node->right, file);
        fprintf(file, "))");
        break;
      }

      case SQRT:
      {
        fprintf(file, "sqrt(");
        generate_latex_function(node->right, file);
        fprintf(file, ")");
        break;
      }

      case POW:
      {
        fprintf(file, "(");
        generate_latex_function(node->left, file);
        fprintf(file, ")^(");
        generate_latex_function(node->right, file);
        fprintf(file, ")");
        break;
      }

      case LOG:
      {
        fprintf(file, "(\\ln(");
        generate_latex_function(node->left, file);
        fprintf(file, ")/ln(");
        generate_latex_function(node->right, file);
        fprintf(file, "))");
        break;
      }

      case LN:
      {
        fprintf(file, "ln(");
        generate_latex_dump(node->right, file);
        fprintf(file, ")");
        break;
      }

      default:
      {
        printf(RED("SNTX_LATEX_ERROR\n"));
        return diff_dump_failure;
        break;
      }
    }
    break;

    case NUM: fprintf(file, "%lg", node->value); break;
    case VAR: fprintf(file, "%c", (char)node->value); break;
    default:
    printf(RED("LATEX_dump dead\n"));
    return diff_dump_failure;
  }

    return diff_dump_success;
}

diff_dump_status generate_latex_dump(diff_node_t* node, FILE* file)
{
  DIFF_DUMP_ASSERT(node, file);

  switch(node->type)
  {
    case OP:

    switch((int)node->value)
    {
      case DIV:
      {
        fprintf(file, "\\frac{");
        generate_latex_dump(node->left, file);
        fprintf(file, "}{");
        generate_latex_dump(node->right, file);
        fprintf(file, "}");
        break;
      }

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
      {
        fprintf(file, "(");
        generate_latex_dump(node->left, file);
        fprintf(file, ")");
        fprintf(file, " + ");
        fprintf(file, "(");
        generate_latex_dump(node->right, file);
        fprintf(file, ")");
        break;
      }

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
      {
        printf(RED("SNTX_LATEX_ERROR\n"));
        return diff_dump_failure;
        break;
      }
    }
    break;

    case NUM: fprintf(file, "%lg", node->value); break;
    case VAR: fprintf(file, "%c", (char)node->value); break;
    default:
    printf(RED("LATEX_dump dead\n"));
    return diff_dump_failure;
  }

    return diff_dump_success;
}