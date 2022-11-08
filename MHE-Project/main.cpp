#include <iostream>
#include <vector>
#include <string>
#include <random>

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
            if (nonogram.get(x,y) == 1)
                filled_squares++;
            if ((nonogram.get(x,y) == 0 || x == nonogram.width - 1) && (filled_squares != 0)) {
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
            if (nonogram.board[y]== 1)
                filled_squares++;
            if ((nonogram.board[y] == 0 || y == (nonogram.width * (nonogram.height - 1)) + x) && (filled_squares  != 0)){
                set.push_back(filled_squares);
                filled_squares  = 0;
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

void brute_force(nonogram_t nonogram) {
    int n = 0;
    while (next_solution(nonogram)) {
        /*
        if ((n % 4096) == 0) {
            std::cout << "Wrong board at ";
            std::cout << n << " tries. Found " << evaluate(nonogram) << " mistakes in submitted Nonogram" << std::endl << nonogram << std::endl;
        }
         */
        if (evaluate(nonogram) == 0) {
            std::cout << "Brute-Force found the right solution in " << n+1 << " tries." << std::endl;
            std::cout << nonogram << std::endl;
            break;
        }
        n++;
    }
};


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

nonogram_t generate_random_solution(const nonogram_t &nonogram) {
    using namespace  std;
    static random_device rd;
    static mt19937 rand(rd());
    uniform_int_distribution<int> distribution(0,1);
    nonogram_t rand_sol = nonogram;
    for (int i = 0; i < nonogram.board.size(); i++) {
        if (nonogram.board[i] <= 0) {
            auto new_board = nonogram;
            rand_sol.board[i] = distribution(rand);
        }
    }
    return rand_sol;
}

std::vector<nonogram_t> random_board(const nonogram_t &nonogram) {
    std::random_device random;
    std::mt19937 gen(rand());
    std::uniform_int_distribution<int> distribution(0,1);

    for(int i = 0; i < nonogram.board.size(); i++) {
        //  nonogram.board[i] = distribution(gen);
    }
    //return;
}

nonogram_t hill_climb_det(nonogram_t nonogram, int iterations) {

}

nonogram_t hill_climb(nonogram_t nonogram, int iterations) {

}

int main(int argc, char** argv) {

    nonogram_t nonogram1 = {
            5,
            5,
            {{1,1,1}, {0}, {0}, {0}, {0}},
            {{1}, {0}, {1}, {0},{1}},
            {0, 0, 0, 0,0,
             0, 0, 0, 0,0,
             0, 0, 0, 0,0,
             0, 0, 0, 0,0,
             0,0,0,0,0}
    };
    nonogram_t nonogram2 = {
            4,
            4,
            {{4}, {1,1}, {1, 1}, {4}},
            {{4}, {1, 1}, {1, 1}, {4}},
            {0, 0, 0, 0,
             0, 0, 0, 0,
             0, 0, 0, 0,
             0, 0, 0, 0}
    };

    auto nonogram = nonogram2;

    std::cout << "\n Nonogram to solve" << std::endl;
    std::cout << nonogram << std::endl;

    for (auto neighbour : generate_neighbours(nonogram)) {
        std::cout << " ------------------------------" << std::endl;
        std::cout << neighbour << std::endl;
    }
    std::cout << " ------------------------------" << std::endl;
    std::cout << generate_random_solution(nonogram) << std::endl;

    std::cout << " ------------------------------" << std::endl;
    std::cout << "Solving with Brute_Force Algorithm" << std::endl;
    brute_force(nonogram);
    //random_board();




    return 0;
}