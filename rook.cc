// Rook.cc
#include "rook.h"

Rook::Rook(char color) : Piece(color, 'R'), moved(false) {}

bool Rook::move(std::string destination) {
    // Convert the current position and destination to coordinates
    int x1 = position[0] - 'a';
    int y1 = position[1] - '1';
    int x2 = destination[0] - 'a';
    int y2 = destination[1] - '1';

    // Check if the move is in a straight line
    if (x1 == x2 || y1 == y2) {
        // Check if the path is clear (this will need to be implemented)
        /* if (isPathClear(x1, y1, x2, y2)) {
            position = destination;
            moved = true;
            return true;
        } */
        return true;
    }

    // If the move is not in a straight line or the path is blocked, the move is invalid
    return false;
}

bool Rook::hasMoved() {
    return moved;
}

