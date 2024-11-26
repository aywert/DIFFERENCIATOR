#ifndef DIFF_FUNC
#define DIFF_FUNC

#include"const_in_diff.h"
#include"stdlib.h"
#include<string.h>
#include<math.h>
#include<sys\stat.h>

#define file_for_LATEX   "log_folder_differenciator//LATEX//LATEX_dump.tex"
#define file_for_reading "log_folder_differenciator//READING_file.txt"

enum
{
    NOT_AN_OPERATOR_PTR = -1,
};

diff_node_t* ctor_node(types_for_diff type, /*union value_t*/ int value, diff_node_t* left, diff_node_t* right);
int tree_dtor(diff_node_t* root);
int dtor_node(diff_node_t* node_ptr);

diff_node_t* diff_reader(const char* file);
diff_node_t* diff_reader_recursion(char* buffer);

#endif