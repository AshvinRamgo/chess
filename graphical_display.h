#include "board.h"
#include "window.h"

class Graphical_Display {
    const int PIECE_OFFSET = 40; //amount of pixels from the top left of the square when drawing pieces
    const int COVER[4] = {200, 350, 400, 100}; //parameters when calling w.drawRectangle for the white cover
    const int MESSAGE[2] = {300, 395}; //parameters of the message position
    const std::string WHITE_RESIGN = "Black wins! By Resignation";
    const std::string BLACK_RESIGN = "White wins! By Resignation";
    const std::string WHITE_CHECKMATE = "White wins! By Checkmate";
    const std::string BLACK_CHECKMATE = "Black wins! By Checkmate";
    const std::string STALEMATE = "Game tied! By Stalemate";
    const Board& board;
    Xwindow w {800, 800};
    public:
        void render_square(int r, int c);
        Graphical_Display(const Board& b);
        void draw_board();
        void render(int r1, int c1, int r2, int c2);
        void score(int black, int white);
        void resign(char color);
        void checkmate(char color);
        void stalemate();
};

