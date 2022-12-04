#include "../Header_Files/nonogram_help_functions.h"
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

nonogram_t generate_neighbour_almost_normal(const nonogram_t &nonogram) {
    static std::random_device rd;
    static std::mt19937 rand(rd());
    std::vector<nonogram_t> neighbours;
    std::normal_distribution normalDistribution;
    std::uniform_int_distribution<int> intDistribution(0,nonogram.board.size()-1);
    double how_may_change = normalDistribution(rand);
    auto new_board = nonogram;
    for (int i = 0; i < how_may_change; i++) {
        int n = intDistribution(rand);
        if ( new_board.board[n] <= 0 ) new_board.board[n] = 1 - new_board.board[n];
    }
    return new_board;
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
    for (unsigned n = 0; n < right.board.size(); n++)
        if (left.board.at(n) != right.board.at(n)) return false;
    return true;
}