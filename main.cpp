#include"INCLUDE\\diff_derivative_functions.h"
#include"INCLUDE\\diff_reading_functions.h"
#include"INCLUDE\\diff_dump_functions.h"

const char* reading_file               = "log_folder_differenciator//READING_file.txt";
const char* file_for_LATEX             = "log_folder_differenciator//LATEX//LATEX_dump.tex";
const char* output_directory_for_LATEX = "log_folder_differenciator//LATEX";
const char* file_for_graphviz          = "log_folder_differenciator//differenciator_graph.dot";
const char* file_for_grapviz_output    = "log_folder_differenciator//differenciator_graph.png";

int main(void)
{ 
    get_analitics(reading_file, file_for_LATEX, output_directory_for_LATEX);
    // diff_node_t* node = diff_reader("log_folder_differenciator//READING_file.txt");
    // diff_node_t* diffed_node = {};
    // diffed_node = get_derivative_of_node(node);
    // dvalue_t variable = 3;
    // simplify_function(diffed_node, variable);
    // latex_dump(diffed_node, file_for_LATEX, output_directory_for_LATEX);
    //print_node_graph(diffed_node, "log_folder_differenciator//differenciator_graph.dot", "log_folder_differenciator//differenciator_graph.png");
    // tree_dtor(diffed_node);
    // tree_dtor(node);

    return 0;
}
