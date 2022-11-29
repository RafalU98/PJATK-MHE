#ifndef MHE_PROJECT_NONOGRAM_FUNCTIONS_H
#define MHE_PROJECT_NONOGRAM_FUNCTIONS_H

#include <iostream>
#include <fstream>
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

using nonogram_t = nonogram_t;

std::ostream &operator<<(std::ostream &output, const nonogram_t &nonogram);


#endif //MHE_PROJECT_NONOGRAM_FUNCTIONS_H
