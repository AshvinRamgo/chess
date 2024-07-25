// Bishop.cc
#include "bishop.h"

Bishop::Bishop(char color) : Piece(color, 'B') {}

bool Bishop::move(std::string destination) {
    // Convert the current position and destination to coordinates
    int x1 = position[0] - 'a';
    int y1 = position[1] - '1';
    int x2 = destination[0] - 'a';
    int y2 = destination[1] - '1';

    // Check if the move is diagonal
    if (abs(x2 - x1) == abs(y2 - y1)) {
        // Check if the path is clear (this will need to be implemented)
        /*if (isPathClear(x1, y1, x2, y2)) {
            position = destination;
            return true;
        } */
        // NOT IMPLEMENTED, DOES ILLEGAL MOVES
        return true;
    }

    // If the move is not diagonal or the path is blocked, the move is invalid
    return false;
}
