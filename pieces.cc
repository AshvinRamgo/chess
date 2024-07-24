// Piece.cc
#include "pieces.h"

Piece::Piece(char color, char type) : color(color), type(type) {}

char Piece::getColor() {
    return color;
}

char Piece::getType() {
    return type;
}

