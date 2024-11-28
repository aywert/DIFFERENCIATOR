#ifndef DIFF_DERIVATIVE_FUNC
#define DIFF_DERIVATIVE_FUNC

#include"const_in_diff.h"
#include<math.h>

const long double epsilon_for_comparing_doubles = 0.000001;
const int poison_calculation = -666;

enum compare_tree_status
{
    different_trees = 0,
    equal_trees = 1,
};

enum simplify_status
{
    cant_be_simplified = 0,
    can_be_simplified  = 1,
    TYPE_ERROR_SMPLF = 2,
};

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

compare_tree_status compare_tree(diff_node_t* root_1, diff_node_t* root_2);

void simplify_function(diff_node_t* node, dvalue_t variable);
void make_easy_reduction(diff_node_t* node);
void count_countable_nodes(diff_node_t* node, dvalue_t variable);
void replace_node(diff_node_t* node_to_replace, diff_node_t* new_node);
simplify_status simple_fire(diff_node_t* node);

branch_status is_var_on_the_branch(diff_node_t* node);
double_compare_status compare_double(double a, double b);

dvalue_t calculate_value(diff_node_t* node, dvalue_t variable);
diff_node_t* get_derivative_of_node(diff_node_t* node);
diff_node_t* get_copy_of_node(diff_node_t* node);

#endif