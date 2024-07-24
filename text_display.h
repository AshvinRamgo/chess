#include "board.h"
#include <iostream>
class Text_Display {
    const Board& board;
    const std::string WRAPPER = "----------------------------------------\n";
    const std::string WHITE_RESIGN = "Black wins! By Resignation\n";
    const std::string BLACK_RESIGN = "White wins! By Resignation\n";
    const std::string WHITE_CHECKMATE = "White wins! By Checkmate\n";
    const std::string BLACK_CHECKMATE = "Black wins! By Checkmate\n";
    const std::string STALEMATE = "Game tied! By Stalemate\n";
    public:
        Text_Display(const Board& b);
        void render();
        void score(int black, int white);
        void resign(char color);
        void checkmate(char color);
        void stalemate();

};
