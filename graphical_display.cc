#include "graphical_display.h"

Graphical_Display::Graphical_Display(const Board& b): board{b} {
    draw_board();
}

void Graphical_Display::draw_board() {
    w.fillRectangle(0, 0, 800, 800);
    for (int r = 8; r > 0; r--) {
        for (int c = 1; c < 9; c++) {
            render_square(r, c);
        }
    }
}

void Graphical_Display::render_square(int r, int c) {
    std::string pos = "";
    pos += ('a' - 1 + c);
    pos += ('0' + r);
    char piece = board.view(pos);
    if (((c % 2) + (r % 2)) % 2 == 0) {
        w.fillRectangle((c - 1) * 100, (8 - r) * 100, 100, 100, Xwindow::Black);
    } else {
        w.fillRectangle((c - 1) * 100, (8 - r) * 100, 100, 100, Xwindow::White);
    }
    int R, G, B;
switch (piece) {
    case 'P':
        R = 224; G = 224; B = 224;
        break;
    case 'p':
        R = 96; G = 96; B = 96;
        break;
    case 'N':
        R = 255; G = 204; B = 153;
        break;
    case 'n':
        R = 204; G = 102; B = 0;
        break;
    case 'B':
        R = 153; G = 204; B = 255;
        break;
    case 'b':
        R = 0; G = 0; B = 204;
        break;
    case 'R':
        R = 255; G = 153; B = 153;
        break;
    case 'r':
        R = 204; G = 0; B = 0;
        break;
    case 'Q':
        R = 204; G = 153; B = 255;
        break;
    case 'q':
        R = 102; G = 0; B = 204;
        break;
    case 'K':
        R = 255; G = 255; B = 153;
        break;
    case 'k':
        R = 204; G = 204; B = 0;
        break;
    default:
        R = -1; G = -1; B = -1;
        break;
}
if (R != -1) {
    w.fillRectangle((c - 1) * 100 + 25, (8 - r) * 100 + 25, 50, 50, R, G, B);
}

}

void Graphical_Display::render(int r1, int c1, int r2, int c2) {
    render_square(r1, c1);
    render_square(r2, c2);
}

void Graphical_Display::score(int black, int white) {
    w.fillRectangle(COVER[0], COVER[1], COVER[2], COVER[3], Xwindow::White);
    std::string message = "Current Score: White: ";
    message += std::to_string(white);
    message += " ,Black: ";
    message += std::to_string(black);
    w.drawString(MESSAGE[0], MESSAGE[1], message);
}

void Graphical_Display::resign(char color) {
    w.fillRectangle(COVER[0], COVER[1], COVER[2], COVER[3], Xwindow::White);
    if (color == 'w') {
        w.drawString(MESSAGE[0], MESSAGE[1], WHITE_RESIGN);
    } else {
        w.drawString(MESSAGE[0], MESSAGE[1], BLACK_RESIGN);
    }
}

void Graphical_Display::checkmate(char color) {
    w.fillRectangle(COVER[0], COVER[1], COVER[2], COVER[3], Xwindow::White);
    if (color == 'w') {
        w.drawString(MESSAGE[0], MESSAGE[1], WHITE_CHECKMATE);
    } else {
        w.drawString(MESSAGE[0], MESSAGE[1], BLACK_CHECKMATE);
    }
}

void Graphical_Display::stalemate() {
    w.fillRectangle(COVER[0], COVER[1], COVER[2], COVER[3], Xwindow::White);
    w.drawString(MESSAGE[0], MESSAGE[1], STALEMATE);
}