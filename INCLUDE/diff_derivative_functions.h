#ifndef DIFF_DERIVATIVE_FUNC
#define DIFF_DERIVATIVE_FUNC

#include"const_in_diff.h"
#include<math.h>

const long double epsilon_for_comparing_doubles = 0.000001;
const int poison_colculation = -666;

enum branch_status 
{
    var_on_the_branch    = 0,
    var_not_on_the_branch = 1,
};

enum double_compare_status
{
    double_bigger   = 1,
    double_equal    = 0,
    double_smaller = -1,
};

void simplify_function(diff_node_t* node, dvalue_t variable);

branch_status is_var_on_the_branch(diff_node_t* node);
diff_node_t* simple_fire(diff_node_t* node);
double_compare_status compare_double(double a, double b);

dvalue_t calculate_value(diff_node_t* node, dvalue_t variable);
diff_node_t* get_derivative_of_node(diff_node_t* node);
diff_node_t* get_copy_of_node(diff_node_t* node);

#endif