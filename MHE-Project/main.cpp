#include <iostream>
#include <vector>
#include <string>
#include <random>
#include <chrono>

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
            output << ((value == 1) ? "███" :
                       ((value == 0) ? "   " : "")) << "|";
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

/*
nonogram_t generate_nonogram(int size) {
    nonogram_t nonogram;
    while(evaluate(nonogram) != 0)
        for (int i = 0; i < size*size; i++){
            std::cout << i;
        }
    return nonogram;
}
*/

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
            auto new_board = nonogram;
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
            //std::cout << new_board;
        }
    }
    return neighbours;
}

nonogram_t generate_neighbour(const nonogram_t &nonogram) {
    auto neighbour = nonogram;
    static std::random_device rd;
    static std::mt19937 rand(rd());
    std::uniform_int_distribution<int> distribution(0, nonogram.board.size()-1);
    auto random_spot = distribution(rand);
    if (neighbour.board[random_spot]== 0 ) neighbour.board[random_spot] = 1;
    return neighbour;
}

nonogram_t generate_best_neighbour(const nonogram_t &nonogram) {
    auto best_neighbour = nonogram;
    for (const auto &neighbour: generate_neighbours(nonogram)) {
        if (evaluate(best_neighbour) > evaluate(neighbour)){
            best_neighbour = neighbour;
        }
    }
    return best_neighbour;
}

nonogram_t hill_climb_deterministic (const nonogram_t& nonogram, int iterations) {
    auto deterministic_result = generate_random_solution(nonogram);
    std::cout << "Random Solution." << " Mistakes: " << evaluate(deterministic_result) << std::endl;
    std::cout << deterministic_result;
    while (true) {
        auto newResult = generate_best_neighbour(deterministic_result);
        if (evaluate(newResult) == evaluate(deterministic_result)){
            std::cout << "\nSolution after algorithm" << " Mistakes: " << evaluate(deterministic_result) << std::endl;
            std::cout << deterministic_result;
            return deterministic_result;
        }
        deterministic_result = newResult;
    }
}

nonogram_t hill_climb(const nonogram_t& nonogram, int iterations) {
    auto result = generate_random_solution(nonogram);
    std::cout << "Random Solution." << " Mistakes: " << evaluate(result) << std::endl;
    std::cout << result;
    for (int i = 0; i < iterations; i++) {
        auto newResult = generate_neighbour(result);
        if (evaluate(newResult) <= evaluate(result))
            result = newResult;
    }
    std::cout << "\nSolution after algorithm" << " Mistakes: " << evaluate(result) << std::endl;
    std::cout << result;
    return result;
}


void brute_force(nonogram_t nonogram) {
    auto start = std::chrono::high_resolution_clock::now();
    int n = 0;
    while (next_solution(nonogram)) {
        /*
        if ((n % 4096) == 0) {
            std::cout << "Wrong board at ";
            std::cout << n << " tries. Found " << evaluate(nonogram) << " mistakes in submitted Nonogram" << std::endl << nonogram << std::endl;
        }
         */
        if (evaluate(nonogram) == 0) {
            auto stop = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
            std::cout << "Brute-Force found the right solution in " << n + 1 << " tries." << std::endl;
            std::cout << "Brute-Force needed " << duration.count()/1e6 << " seconds." << std::endl;
            std::cout << nonogram << std::endl;
            break;
        }
        n++;
    }
};

void random_solution(const nonogram_t &nonogram) {
    auto start = std::chrono::high_resolution_clock::now();
    auto rand = generate_random_solution(nonogram);
    int n = 0;
    while (evaluate(rand) != 0) {
        /*
        if ((n % 4096) == 0) {
            std::cout << "Wrong board at " << n << " tries. Found " << std::endl;
            std::cout << evaluate(nonogram) << " mistakes in submitted Nonogram\n" << rand << std::endl;
        }
        */
        rand = generate_random_solution(nonogram);
        if (evaluate(rand) == 0) {
            auto stop = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
            std::cout << "Random_Solution found the right solution in " << n + 1 << " tries." << std::endl;
            std::cout << "Random solution generator needed " << duration.count()/1e6 << " seconds." << std::endl;
            std::cout << rand << std::endl;
            break;
        }
        n++;
    }
}

int main(int argc, char **argv) {

    nonogram_t nonogram1 = {
            5,
            5,
            {{1, 1, 1}, {0}, {0}, {0}, {0}},
            {{1}, {0}, {1}, {0}, {1}},
            {0, 0, 0, 0, 0,
             0, 0, 0, 0, 0,
             0, 0, 0, 0, 0,
             0, 0, 0, 0, 0,
             0, 0, 0, 0, 0}
    };
    nonogram_t nonogram2 = {
            4,
            4,
            {{4}, {1, 1}, {1, 1}, {4}},
            {{4}, {1, 1}, {1, 1}, {4}},
            {0, 0, 0, 0,
             0, 0, 0, 0,
             0, 0, 0, 0,
             0, 0, 0, 0}
    };

    nonogram_t nonogram3 = {
            3,
            3,
            {{1}, {0}, {1,1}},
            {{1,1}, {0}, {1}},
            {0, 0, 0,
             0, 0, 0,
             0, 0, 0}
    };

    //generate_nonogram(3);

    const auto &nonogram = nonogram3;
    int iterations = 500;

    std::cout << "\n Nonogram to solve" << std::endl;
    std::cout << nonogram << std::endl;

    std::cout << " ------------------------------" << std::endl;
    std::cout << "Solving with Brute_Force Algorithm" << std::endl;
    brute_force(nonogram);

    std::cout << " ------------------------------" << std::endl;
    std::cout << "Solving with Random-Solution Algorithm" << std::endl;
    random_solution(nonogram);

    std::cout << " ------------------------------" << std::endl;
    std::cout << "Hill Climb deterministic" << std::endl;
    hill_climb_deterministic(nonogram,iterations);

    std::cout << " ------------------------------" << std::endl;
    std::cout << "Hill Climb standard" << std::endl;
    hill_climb(nonogram,iterations);

    return 0;
}