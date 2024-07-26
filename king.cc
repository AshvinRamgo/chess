// King.cc
#include "king.h"
#include "rook.h" // Include the Rook header file to access the hasMoved method
#include "board.h"

King::King(char color, const Board& b) : Piece(color, 'K', b), moved(false) {}

bool King::move(std::string position, std::string destination) {
    // Convert the current position and destination to coordinates
    int x1 = position[0] - 'a';
    int y1 = '8' - position[1];
    int x2 = destination[0] - 'a';
    int y2 = '8' - destination[1];

    // Check if the move is to an adjacent square
    if (abs(x1 - x2) <= 1 && abs(y1 - y2) <= 1) {
        // position = destination;
        moved = true;
        return true;
    }
    /*
    // Check for castling move
    if (!moved && y1 == y2 && (x2 == x1 + 2 || x2 == x1 - 2)) {
        // Check if the path is clear and the rook has not moved
        // Assuming rook is an instance of the Rook class
        /* Rook* rook = getRook(x2 > x1 ? 'h' : 'a');
        if (board.isPathClear(x1, y1, x2, y2) && rook && !rook->hasMoved()) {
            position = destination;
            moved = true;
            return true;
        } 
        return false;
    } 
    */
    // If the move is not to an adjacent square or a valid castling move, the move is invalid
    return false;
}


bool King::hasMoved() {
    return moved;
}

