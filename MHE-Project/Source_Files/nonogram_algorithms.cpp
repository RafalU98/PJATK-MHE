#include "../Header_Files/nonogram_algorithms.h"

nonogram_t sim_ann(const nonogram_t &nonogram, int iterations, bool show_time, bool show_convergence_curve,
                   bool show_solution, bool show_quality, bool show_iterations, bool show_function_calls,
                   std::function<double(int)> T) {
    auto start = std::chrono::high_resolution_clock::now();
    auto s = generate_random_solution(nonogram);
    //auto s = generate_neighbour(nonogram);
    auto best = s;
    int calls = 0, found = 0, iter = 0;
    static std::random_device rd;
    static std::mt19937 rand(rd());

    for (int n = 0; n < iterations; n++) {
        iter++;
        auto t = generate_neighbour_almost_normal(best);
        if (evaluate(t) < evaluate(s)) {
            s = t;
            calls++;
            if (evaluate(s) < evaluate(best)) {
                best = s;
                found = n;
            }
            if (evaluate(best) == 0) break;
        } else {
            std::uniform_real_distribution<double> distribution(0.0, 1.0);
            double v = std::exp(-std::abs(evaluate(t)) / T(n));
            if (distribution(rand) < v) {
                s = t;
            }
        }
        if (show_convergence_curve) {
            auto time = std::chrono::high_resolution_clock::now();
            auto currentDuration = std::chrono::duration_cast<std::chrono::microseconds>(time - start);
            //std::cout << n << " " << evaluate(t) << " " << currentDuration.count() / 1e6 << std::endl;
            std::cout << "Step: " << n << " Mistakes: " << evaluate(t) << " Time Passed: " <<
                      currentDuration.count() / 1e6  << "\n" << t << std::endl;
        }
    }
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

    if (show_time) std::cout << "Time: " << duration.count() / 1e6 << " seconds." << std::endl;
    if (show_solution) std::cout << "Result:\n" << best;
    if (show_quality) std::cout << "Mistakes: " << evaluate(best) << std::endl;
    if (show_iterations) std::cout << "Iterations made: " << iter << ". Earliest Best found at: " << found << std::endl;
    if (show_function_calls) std::cout << "Evaluation Function calls: " << calls << std::endl;

    return best;
}

nonogram_t tabu(const nonogram_t &nonogram, int iterations, int tabu_size, bool show_time, bool show_convergence_curve,
                bool show_solution, bool show_quality, bool show_iterations, bool show_function_calls) {

    auto start = std::chrono::high_resolution_clock::now();
    int calls = 0, found = 0, iter = 0;

    std::list<nonogram_t> tabu_list;
    tabu_list.push_back(generate_random_solution(nonogram));
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
            return best;
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
        if (show_convergence_curve) {
            auto time = std::chrono::high_resolution_clock::now();
            auto currentDuration = std::chrono::duration_cast<std::chrono::microseconds>(time - start);
            //std::cout << n << " " << evaluate(tabu_list.back()) << " " << currentDuration.count() / 1e6 << std::endl;
            std::cout << "Step: " << n << " Mistakes: " << evaluate(tabu_list.back()) << " Time Passed: " <<
                      currentDuration.count() / 1e6 << "\n" << tabu_list.back() <<  std::endl;
        }
    }

    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

    if (show_time) std::cout << "Time: " << duration.count() / 1e6 << " seconds." << std::endl;
    if (show_solution) std::cout << "Result:\n" << best;
    if (show_quality) std::cout << "Mistakes: " << evaluate(best) << std::endl;
    if (show_iterations) std::cout << "Iterations made: " << iter << ". Earliest Best found at: " << found << std::endl;
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
        }
        if (evaluate(best) == 0) {
            break;
        }
        if (show_convergence_curve) {
            auto time = std::chrono::high_resolution_clock::now();
            auto currentDuration = std::chrono::duration_cast<std::chrono::microseconds>(time - start);
            //std::cout << n << " " << evaluate(newResult) << " " << currentDuration.count() / 1e6 << std::endl;
            std::cout << "Step: " << n << " Mistakes: " << evaluate(newResult) << " Time Passed: " <<
                      currentDuration.count() / 1e6 << std::endl;
        }
    }

    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

    if (show_time) std::cout << "Time: " << duration.count() / 1e6 << " seconds." << std::endl;
    if (show_solution) std::cout << "Result:\n" << best;
    if (show_quality) std::cout << "Mistakes: " << evaluate(best) << std::endl;
    if (show_iterations) std::cout << "Iterations made: " << iter << ". Earliest Best found at: " << found << std::endl;
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
        if (show_convergence_curve) {
            auto time = std::chrono::high_resolution_clock::now();
            auto currentDuration = std::chrono::duration_cast<std::chrono::microseconds>(time - start);
            //std::cout << n << " " << evaluate(newResult) << " " << currentDuration.count() / 1e6 << std::endl;
            std::cout << "Step: " << n << " Mistakes: " << evaluate(newResult) << " Time Passed: " <<
                      currentDuration.count() / 1e6 << std::endl;
        }
    }

    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

    if (show_time) std::cout << "Time: " << duration.count() / 1e6 << " seconds." << std::endl;
    if (show_solution) std::cout << "Result:\n" << best;
    if (show_quality) std::cout << "Mistakes: " << evaluate(best) << std::endl;
    if (show_iterations) std::cout << "Iterations made: " << iter << ". Earliest Best found at: " << found << std::endl;
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
        if (show_convergence_curve) {
            auto time = std::chrono::high_resolution_clock::now();
            auto currentDuration = std::chrono::duration_cast<std::chrono::microseconds>(time - start);
            //std::cout << n << " " << evaluate(rand) << " " << currentDuration.count() / 1e6 << std::endl;
            std::cout << "Step: " << n << " Mistakes: " << evaluate(rand) << " Time Passed: " <<
                      currentDuration.count() / 1e6 << std::endl;
        }
        if (evaluate(best) == 0) break;
    }

    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

    if (show_time) std::cout << "Time: " << duration.count() / 1e6 << " seconds." << std::endl;
    if (show_solution) std::cout << "Result:\n" << best;
    if (show_quality) std::cout << "Mistakes: " << evaluate(best) << std::endl;
    if (show_iterations) std::cout << "Iterations made: " << iter << ". Earliest Best found at: " << found << std::endl;
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
        if (show_convergence_curve) {
            auto time = std::chrono::high_resolution_clock::now();
            auto currentDuration = std::chrono::duration_cast<std::chrono::microseconds>(time - start);
            //std::cout << n << " " << evaluate(nonogram) << " " << currentDuration.count() / 1e6 << std::endl;
            std::cout << "Step: " << n << " Mistakes: " << evaluate(nonogram) << " Time Passed: " <<
                      currentDuration.count() / 1e6 << std::endl;
        }
        if (evaluate(best) == 0) break;
    }

    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

    if (show_time) std::cout << "Time: " << duration.count() / 1e6 << " seconds." << std::endl;
    if (show_solution) std::cout << "Result:\n" << best;
    if (show_quality) std::cout << "Mistakes: " << evaluate(best) << std::endl;
    if (show_iterations) std::cout << "Iterations made: " << iter << ". Earliest Best found at: " << found << std::endl;
    if (show_function_calls) std::cout << "Evaluation Function calls: " << calls << std::endl;

    return best;
}