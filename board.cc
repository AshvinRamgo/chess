#include "board.h"
#include "pieces.h"
#include "queen.h"
#include "pawn.h"
#include "rook.h"
#include "knight.h"
#include "king.h"
#include "bishop.h"
#include <iostream>
#include <sstream>

Board::Board() {
    initialize();
}

Board::~Board() {
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            delete board[i][j];
        }
    }
}

void Board::initialize() {
    // Initialize the board with the standard starting positions
    // Black pieces
    board[0][0] = new Rook('B', *this);
    board[0][1] = new Knight('B', *this);
    board[0][2] = new Bishop('B', *this);
    board[0][3] = new Queen('B', *this);
    board[0][4] = new King('B', *this);
    board[0][5] = new Bishop('B', *this);
    board[0][6] = new Knight('B', *this);
    board[0][7] = new Rook('B', *this);
    for (int i = 0; i < 8; ++i) {
        board[1][i] = new Pawn('B', *this);
    }

    // White pieces
    board[7][0] = new Rook('W', *this);
    board[7][1] = new Knight('W', *this);
    board[7][2] = new Bishop('W', *this);
    board[7][3] = new Queen('W', *this);
    board[7][4] = new King('W', *this);
    board[7][5] = new Bishop('W',*this);
    board[7][6] = new Knight('W',*this);
    board[7][7] = new Rook('W', *this);
    for (int i = 0; i < 8; ++i) {
        board[6][i] = new Pawn('W', *this);
    }

    // Empty squares
    for (int i = 2; i < 6; ++i) {
        for (int j = 0; j < 8; ++j) {
            board[i][j] = nullptr;
        }
    }
}

char Board::view(const std::string& position) const { 
    int row = '8' - position[1];
    int col = position[0] - 'a';
    /* if (board[row][col]) {
        return std::string(1, board[row][col]->getColor()) + board[row][col]->getType();
    }
    return ""; */
    if (board[row][col]) {
        if (board[row][col]->getColor() == 'W') {
            return board[row][col]->getType();
        }
        return board[row][col]->getType() - 'A' + 'a';
    }
    return ' ';
}

bool Board::move(const std::string& before, const std::string& after, char promotion) {
    int before_row = '8' - before[1];
    int before_col = before[0] - 'a';
    int after_row = '8' - after[1];
    int after_col = after[0] - 'a';


    Piece* toMove = board[before_row][before_col];
    if (board[before_row][before_col] && board[before_row][before_col]->move(before, after) && board[before_row][before_col]->getColor() != board[after_row][after_col]->getColor()) {
        /*Piece* temp = board[after_row][after_col];                     // A simpler version is wrote below
        board[after_row][after_col] = board[before_row][before_col];     // note the "delete temp" below is part of this"
        board[before_row][before_col] = temp;
        move_history.push_back(before + after + promotion);
        lastMovedPiece = board[after_row][after_col];*/
        if (board[after_row][after_col]) {
            delete board[after_row][after_col];
        }
        board[after_row][after_col] = board[before_row][before_col];
        board[before_row][before_col] = nullptr;

        // Handle promotion
        if (toMove->getType() == 'P' && (after_row == 0 || after_row == 7)) {
            delete board[after_row][after_col];
            switch (promotion) {
                case 'Q':
                    board[after_row][after_col] = new Queen(toMove->getColor(), *this);
                    break;
                case 'R':
                    board[after_row][after_col] = new Rook(toMove->getColor(), *this);
                    break;
                case 'B':
                    board[after_row][after_col] = new Bishop(toMove->getColor(), *this);
                    break;
                case 'N':
                    board[after_row][after_col] = new Knight(toMove->getColor(), *this);
                    break;
                default:
                    board[after_row][after_col] = new Queen(toMove->getColor(), *this);
                    break;
            }
        }

        //delete temp;
        return true;
    }
    return false;
}

bool Board::isSquareUnderAttack(const std::string& position, char attackerColor) const {
    // Iterate over all pieces of the specified attacker color and check if any of them can move to the specified position
    int row = '8' - position[1];
    int col = position[0] - 'a';

    for (int i = 7; i >= 0; --i) {
        for (int j = 0; j < 8; ++j) {
            std::string from = "";
            from += 'a' + j;
            from += '8' - i;
            if (board[i][j] && board[i][j]->getColor() == attackerColor) {
                std::string currentPos = std::string(1, 'a' + j) + std::to_string(i + 1);
                if (board[i][j]->move(from, position)) {
                    return true;
                }
            }
        }
    }
    return false;
}

bool Board::check(const std::string& kingPosition) const {
    
    char kingColor = view(kingPosition);
    if (kingColor = 'K') {
        kingColor = 'W';
    } else {
        kingColor = 'B';
    }
    char attackerColor = (kingColor == 'W') ? 'B' : 'W';
    return isSquareUnderAttack(kingPosition, attackerColor);
}

