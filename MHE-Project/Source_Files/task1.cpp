#include "../Header_Files/task1.h"

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