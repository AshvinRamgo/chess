// Rook.h
#ifndef ROOK_H
#define ROOK_H

#include "pieces.h"
#include <string>

class Rook : public Piece {
public:
    Rook(char color);
    bool move(std::string destination);
    bool hasMoved();
private:
    bool moved;
};

#endif // ROOK_H

