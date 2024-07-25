// Piece.cc
#include "pieces.h"

Piece::Piece(char color, char type, const Board& b) : color(color), type(type), board(b) {}

char Piece::getColor() {
    return color;
}

char Piece::getType() {
    return type;
}

