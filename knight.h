// Knight.h
#ifndef KNIGHT_H
#define KNIGHT_H

#include "pieces.h"
#include <string>

class Knight : public Piece {
public:
    Knight(char color, const Board& b);
    bool move(std::string position, std::string destination);
};

#endif // KNIGHT_H

