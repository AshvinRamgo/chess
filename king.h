// King.h
#ifndef KING_H
#define KING_H

#include "pieces.h"
#include <string>

class King : public Piece {
public:
    King(char color, const Board& b);
    bool move(std::string position, std::string destination);
    bool hasMoved();
    bool moved;
    
};

#endif // KING_H

