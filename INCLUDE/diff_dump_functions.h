#ifndef DIFF_DUMP_FUNCTION
#define DIFF_DUMP_FUNCTION

#include"const_in_diff.h"
#include<stdio.h>
#include<assert.h>
#include<stdlib.h>

#define file_graph_input  "log_folder_differenciator//differenciator_graph.dot"
#define file_graph_output "log_folder_differenciator//differenciator_graph.png"

enum diff_dump_status
{
    diff_dump_failure = 0,
    diff_dump_success = 1,
};

diff_dump_status node_dump(const diff_node_t* node);

diff_dump_status print_node_graph(const diff_node_t* node, const char* file);
diff_dump_status generate_graph(const diff_node_t* node, FILE* file);

diff_dump_status analitical_latex_dump(const diff_node_t* node, const diff_node_t* diffed_node, 
                                       const dvalue_t* derivative_value_buffer, const int degree, const dvalue_t variable, const char* file_name);
diff_dump_status latex_dump(const diff_node_t* node, const char* file);
diff_dump_status generate_latex_dump(const diff_node_t* node, FILE* file);
diff_dump_status generate_latex_function(const diff_node_t* node, FILE* file);

#endif