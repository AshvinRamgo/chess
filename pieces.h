// Piece.h
#ifndef PIECE_H
#define PIECE_H

#include <string>

class Piece {
public:
    Piece(char color, char type);
    virtual bool move(std::string destination) = 0; // Pure virtual function
    char getColor();
    char getType();
protected:
    char color;
    char type;
    std::string position;
};

#endif // PIECE_H

