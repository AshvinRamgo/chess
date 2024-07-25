// Pawn.h
#ifndef PAWN_H
#define PAWN_H

#include "pieces.h"

class Pawn : public Piece {
public:
    Pawn(char color, const Board& b);
    bool move(std::string position, std::string destination) override;
    bool enPassant(std::string destination, Piece* lastMovedPiece);
    void promotion(char pieceType);
private:
    bool hasMoved;
};

#endif // PAWN_H
