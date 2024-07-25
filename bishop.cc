// Bishop.cc
#include "bishop.h"
#include "board.h"

Bishop::Bishop(char color, const Board& b) : Piece(color, 'B', b) {}

bool Bishop::move(std::string position, std::string destination) {
    // Convert the current position and destination to coordinates
    int x1 = position[0] - 'a';
    int y1 = '8' - position[1];
    int x2 = destination[0] - 'a';
    int y2 = '8' - destination[1];

    // Check if the move is diagonal
    if (abs(x2 - x1) == abs(y2 - y1)) {
        // Check if the path is clear 
        if (board.isPathClear(x1, y1, x2, y2)) {
            //position = destination;
            return true;
        } 
    }

    // If the move is not diagonal or the path is blocked, the move is invalid
    return false;
}
