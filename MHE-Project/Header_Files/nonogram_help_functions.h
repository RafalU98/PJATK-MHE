#ifndef MHE_PROJECT_NONOGRAM_HELP_FUNCTIONS_H
#define MHE_PROJECT_NONOGRAM_HELP_FUNCTIONS_H

#include "../Header_Files/libraries.h"

int count_inconsistent(const nonogram_t &nonogram);
double evaluate(const nonogram_t &nonogram);
bool next_solution(nonogram_t &nonogram);
nonogram_t generate_random_solution(const nonogram_t &nonogram);
std::vector<nonogram_t> generate_neighbours(const nonogram_t &nonogram);
nonogram_t generate_neighbour(const nonogram_t &nonogram);
nonogram_t generate_best_neighbour(const nonogram_t &nonogram);
bool operator==(nonogram_t left, nonogram_t right);

#endif //MHE_PROJECT_NONOGRAM_HELP_FUNCTIONS_H
