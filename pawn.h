// Pawn.h
#ifndef PAWN_H
#define PAWN_H

#include "pieces.h"
#include <string>

class Pawn : public Piece {
public:
    Pawn(char color);
    bool move(std::string destination, char promotion = 'Q');
private:
    bool hasMoved;
    std::string lastMove; // To store the last move made by the pawn
};

#endif // PAWN_H

