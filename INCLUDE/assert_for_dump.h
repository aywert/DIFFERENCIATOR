#ifndef DIFF_ASSERT_FOR_DUMP
#define DIFF_ASSERT_FOR_DUMP

#define DIFF_DUMP_ASSERT(X, Y) if (verifier_for_dump_functions(X, (const char*)Y) == diff_dump_failure) return diff_dump_failure;

#endif