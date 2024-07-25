// Piece.h
#ifndef PIECE_H
#define PIECE_H

#include <string>

class Board; // forward declaration

class Piece {
public:
    Piece(char color, char type, const Board& b);
    virtual bool move(std::string position, std::string destination) = 0; // Pure virtual function
    char getColor();
    char getType();
protected:
    const Board& board;
    char color;
    char type;
    //std::string position;
};

#endif // PIECE_H

