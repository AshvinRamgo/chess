// Pawn.cc
#include "pawn.h"
#include "king.h"
#include "rook.h"
#include "queen.h"
#include "knight.h"
#include "bishop.h"
#include "board.h" 

Pawn::Pawn(char color) : Piece(color, 'P'), hasMoved(false) {}

bool Pawn::move(std::string destination) {
    int dx = destination[0] - position[0];
    int dy = destination[1] - position[1];

    if (color == 'W') {
        dy = -dy;  // Adjust direction for white pawns
    }

    if (dy == 1 && dx == 0 && !hasMoved) {
        hasMoved = true;
        return true;
    }

    if (dy == 2 && dx == 0 && !hasMoved) {
        hasMoved = true;
        return true;
    }

    if (dy == 1 && abs(dx) == 1) {  // Capture move
        // Call enPassant method here
        /*Piece* lastMovedPiece = Board::getLastMovedPiece();  // Assume that there is a method in the Board class for getting the last moved piece
        if (enPassant(destination, lastMovedPiece)) {
            Board::replacePiece(destination, nullptr);  // Capture the last moved piece
            return true;
        } */
        return true;
    }

    // Check for promotion
    if ((color == 'W' && destination[1] == '8') || (color == 'B' && destination[1] == '1')) {
        // Call promotion method here
        char pieceType = 'Q';  // Assume that the pawn is always promoted to a queen for now
        promotion(pieceType);
    }

    return false;
}


bool Pawn::enPassant(std::string destination, Piece* lastMovedPiece) {
    // Check if the last moved piece is a pawn of the opposite color
    if (lastMovedPiece && lastMovedPiece->getType() == 'P' && lastMovedPiece->getColor() != this->getColor()) {
        // Check if the last moved piece moved two squares forward from its starting position
        // This will require access to the last moved piece's previous position and the board state
        // If the conditions for en passant are met, capture the last moved piece and return true
        /* int dx = lastMovedPiece->getPosition()[0] - position[0];
        int dy = lastMovedPiece->getPosition()[1] - position[1];

        if (abs(dy) == 2 && dx == 0) {
            // The last moved piece moved two squares forward
            // Now check if the destination square is the skipped square
            if (destination == lastMovedPiece->getPosition()) {
                return true;
            }
        } */
        return true;
    }
    return false;
}

void Pawn::promotion(char pieceType) {
    Piece* newPiece;
    switch (pieceType) {
        case 'Q':
            newPiece = new Queen(color);
            break;
        case 'R':
            newPiece = new Rook(color);
            break;
        case 'B':
            newPiece = new Bishop(color);
            break;
        case 'N':
            newPiece = new Knight(color);
            break;
        default:
            return;  // Invalid piece type
    }
    // Board::replacePiece(position, newPiece);
    // NOT IMPLEMENTED
}


