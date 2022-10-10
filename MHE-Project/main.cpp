/**                             Nonogram Example
 *                  2 2 4 4                             2 2 4 4
 *            0 9 9 2 3 2 2 1 0                   0 9 9 2 3 2 2 1 0
 *          0| | | | | | | | | |                0| | | | | | | | | |   //0
 *          4| | | | | | | | | |                4| |█|█|█|█| | | | |   //1
 *          6| | | | | | | | | |                6| |█|█|█|█|█|█| | |   //2
 *        2 2| | | | | | | | | |              2 2| |█|█| | |█|█| | |   //3
 *        2 2| | | | | | | | | |              2 2| |█|█| | |█|█| | |   //4
 *          6| | | | | | | | | |                6| |█|█|█|█|█|█| | |   //5
 *          4| | | | | | | | | |                4| |█|█|█|█| | | | |   //6
 *        2 2| | | | | | | | | |              2 2| |█|█| |█|█| | | |   //7
 *        2 2| | | | | | | | | |              2 2| |█|█| | |█|█| | |   //8
 *        2 2| | | | | | | | | |              2 2| |█|█| | | |█|█| |   //9
 *          0| | | | | | | | | |                0| | | | | | | | | |   //10
 *
 */
#include <iostream>
#include <vector>
#include <string>

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
        return board.at(y * width + x);
    }
};


std::ostream &operator<<(std::ostream &output, const nonogram_t &nonogram) {
    output << "\t\t";
    for (int w = 0; w < nonogram.width; w++) {
        for (int ccs = 0; ccs < nonogram.column_clues[w].size(); ccs++) {
            output << nonogram.column_clues[w][ccs];
        }
        output << "\t";
    }
    output << std::endl;

    for (int h = 0; h < nonogram.height; h++) {
        for (int rcs = 0; rcs < nonogram.row_clues[h].size(); rcs++)
            output << nonogram.row_clues[h][rcs];
        output << "\t";
        for (int w = 0; w < nonogram.width + 1; w++) {
            auto &val = nonogram.board[h * nonogram.width + w];
            output << ((val > 0) ? "███" :
                       ((val < 1) ? "   " : "")) << "|";
        }
        output << std::endl;
    }
    return output;
}

int count_inconsistent(nonogram_t &nonogram) {
    bool first_seen = false;
    //for ( int y = 0; y < nonogram.width){
    //
    //};
}

double evaluate(const nonogram_t &nonogram) {

}

nonogram_t nonogram = {
        9,
        11,
        {{0}, {9}, {9}, {2, 2}, {2, 3}, {4, 2},
         {4, 2}, {1}, {0}},
        {{0}, {4}, {6}, {2, 2}, {2, 2}, {6}, {4},
         {2, 2}, {2, 2}, {2, 2}, {0}},
        {
                0, 0, 0, 0, 0, 0, 0, 0, 0, 0,   //0
                0, 0, 0, 0, 0, 0, 0, 0, 0, //1
                0, 0, 0, 0, 0, 0, 0, 0, 0, //2
                0, 0, 0, 0, 0, 0, 0, 0, 0, //3
                0, 0, 0, 0, 0, 0, 0, 0, 0, //4
                0, 0, 0, 0, 0, 0, 0, 0, 0, //5
                0, 0, 0, 0, 0, 0, 0, 0, 0, //6
                0, 0, 0, 0, 0, 0, 0, 0, 0, //7
                0, 0, 0, 0, 0, 0, 0, 0, 0, //8
                0, 0, 0, 0, 0, 0, 0, 0, 0, //9
                0, 0, 0, 0, 0, 0, 0, 0, 0  //10
        }

};

nonogram_t nonogram_solution = {
        9,
        11,
        {{0}, {9}, {9}, {2, 2}, {2, 3}, {4, 2},
         {4, 2}, {1}, {0}},
        {{0}, {4}, {6}, {2, 2}, {2, 2}, {6},
         {4}, {2, 2}, {2, 2}, {2, 2}, {0}},
        {
                0, 0, 0, 0, 0, 0, 0, 0, 0, 0,   //0
                0, 1, 1, 1, 1, 0, 0, 0, 0, //1
                0, 1, 1, 1, 1, 1, 1, 0, 0, //2S
                0, 1, 1, 0, 0, 1, 1, 0, 0, //3
                0, 1, 1, 0, 0, 1, 1, 0, 0, //4
                0, 1, 1, 1, 1, 1, 1, 0, 0, //5
                0, 1, 1, 1, 1, 0, 0, 0, 0, //6
                0, 1, 1, 0, 1, 1, 0, 0, 0, //7
                0, 1, 1, 0, 0, 1, 1, 0, 0, //8
                0, 1, 1, 0, 0, 0, 1, 1, 0, //9
                0, 0, 0, 0, 0, 0, 0, 0, 0  //10
        }

};

int main() {
    std::cout << "Example of a NonogramPuzzle" << std::endl;
    std::cout << nonogram << std::endl;

    std::cout << "Solved NonogramPuzzle" << std::endl;
    std::cout << nonogram_solution;

    return 0;
}