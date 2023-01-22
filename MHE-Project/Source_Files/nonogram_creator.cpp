#include "../Header_Files/nonogram_help_functions.h"

using json = nlohmann::json;

void nonogramCreator(int width, int height){


    std::random_device rd23;
    std::mt19937 randomizer2(rd23());

    std::vector<std::vector<int>> column_clues;
    std::vector<std::vector<int>> row_clues;

    std::vector<int> board;
    std::vector<int> solution_board;

    for (int n = 0; n < height; n++){
        for(int m = 0; m < width; m++) {
            int generated_random;
            std::uniform_int_distribution<int> intDistribution(0, 1);
            generated_random = intDistribution(randomizer2);
            board.push_back(0);
            solution_board.push_back(generated_random);
        }
    }

    for (int y = 0; y < height; y++) {
        std::vector<int> set = {};
        int filled_squares = 0;
        for (int x = 0; x < width; x++) {
            if ((solution_board[(y*width+x)]) == 1)
                filled_squares++;
            if ((solution_board[(y*width+x)] == 0 || x == width - 1) && (filled_squares != 0)) {
                set.push_back(filled_squares);
                filled_squares = 0;
            }
        }
        if (set.empty()) set.push_back(0);
        row_clues.push_back(set);
    }

    //column works
    for (int x = 0; x < width; x++) {
        std::vector<int> set = {};
        int filled_squares = 0;
        for (int y = x; y <= solution_board.size(); y += width) {
            if (solution_board[y] == 1)
                filled_squares++;
            if ((solution_board[y] == 0 || y == (width * (height - 1)) + x) && (filled_squares != 0)) {
                set.push_back(filled_squares);
                filled_squares = 0;
            }
        }
        if (set.empty()) set.push_back(0);
        column_clues.push_back(set);
    }

    json j_object = {{"w", width},
                     {"h", height},
                     {"column_clues", column_clues},
                     {"row_clues", row_clues},
                     {"board", board},
                     {"solution_board",solution_board}
    };

    std::cout << j_object.dump(1, '\t');
}

