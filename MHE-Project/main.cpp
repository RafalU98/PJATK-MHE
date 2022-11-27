#include <iostream>
#include <fstream>
#include "json.hpp"
#include <vector>
#include <string>
#include <random>
#include <chrono>
#include <list>
#include <functional>

struct nonogram_t {
    int width;
    int height;
    std::vector<std::vector<int>> column_clues;
    std::vector<std::vector<int>> row_clues;
    std::vector<int> board;

    int &get(const int x, const int y) {
        return board[y * width + x];
    }

    int get(const int x, const int y) const {
        if ((x < 0) || (x >= width) || (y < 0) || (y >= height)) throw std::invalid_argument("out of board");
        return board.at(y * width + x);
    }
};

std::ostream &operator<<(std::ostream &output, const nonogram_t &nonogram) {
    output << "\t";
    for (int w = 0; w < nonogram.width; w++) {
        for (int ccs = 0; ccs < nonogram.column_clues[w].size(); ccs++) {
            if (ccs < nonogram.column_clues[w].size() - 1)
                output << nonogram.column_clues[w][ccs] << " ";
            else
                output << nonogram.column_clues[w][ccs];
        }
        output << "\t";
    }
    output << std::endl;

    for (int h = 0; h < nonogram.height; h++) {
        for (int rcs = 0; rcs < nonogram.row_clues[h].size(); rcs++)
            if (rcs < (nonogram.row_clues[h].size() - 1))
                output << nonogram.row_clues[h][rcs] << " ";
            else
                output << nonogram.row_clues[h][rcs] << "\t";
        for (int w = 0; w < nonogram.width; w++) {
            auto &value = nonogram.board[h * nonogram.width + w];
            output << ((value == 1) ? "███████" :
                       ((value == 0) ? "       " : "")) << "|";
        }
        output << std::endl;
    }
    return output;
}

/* The function is iterating first through the elements in rows and then through the elements in columns at the board
 * to check if submitted answer == solution, the returned number describes the value of "Wrong rows + Wrong columns"
 *
 *  adds 1 if element != NONE and pushes the value to current set when it comes across NONE or row/column ends.
 *  check if number set[x] == solution set[x], if not adds 1 to mistakes
 */
int count_inconsistent(const nonogram_t &nonogram) {
    int mistakes = 0;

    //Count wrong submitted Rows
    for (int y = 0; y < nonogram.height; y++) {
        std::vector<int> set = {};
        int filled_squares = 0;
        for (int x = 0; x < nonogram.width; x++) {
            if (nonogram.get(x, y) == 1)
                filled_squares++;
            if ((nonogram.get(x, y) == 0 || x == nonogram.width - 1) && (filled_squares != 0)) {
                set.push_back(filled_squares);
                filled_squares = 0;
            }
        }
        if (set.empty()) set.push_back(0);
        if (set != nonogram.row_clues[y]) mistakes++;
    }

    //Count wrong submitted Columns
    for (int x = 0; x < nonogram.width; x++) {
        std::vector<int> set = {};
        int filled_squares = 0;
        for (int y = x; y <= nonogram.board.size(); y += nonogram.width) {
            if (nonogram.board[y] == 1)
                filled_squares++;
            if ((nonogram.board[y] == 0 || y == (nonogram.width * (nonogram.height - 1)) + x) &&
                (filled_squares != 0)) {
                set.push_back(filled_squares);
                filled_squares = 0;
            }
        }
        if (set.empty()) set.push_back(0);
        if (set != nonogram.column_clues[x]) mistakes++;
    }

    return mistakes;
}

double evaluate(const nonogram_t &nonogram) {
    return count_inconsistent(nonogram);
}

bool next_solution(nonogram_t &nonogram) {
    int i = 0;
    for (; i < nonogram.board.size(); i++) {
        if (nonogram.board[i] == 0) {
            nonogram.board[i] = 1;
            break;
        } else
            nonogram.board[i] = 0;
    }
    return (i != nonogram.board.size());
}

nonogram_t generate_random_solution(const nonogram_t &nonogram) {
    static std::random_device rd;
    static std::mt19937 rand(rd());
    std::uniform_int_distribution<int> distribution(0, 1);
    nonogram_t random_solution = nonogram;
    for (int i = 0; i < nonogram.board.size(); i++) {
        if (nonogram.board[i] <= 0) {
            random_solution.board[i] = distribution(rand);
        }
    }
    return random_solution;
}

