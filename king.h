// King.h
#ifndef KING_H
#define KING_H

#include "pieces.h"
#include <string>

class King : public Piece {
public:
    King(char color);
    bool move(std::string destination);
    bool hasMoved();
private:
    bool moved;
};

#endif // KING_H

