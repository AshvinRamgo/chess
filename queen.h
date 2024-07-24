// Queen.h
#ifndef QUEEN_H
#define QUEEN_H

#include "pieces.h"
#include <string>

class Queen : public Piece {
public:
    Queen(char color);
    bool move(std::string destination);
};

#endif // QUEEN_H
