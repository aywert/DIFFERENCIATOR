#ifndef DIFF_DERIVATIVE_FUNC
#define DIFF_DERIVATIVE_FUNC

#include"const_in_diff.h"
#include<math.h>

double calculate_value(diff_node_t* node, double variable);
diff_node_t* get_derivative_of_node(diff_node_t* node);
diff_node_t* get_copy_of_node(diff_node_t* node);

#endif