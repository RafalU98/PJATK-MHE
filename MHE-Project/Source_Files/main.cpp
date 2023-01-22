#include "../Header_Files/libraries.h"

int main(int argc, char **argv) {
    //std::cout << "Welcome\n"
                 "To start the Program enter following:\n"
                 "1ST ARGUMENT = Function (b -> BruteForce, r -> Random-Solution, "
                 "hd -> Hill Climb Deterministic, hr -> Hill Climb Randomized, tabu -> Tabu method, sim -> Simulated Annealing\n"
                 "Or if you want all functions: all -> all algorithms\n"
                 "2ND ARGUMENT = Iterations as an Integer\n"
                 "3RD ARGUMENT = nonogram.json (Edit with your own Nonogram)\n"
                 "You can also choose a sample: nonogram*.json, where * is a number from 1 to 3\n"
                 "4TH ARGUMENT = list of tabu size\n"
                 "5TH ARGUMENT = 1 if you want too see the time, that the function needed. 0 if not\n"
                 "6TH ARGUMENT = 1 if you want too see the convergence curve of the function. 0 if not\n"
                 "7TH ARGUMENT = 1 if you want too see the solution of the function. 0 if not\n"
                 "8TH ARGUMENT = 1 if you want too see the quality or mistakes of the result. 0 if not\n"
                 "9TH ARGUMENT = 1 if you want too see the total iterations of the function. 0 if not\n"
                 "10TH ARGUMENT = 1 if you want too see how many times the quality got better. 0 if not\n"
                 "11TH ARGUMENT = 1 if you want too see the solution nonogram. . 0 if not\n";

    if (std::string(argv[1]) == "Samples/task1.json") {
        std::ifstream file(argv[1]);
        nlohmann::json data = nlohmann::json::parse(file);
        std::string text = data["text"];
        int h = data["h"];
        int w = data["w"];
        task1(h, w, text);
        return 0;
    }

    std::string function = argv[1];
    int iterations = atoi(argv[2]);

    std::string file_name = argv[3];
    std::ifstream file(file_name);
    nlohmann::json data = nlohmann::json::parse(file);

    int tabu_size = atoi(argv[4]);

    int show_time = atoi(argv[5]);
    int show_convergence_curve = atoi(argv[6]);
    int show_solution = atoi(argv[7]);
    int show_quality = atoi(argv[8]);
    int show_iterations = atoi(argv[9]);
    int show_function_calls = atoi(argv[10]);
    int solution_nonogram = atoi(argv[11]);
    int width_random = atoi(argv[12]);
    int height_random = atoi(argv[13]);

    nonogram_t nonogram = {
            data["w"],
            data["h"],
            data["column_clues"],
            data["row_clues"],
            data["board"]
    };

    nonogram_t nonogramSolution = {
            data["w"],
            data["h"],
            data["column_clues"],
            data["row_clues"],
            data["solution_board"]
    };

    //std::cout << "\n Nonogram to solve" << std::endl;
    //std::cout << nonogram << std::endl;

    if (function == "b" || function == "all") {
        std::cout << " ------------------------------" << std::endl;
        std::cout << "Brute_Force Algorithm" << std::endl;
        brute_force(nonogram, iterations, show_time, show_convergence_curve, show_solution, show_quality,
                    show_iterations, show_function_calls);
    }

    if (function == "r" || function == "all") {
        std::cout << " ------------------------------" << std::endl;
        std::cout << "Random-Solution Algorithm" << std::endl;
        random_solution(nonogram, iterations, show_time, show_convergence_curve, show_solution, show_quality,
                        show_iterations, show_function_calls);
    }

    if (function == "hd" || function == "all") {
        std::cout << " ------------------------------" << std::endl;
        std::cout << "Hill Climb deterministic" << std::endl;
        hill_climb_det(nonogram, iterations, show_time, show_convergence_curve, show_solution, show_quality,
                       show_iterations, show_function_calls);
    }

    if (function == "hr" || function == "all") {
        std::cout << " ------------------------------" << std::endl;
        std::cout << "Hill Climb randomized" << std::endl;
        hill_climb(nonogram, iterations, show_time, show_convergence_curve, show_solution, show_quality,
                   show_iterations, show_function_calls);
    }

    if (function == "tabu" || function == "all") {
        std::cout << " ---------------------- --------" << std::endl;
        std::cout << "Tabu Method" << std::endl;
        tabu(nonogram, iterations, tabu_size, show_time, show_convergence_curve, show_solution, show_quality,
             show_iterations, show_function_calls);
    }

    if (function == "sim" || function == "all") {
        std::cout << " ---------------------- --------" << std::endl;
        std::cout << "Simulated annealing" << std::endl;
        sim_ann(nonogram, iterations, show_time, show_convergence_curve, show_solution, show_quality,
                show_iterations, show_function_calls);
    }

    if (function == "ga" || function == "all") {
        std::cout << " ---------------------- --------" << std::endl;
        std::cout << "Genetic Algorithm" << std::endl;

        int population_size = 100;
        double crossover_probability = 0.1;
        double mutation_probability = 0.01;
        gen_alg(nonogram, iterations, show_time, show_convergence_curve, show_solution, show_quality,
                show_iterations, show_function_calls, population_size, crossover_probability,
                mutation_probability);
    }

    if (function == "new") {
        nonogramCreator(width_random,height_random);
    }

    if (solution_nonogram == 1) {
        std::cout << "This was the Nonogram we were looking for:\n" << nonogramSolution;
    }


    return 0;
}