// Knight.cc
#include "knight.h"
#include "board.h"
#include <cmath>

Knight::Knight(char color, const Board& b) : Piece(color, 'N', b) {}

bool Knight::move(std::string position, std::string destination) {
    int dx = abs(destination[0] - position[0]);
    int dy = abs(destination[1] - position[1]);

    // Check if the move is legal for a knight
    if ((dx == 2 && dy == 1) || (dx == 1 && dy == 2)) {
        //position = destination;
        return true;
    }

    return false;
}


