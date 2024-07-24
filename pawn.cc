// Pawn.cc
#include "pawn.h"
#include "king.h"
#include "rook.h"
#include "queen.h"
#include "knight.h"
#include "bishop.h"

Pawn::Pawn(char color) : Piece(color, 'P'), hasMoved(false), lastMove("") {}

bool Pawn::move(std::string destination, char promotion) {
    // Calculate the difference in rows and columns between the current position and the destination
    int rowDiff = destination[1] - position[1];
    int colDiff = destination[0] - position[0];

    // Check if the move is valid for a pawn
    if (color == 'W') {
        if ((rowDiff == 1 && colDiff == 0 && board[destination] == nullptr) || 
            (rowDiff == 1 && abs(colDiff) == 1 && board[destination] != nullptr && board[destination]->color == 'B')) {
            position = destination;
            hasMoved = true;
            lastMove = destination;
            return true;
        } else if (!hasMoved && rowDiff == 2 && colDiff == 0 && board[destination] == nullptr) {
            position = destination;
            hasMoved = true;
            lastMove = destination;
            return true;
        }
    } else { // color == 'B'
        if ((rowDiff == -1 && colDiff == 0 && board[destination] == nullptr) || 
            (rowDiff == -1 && abs(colDiff) == 1 && board[destination] != nullptr && board[destination]->color == 'W')) {
            position = destination;
            hasMoved = true;
            lastMove = destination;
            return true;
        } else if (!hasMoved && rowDiff == -2 && colDiff == 0 && board[destination] == nullptr) {
            position = destination;
            hasMoved = true;
            lastMove = destination;
            return true;
        }
    }

    // Check for en passant
    if (abs(rowDiff) == 1 && abs(colDiff) == 1 && board[destination] == nullptr) {
        // Get the position of the pawn that would be captured en passant
        std::string enPassantPawn = destination;
        enPassantPawn[1] = position[1]; // Same row as the current position

        // Check if the last move of the pawn at the enPassantPawn position was a two-square move
        if (board[enPassantPawn] != nullptr && board[enPassantPawn]->color != color && 
            board[enPassantPawn]->lastMove == enPassantPawn && abs(board[enPassantPawn]->position[1] - enPassantPawn[1]) == 2) {
            // Capture the pawn en passant
            delete board[enPassantPawn];
            board[enPassantPawn] = nullptr;
            position = destination;
            lastMove = destination;
            return true;
        }
    }

    // Check for promotion
    if ((color == 'W' && destination[1] == '8') || (color == 'B' && destination[1] == '1')) {
    // Replace the pawn with a new piece of the chosen type
    delete this;
    if (promotion == 'R') {
        board[position] = new Rook(color);
    } else if (promotion == 'N') {
        board[position] = new Knight(color);
    } else if (promotion == 'B') {
        board[position] = new Bishop(color);
    } else if (promotion == 'Q') {
        board[position] = new Queen(color);
    } else { // promotion == 'K'
        board[position] = new King(color);
    }
    return true;
}


    // If none of the conditions are met, the move is invalid
    return false;
}

