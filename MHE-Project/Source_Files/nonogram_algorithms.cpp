#include "../Header_Files/nonogram_algorithms.h"
nonogram_t tabu(const nonogram_t &nonogram, int iterations, int tabu_size, bool show_time, bool show_convergence_curve,
                bool show_solution, bool show_quality, bool show_iterations, bool show_function_calls) {

    auto start = std::chrono::high_resolution_clock::now();
    int calls = 0, found = 0, iter = 0;
    std::list<nonogram_t> tabu_list;
    tabu_list.push_back(nonogram);
    auto best = tabu_list.back();

    for (int n = 0; n < iterations; n++) {
        iter++;
        if (evaluate(tabu_list.back()) == 0) {
            break;
        }
        std::vector<nonogram_t> neighbours;
        for (const auto &element: generate_neighbours(tabu_list.back())) {
            bool finder = (std::find(tabu_list.begin(), tabu_list.end(), element) != tabu_list.end());
            if (!finder) neighbours.push_back(element);
        }
        if (neighbours.empty()) {
            std::cerr << "Method got stuck at iteration: " << n << "\nBest Solution was: " <<
                      evaluate(best) << "\n" << best << "List Size: " << tabu_list.size() << std::endl;
        }
        tabu_list.push_back(*std::min_element(neighbours.begin(), neighbours.end(),
                                              [](auto left, auto right) {
                                                  return evaluate(left) < evaluate(right);
                                              }));
        if (evaluate(tabu_list.back()) <= evaluate(best)) {
            found = n;
            calls++;
            best = tabu_list.back();
        }
        if (tabu_list.size() > tabu_size) tabu_list.pop_front();
        if (show_convergence_curve) std::cout << "Step: " << n << " Mistakes: " << evaluate(best) << std::endl;
    }

    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

    if (show_time) std::cout << "Time: " << duration.count() / 1e6 << " seconds." << std::endl;
    if (show_solution) std::cout << "Result:\n" << best;
    if (show_quality) std::cout << "Mistakes: " << evaluate(best) << std::endl;
    if (show_iterations) std::cout << "Iterations made: " << iter << ". Best found at: " << found << std::endl;
    if (show_function_calls) std::cout << "Evaluation Function calls: " << calls << std::endl;

    return best;
}

nonogram_t hill_climb_det(const nonogram_t &nonogram, int iterations, bool show_time, bool show_convergence_curve,
                          bool show_solution, bool show_quality, bool show_iterations, bool show_function_calls) {

    auto start = std::chrono::high_resolution_clock::now();
    auto best = nonogram;
    int calls = 0, found = 0, iter = 0;

    for (int n = 0; n < iterations; n++) {
        iter++;
        auto newResult = generate_best_neighbour(best);
        if (evaluate(newResult) < evaluate(best)) {
            best = newResult;
            calls++;
            found = n;
            break;
        }
        if (show_convergence_curve) std::cout << "Step: " << n << " Mistakes: " << evaluate(best) << std::endl;
    }

    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

    if (show_time) std::cout << "Time: " << duration.count() / 1e6 << " seconds." << std::endl;
    if (show_solution) std::cout << "Result:\n" << best;
    if (show_quality) std::cout << "Mistakes: " << evaluate(best) << std::endl;
    if (show_iterations) std::cout << "Iterations made: " << iter << ". Best found at: " << found << std::endl;
    if (show_function_calls) std::cout << "Evaluation Function calls: " << calls << std::endl;

    return best;
}

nonogram_t hill_climb(const nonogram_t &nonogram, int iterations, bool show_time, bool show_convergence_curve,
                      bool show_solution, bool show_quality, bool show_iterations, bool show_function_calls) {

    auto start = std::chrono::high_resolution_clock::now();
    auto best = nonogram;
    int calls = 0, found = 0, iter = 0;

    for (int n = 0; n < iterations; n++) {
        iter++;
        auto newResult = generate_neighbour(best);
        if (evaluate(newResult) <= evaluate(best)) {
            calls++;
            best = newResult;
            found = n;
        }
        if (show_convergence_curve) std::cout << "Step: " << n << " Mistakes: " << evaluate(best) << std::endl;
    }

    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

    if (show_time) std::cout << "Time: " << duration.count() / 1e6 << " seconds." << std::endl;
    if (show_solution) std::cout << "Result:\n" << best;
    if (show_quality) std::cout << "Mistakes: " << evaluate(best) << std::endl;
    if (show_iterations) std::cout << "Iterations made: " << iter << ". Best found at: " << found << std::endl;
    if (show_function_calls) std::cout << "Evaluation Function calls: " << calls << std::endl;

    return best;
}

nonogram_t random_solution(const nonogram_t &nonogram, int iterations, bool show_time, bool show_convergence_curve,
                           bool show_solution, bool show_quality, bool show_iterations, bool show_function_calls) {

    auto start = std::chrono::high_resolution_clock::now();
    auto best = generate_random_solution(nonogram);
    int calls = 0, found = 0, iter = 0;

    for (int n = 0; n < iterations; n++) {
        iter++;
        auto rand = generate_random_solution(nonogram);
        if (evaluate(rand) < evaluate(best)) {
            calls++;
            best = rand;
            found = n;
        }
        if (show_convergence_curve) std::cout << "Step: " << n << " Mistakes: " << evaluate(best) << std::endl;
        if (evaluate(best) == 0) break;
    }

    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

    if (show_time) std::cout << "Time: " << duration.count() / 1e6 << " seconds." << std::endl;
    if (show_solution) std::cout << "Result:\n" << best;
    if (show_quality) std::cout << "Mistakes: " << evaluate(best) << std::endl;
    if (show_iterations) std::cout << "Iterations made: " << iter << ". Best found at: " << found << std::endl;
    if (show_function_calls) std::cout << "Evaluation Function calls: " << calls << std::endl;

    return best;
}

nonogram_t brute_force(nonogram_t nonogram, int iterations, bool show_time, bool show_convergence_curve,
                       bool show_solution, bool show_quality, bool show_iterations, bool show_function_calls) {

    auto start = std::chrono::high_resolution_clock::now();
    auto best = nonogram;
    int calls = 0, found = 0, iter = 0;

    for (int n = 0; n < iterations; n++) {
        iter++;
        next_solution(nonogram);
        if (evaluate(nonogram) < evaluate(best)) {
            calls++;
            best = nonogram;
            found = n;
        }
        if (show_convergence_curve) std::cout << "Step: " << n << " Mistakes: " << evaluate(best) << std::endl;
        if (evaluate(best) == 0) break;
    }

    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

    if (show_time) std::cout << "Time: " << duration.count() / 1e6 << " seconds." << std::endl;
    if (show_solution) std::cout << "Result:\n" << best;
    if (show_quality) std::cout << "Mistakes: " << evaluate(best) << std::endl;
    if (show_iterations) std::cout << "Iterations made: " << iter << ". Best found at: " << found << std::endl;
    if (show_function_calls) std::cout << "Evaluation Function calls: " << calls << std::endl;

    return best;
}