// Knight.h
#ifndef KNIGHT_H
#define KNIGHT_H

#include "pieces.h"
#include <string>

class Knight : public Piece {
public:
    Knight(char color);
    bool move(std::string destination);
};

#endif // KNIGHT_H

