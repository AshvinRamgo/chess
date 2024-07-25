// Rook.h
#ifndef ROOK_H
#define ROOK_H

#include "pieces.h"
#include <string>

class Rook : public Piece {
public:
    Rook(char color, const Board& b);
    bool move(std::string position, std::string destination);
    bool hasMoved();
private:
    bool moved;
};

#endif // ROOK_H