bool Board::checkmate(char kingColor) /*const*/ {
    std::string kingPosition;
    for (int i = 7; i >= 0; --i) {
        for (int j = 0; j < 8; ++j) {
            if (board[i][j] && board[i][j]->getColor() == kingColor && board[i][j]->getType() == 'K') {
                kingPosition = std::string(1, 'a' + j) + std::to_string(i + 1);
                break;
            }
        }
    }
    if (!check(kingPosition)) {
        return false;
    }

    // Check if any legal move can remove the check
    for (int i = 7; i >= 0; --i) {
        for (int j = 0; j < 8; ++j) {
            if (board[i][j] && board[i][j]->getColor() == kingColor) {
                std::string currentPos = std::string(1, 'a' + j) + std::to_string(i + 1);
                for (int r = 7; r >= 0; --r) {
                    for (int c = 0; c < 8; ++c) {
                        std::string newPos = std::string(1, 'a' + c) + std::to_string(r + 1);
                        Piece* temp = board[r][c];
                        std::string from = "";
                        from += 'a' + j;
                        from += '8' - i;
                        if (board[i][j]->move(from, newPos)) {
                            board[r][c] = board[i][j];
                            board[i][j] = nullptr;
                            if (!check(kingPosition)) {
                                board[i][j] = board[r][c];
                                board[r][c] = temp;
                                return false;
                            }
                            board[i][j] = board[r][c];
                            board[r][c] = temp;
                        }
                    }
                }
            }
        }
    }
    return true;
}

bool Board::stalemate(char kingColor) const {
    std::string kingPosition;
    for (int i = 7; i >= 0; --i) {
        for (int j = 0; j < 8; ++j) {
            if (board[i][j] && board[i][j]->getColor() == kingColor && board[i][j]->getType() == 'K') {
                kingPosition = std::string(1, 'a' + j) + std::to_string(i + 1);
                break;
            }
        }
    }
    if (check(kingPosition)) {
        return false;
    }

    // Check if there are any legal moves available for the king's color
    for (int i = 7; i >= 0; --i) {
        for (int j = 0; j < 8; ++j) {
            if (board[i][j] && board[i][j]->getColor() == kingColor) {
                for (int r = 7; r >= 0; --r) {
                    for (int c = 0; c < 8; ++c) {
                        std::string newPos = std::string(1, 'a' + c) + std::to_string(r + 1);
                        std::string from = "";
                        from += 'a' + j;
                        from += '8' - i;
                        if (board[i][j]->move(from, newPos)) {
                            return false;
                        }
                    }
                }
            }
        }
    }
    return true;
}

void Board::undo() {
    if (!move_history.empty()) {
        std::string last_move = move_history.back();
        move_history.pop_back();
        // Implement logic to undo the last move
    }
}


void Board::replacePiece(std::string position, Piece* newPiece) {
    int row = '8' - position[1];
    int col = position[0] - 'a';
    delete board[row][col];
    board[row][col] = newPiece;
}

// This method assumes a valid path
bool Board::isPathClear(int startX, int startY, int endX, int endY) const {
    // Determine the direction of the move
    int directionX, directionY;
    if (endX > startX) {directionX = 1;}
    else if (endX == startX) {directionX = 0;}
    else {directionX = -1;}
    if (endY > startY) {directionY = 1;}
    else if (endY == startY) {directionY = 0;}
    else {directionY = -1;}

    // Move to next square in direction of the move
    startX += directionX;
    startY += directionY;

    // Continue moving in direction of move until we reach destination
    while (startX != endX || startY != endY) {
        // Convert current coordinates to a position string
        //std::string currentPosition = std::string(1, 'a' + startX) + std::to_string(1 + startY);       //commented out because not used

        // If the current square is occupied, path is not clear
        if (board[startY][startX] != nullptr) {
            return false;
        }

        // Move to next square in direction of the move
        startX += directionX;
        startY += directionY;
    }

    // If we reached the destination without finding any occupied squares, path is clear
    return true;
}

/* bool Board::isValidSetup() const {
    int whiteKingCount = 0;
    int blackKingCount = 0;

    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            Piece* piece = board[i][j];
            if (piece) {
                // Check for pawns on the first or last row
                if ((i == 0  i == 7) && piece->getType() == 'P') {
                    return false;
                }

                // Count the kings
                if (piece->getType() == 'K') {
                    if (piece->getColor() == 'W') {
                        ++whiteKingCount;
                    } else if (piece->getColor() == 'B') {
                        ++blackKingCount;
                    }
                }
            }
        }
    }

    // Check for exactly one king of each color
    if (whiteKingCount != 1  blackKingCount != 1) {
        return false;
    }

    // Check if either king is in check
    std::string whiteKingPosition, blackKingPosition;
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            Piece* piece = board[i][j];
            if (piece && piece->getType() == 'K') {
                if (piece->getColor() == 'W') {
                    whiteKingPosition = std::string(1, 'a' + j) + std::to_string(8 - i);
                } else if (piece->getColor() == 'B') {
                    blackKingPosition = std::string(1, 'a' + j) + std::to_string(8 - i);
                }
            }
        }
    }

    if (check(whiteKingPosition) || check(blackKingPosition)) {
        return false;
    }

    // If all checks passed, the setup is valid
    return true;
} */
