// Bishop.h
#ifndef BISHOP_H
#define BISHOP_H

#include "pieces.h"
#include <string>

class Bishop : public Piece {
public:
    Bishop(char color);
    bool move(std::string destination);
};

#endif // BISHOP_H