std::vector<nonogram_t> generate_neighbours(const nonogram_t &nonogram) {
    std::vector<nonogram_t> neighbours;
    for (int i = 0; i < nonogram.board.size(); i++) {
        if (nonogram.board[i] <= 0) {
            auto new_board = nonogram;
            new_board.board[i] = 1 - new_board.board[i];
            neighbours.push_back(new_board);
        }
    }
    return neighbours;
}

nonogram_t generate_neighbour(const nonogram_t &nonogram) {
    auto neighbour = nonogram;
    static std::random_device rd;
    static std::mt19937 rand(rd());
    std::uniform_int_distribution<int> distribution(0, nonogram.board.size() - 1);
    auto random_spot = distribution(rand);
    if (neighbour.board[random_spot] == 0) neighbour.board[random_spot] = 1;
    return neighbour;
}

nonogram_t generate_best_neighbour(const nonogram_t &nonogram) {
    auto best_neighbour = nonogram;
    for (const auto &neighbour: generate_neighbours(nonogram)) {
        if (evaluate(neighbour) <= evaluate(best_neighbour))
            best_neighbour = neighbour;
    }
    return best_neighbour;
}

bool operator==(nonogram_t left, nonogram_t right) {
    if ((left.width != right.width) || left.height != right.height) return false;
    for (unsigned n = 0; n < right.board.size(); n++) {
        if (left.board.at(n) != right.board.at(n)) return false;
    }
    return true;
}

nonogram_t tabu_method(const nonogram_t &nonogram, int iterations, int tabu_size) {
    std::list<nonogram_t> tabu_list;
    //tabu_list.push_back(generate_random_solution(nonogram));
    tabu_list.push_back(nonogram);
    auto result_tabu = tabu_list.back();
    for (int n = 0; n < iterations; n++) {
        if (evaluate(tabu_list.back()) == 0) {
            std::cout << "Tabu Method found the solution at iteration:" << n << std::endl
                      << result_tabu << "List Size: " << tabu_list.size() << std::endl;
            return result_tabu;
        }
        std::vector<nonogram_t> neighbours;
        for (const auto &element: generate_neighbours(tabu_list.back())) {
            bool found = (std::find(tabu_list.begin(), tabu_list.end(), element) != tabu_list.end());
            if (!found) neighbours.push_back(element);
        }
        if (neighbours.empty()) {
            std::cerr << "Method got stuck at iteration: " << n << "\nBest Solution was: " <<
                      evaluate(result_tabu) << "\n" << result_tabu << "List Size: " << tabu_list.size() << std::endl;
        }
        tabu_list.push_back(*std::min_element(neighbours.begin(), neighbours.end(),
                                              [](auto left, auto right) {
                                                  return evaluate(left) < evaluate(right);
                                              }));
        if (evaluate(tabu_list.back()) <= evaluate(result_tabu)) {
            result_tabu = tabu_list.back();
        }
        if (tabu_list.size() > tabu_size) tabu_list.pop_front();
    }
    return result_tabu;
}

nonogram_t hill_climb_deterministic(const nonogram_t &nonogram, int iterations) {
    //auto deterministic_result = generate_random_solution(nonogram);
    //std::cout << "Random Solution." << " Mistakes: " << evaluate(deterministic_result) << std::endl;
    //std::cout << deterministic_result;
    auto deterministic_result = nonogram;
    for (int n = 0; n < iterations; n++) {
        auto newResult = generate_best_neighbour(deterministic_result);
        if (evaluate(newResult) == evaluate(deterministic_result)) {
            std::cout << "\nSolution after algorithm" << " Mistakes: " << evaluate(deterministic_result) <<
                      ". Iterations: " << n << std::endl;
            std::cout << deterministic_result;
            return deterministic_result;
        }
        deterministic_result = newResult;
    }
    return deterministic_result;
}

nonogram_t hill_climb(const nonogram_t &nonogram, int iterations) {
    //auto result = generate_random_solution(nonogram);
    //std::cout << "Random Solution." << " Mistakes: " << evaluate(result) << std::endl;
    //std::cout << result;
    auto result = nonogram;
    for (int i = 0; i < iterations; i++) {
        auto newResult = generate_neighbour(result);
        if (evaluate(newResult) <= evaluate(result))
            result = newResult;
    }
    std::cout << "\nSolution after algorithm" << " Mistakes: " << evaluate(result) << std::endl;
    std::cout << result;
    return result;
}

