#ifndef MHE_PROJECT_NONOGRAM_ALGORITHMS_H
#define MHE_PROJECT_NONOGRAM_ALGORITHMS_H

#include "../Header_Files/libraries.h"

nonogram_t sim_ann(const nonogram_t &nonogram, int iterations, bool show_time, bool show_convergence_curve,
                   bool show_solution, bool show_quality, bool show_iterations, bool show_function_calls,
                   std::function<double(int)> T = [](int k) { return 1000.0 / k + 1; });

nonogram_t tabu(const nonogram_t &nonogram, int iterations, int tabu_size, bool show_time, bool show_convergence_curve,
                bool show_solution, bool show_quality, bool show_iterations, bool show_function_calls);

nonogram_t hill_climb_det(const nonogram_t &nonogram, int iterations, bool show_time, bool show_convergence_curve,
                          bool show_solution, bool show_quality, bool show_iterations, bool show_function_calls);

nonogram_t hill_climb(const nonogram_t &nonogram, int iterations, bool show_time, bool show_convergence_curve,
                      bool show_solution, bool show_quality, bool show_iterations, bool show_function_calls);

nonogram_t random_solution(const nonogram_t &nonogram, int iterations, bool show_time, bool show_convergence_curve,
                           bool show_solution, bool show_quality, bool show_iterations, bool show_function_calls);

nonogram_t brute_force(nonogram_t nonogram, int iterations, bool show_time, bool show_convergence_curve,
                       bool show_solution, bool show_quality, bool show_iterations, bool show_function_calls);

nonogram_t gen_alg(const nonogram_t &nonogram, int iterations, bool show_time, bool show_convergence_curve,
                   bool show_solution, bool show_quality, bool show_iterations, bool show_function_calls,
                   int populations_size, double crossover_probability, double mutation_probability,
                   nonogram_t &solution_nonogram);

#endif //MHE_PROJECT_NONOGRAM_ALGORITHMS_H
