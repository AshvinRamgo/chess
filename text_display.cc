 #include "text_display.h"
Text_Display::Text_Display(const Board& b): board{b} {}
void Text_Display::render() {
    std::cout << WRAPPER;
    for (int i = 0; i < 10; i++) {
        std::cout << '-';
    }
    std::cout << '\n';
    for (int row = 8; row > 0; row--) {
        std::cout << '|';
        for (int column = 0; column < 8; column++) { 
            std::string pos = "";
            pos += ('a' + column);
            pos += ('0' + row);
            char piece = board.view(pos);
            if (piece == ' ') {
                if (((column % 2) + (row % 2)) % 2 == 0) {
                    piece = '#';
                } else {
                    piece = ' ';
                }
            }
            std::cout << piece;
        }
        std::cout << "|\n";
    }
    for (int i = 0; i < 10; i++) {
        std::cout << '-';
    }
    std::cout << '\n' << WRAPPER << '\n';
}

void Text_Display::score(int black, int white) {
    std::cout << WRAPPER << "Current Score: \n" << "Black: " << black << ", White: " << white << std::endl << WRAPPER << '\n';
}

void Text_Display::resign(char color) {
    if (color == 'w') {
        std::cout << WRAPPER << WHITE_RESIGN << WRAPPER << '\n';
    } else {
        std::cout << WRAPPER << BLACK_RESIGN << WRAPPER << '\n';
    }
}
void Text_Display::checkmate(char color) {
    if (color == 'w') {
        std::cout << WRAPPER << WHITE_CHECKMATE << WRAPPER << '\n';
    } else {
        std::cout << WRAPPER << BLACK_CHECKMATE << WRAPPER << '\n';
    }
}

void Text_Display::stalemate() {
    std::cout << WRAPPER << STALEMATE << WRAPPER << '\n';
}

