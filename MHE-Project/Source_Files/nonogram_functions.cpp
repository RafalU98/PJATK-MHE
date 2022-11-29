#include "../Header_Files/nonogram_functions.h"

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