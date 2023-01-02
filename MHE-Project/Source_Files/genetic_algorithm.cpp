#include "../Header_Files/nonogram_algorithms.h"

std::random_device rd;
std::mt19937 ga_random(rd());

double fitness(const nonogram_t &nonogram, nonogram_t &solution) {
    int mistakes = 0;
    for (int i = 0; i < solution.board.size(); i++) {
        if (nonogram.board[i] != solution.board[i]) {
            mistakes++;
        }
    }
    return mistakes;
}

std::vector<int> selection(const std::vector<double> &population_fitnesses) {
    std::uniform_int_distribution<> distribution(0, population_fitnesses.size() - 1);
    std::vector<int> selection_return;
    while (selection_return.size() < population_fitnesses.size()) {
        int a = distribution(ga_random), b = distribution(ga_random);
        selection_return.push_back((population_fitnesses[a] < population_fitnesses[b]) ? a : b);
    }
    return selection_return;
}

std::vector<nonogram_t> crossover(const std::vector<nonogram_t> current_pair) {
    std::vector<nonogram_t> offspring = current_pair;
    std::uniform_int_distribution<int> distribution(0, current_pair[0].board.size() - 1);
    int split = distribution(ga_random);
    for (int i = 0; i < split; i++) {
        std::swap(offspring[0].board[i], offspring[1].board[i]);
    }
    return offspring;
}

nonogram_t mutation(nonogram_t &nonogram) {
    std::uniform_int_distribution<> distribution(0, nonogram.board.size() - 1);
    int a(distribution(ga_random)), b(distribution(ga_random));
    auto mutant = nonogram;
    std::swap(mutant.board[a], mutant.board[b]);
    return mutant;
}

auto print_population = [](auto results, nonogram_t &solution) {
    for (auto e: results)
        std::cout << fitness(e, solution) << " | ";
};

nonogram_t gen_alg(const nonogram_t &nonogram, int iterations, bool show_time, bool show_convergence_curve,
                   bool show_solution, bool show_quality, bool show_iterations, bool show_function_calls,
                   int population_size, double crossover_probability, double mutation_probability,
                   nonogram_t &solution_nonogram) {

    auto start = std::chrono::high_resolution_clock::now();
    int calls = 0, found = 0, iter = 0;
    std::vector<nonogram_t> initial_population(population_size);
    std::generate(initial_population.begin(), initial_population.end(), [&]() {
        return generate_random_solution(nonogram);
    });
    std::vector<nonogram_t> population = initial_population;
    std::sort(population.begin(), population.end(), [&](auto a, auto b) {
        return fitness(a, solution_nonogram) < fitness(b, solution_nonogram);
    });
    auto best = population[0];
    if (show_convergence_curve) print_population(population, solution_nonogram);
    std::cout << std::endl;
    for (int n = 0; n < iterations; n++) {
        iter++;
        std::vector<double> fitnesses(population_size);
        std::transform(population.begin(), population.end(), fitnesses.begin(),
                       [&](auto e) { return fitness(e, solution_nonogram); });
        auto selected = selection(fitnesses);
        std::vector<nonogram_t> new_gen;
        for (int i = 0; i < (population_size - 1); i += 2) {
            std::uniform_real_distribution<double> realDistribution(0.0, 1.0);
            std::vector<nonogram_t> current_pair = {population.at(selected.at(i)), population.at(selected.at(i + 1))};
            if (realDistribution(ga_random) > crossover_probability) {
                current_pair = crossover(current_pair);
            }
            for (auto &e: current_pair) {
                if (realDistribution(ga_random) > mutation_probability) {
                    e = mutation(e);
                }
            }
            new_gen.push_back(current_pair.at(0));
            new_gen.push_back(current_pair.at(1));
        }
        population = new_gen;

        if (fitness(best, solution_nonogram) > fitness(population[0], solution_nonogram)) {
            calls = calls++;
            found = n;
            best = population[0];
        }
        if (show_convergence_curve) {
            auto time = std::chrono::high_resolution_clock::now();
            auto currentDuration = std::chrono::duration_cast<std::chrono::microseconds>(time - start);
            std::cout << "Step: " << n << " Time Passed: " << currentDuration.count() / 1e6 << " Population: ";
            print_population(population, solution_nonogram);
            std::cout << std::endl;
        }
        if (fitness(best, solution_nonogram) == 0) break;
    }

    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

    if (show_time) std::cout << "Time: " << duration.count() / 1e6 << " seconds." << std::endl;
    if (show_solution) std::cout << "Result:\n" << best;
    if (show_quality) std::cout << "Mistakes: " << fitness(best, solution_nonogram) << std::endl;
    if (show_iterations) std::cout << "Iterations made: " << iter << ". Earliest Best found at: " << found << std::endl;
    if (show_function_calls) std::cout << "Evaluation Function calls: " << calls << std::endl;

    return best;
}