void brute_force(nonogram_t nonogram, int iterations) {
    auto start = std::chrono::high_resolution_clock::now();
    auto best = nonogram;
    for (int n = 0; n < iterations; n++) {
        next_solution(nonogram);
        if (evaluate(nonogram) < evaluate(best)) best = nonogram;
        if (evaluate(nonogram) == 0) {
            auto stop = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
            std::cout << "Brute-Force found the right solution in " << n + 1 << " tries." << std::endl;
            std::cout << "Brute-Force needed " << duration.count() / 1e6 << " seconds." << std::endl;
            std::cout << nonogram << std::endl;
            break;
        }
    }
    std::cout << "Best solution (with given iterations) was with mistakes: " << evaluate(best) << std::endl;
    std::cout << best << std::endl;
}

void random_solution(const nonogram_t &nonogram, int iterations) {
    auto start = std::chrono::high_resolution_clock::now();
    auto best = generate_random_solution(nonogram);
    for (int n = 0; n < iterations; n++) {
        auto rand = generate_random_solution(nonogram);
        if (evaluate(rand) < evaluate(best)) best = rand;
        if (evaluate(rand) == 0) {
            auto stop = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
            std::cout << "Random_Solution found the right solution in " << n + 1 << " tries." << std::endl;
            std::cout << "Random solution generator needed " << duration.count() / 1e6 << " seconds." << std::endl;
            std::cout << rand << std::endl;
            break;
        }
    }
    std::cout << "Best solution (with given iterations) was with mistakes: " << evaluate(best) << std::endl;
    std::cout << best << std::endl;
}

void task1(int h, int w, const std::string &text) {
    if (text.length() <= w - 2) {
        for (int x = 0; x < h; x++) {
            if (x == 0 || x == h - 1) {
                for (int i = 0; i < w; i++)
                    std::cout << "█";
                std::cout << std::endl;
            } else if (x == (h / 2)) {
                std::cout << "█";
                for (int j = 0; j < ((w - text.size()) / 2) - 1; j++)
                    std::cout << ' ';
                std::cout << text;
                for (int j = ((w - text.size()) / 2) + text.size() + 1; j < w; j++)
                    std::cout << ' ';
                std::cout << "█" << std::endl;
            } else {
                std::cout << "█";
                for (int k = 1; k < w - 1; k++)
                    std::cout << " ";
                std::cout << "█" << std::endl;
            }
        }
    } else
        std::cout << "text is too big for the box" << std::endl;
}

int main(int argc, char **argv) {
    std::cout << "Welcome\n"
                 "To start the Program enter following:\n"
                 "1ST ARGUMENT = Function (b -> BruteForce, r -> Random-Solution, "
                 "hd -> Hill Climb Deterministic, hr -> Hill Climb Randomized, tabu -> Tabu method\n"
                 "Or if you want all functions: all -> all algorithms\n"
                 "2ND ARGUMENT = Iterations as an Integer\n"
                 "3RD ARGUMENT = nonogram.json (Edit with your own Nonogram)\n"
                 "You can also choose a sample: nonogram*.json, where * is a number from 1 to 3\n"
                 "4TH ARGUMENT = list of tabu size" << std::endl;

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
    int tabu_size = atoi(argv[4]);
    std::ifstream file(file_name);
    nlohmann::json data = nlohmann::json::parse(file);

    nonogram_t nonogram = {
            data["w"],
            data["h"],
            data["column_clues"],
            data["row_clues"],
            data["board"]
    };

    std::cout << "\n Nonogram to solve" << std::endl;
    std::cout << nonogram << std::endl;

    if (function == "b" || function == "all") {
        std::cout << " ------------------------------" << std::endl;
        std::cout << "Brute_Force Algorithm" << std::endl;
        brute_force(nonogram, iterations);

    }

    if (function == "r" || function == "all") {
        std::cout << " ------------------------------" << std::endl;
        std::cout << "Random-Solution Algorithm" << std::endl;
        random_solution(nonogram, iterations);
    }

    if (function == "hd" || function == "all") {
        std::cout << " ------------------------------" << std::endl;
        std::cout << "Hill Climb deterministic" << std::endl;
        hill_climb_deterministic(nonogram, iterations);
    }

    if (function == "hr" || function == "all") {
        std::cout << " ------------------------------" << std::endl;
        std::cout << "Hill Climb randomized" << std::endl;
        hill_climb(nonogram, iterations);
    }

    if (function == "tabu" || function == "all") {
        std::cout << " ----------------------  --------" << std::endl;
        std::cout << "Tabu Method" << std::endl;
        tabu_method(nonogram, iterations, tabu_size);
    }
    return 0;
}