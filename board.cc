#include "board.h"
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
    board[0][0] = new Rook('B');
    board[0][1] = new Knight('B');
    board[0][2] = new Bishop('B');
    board[0][3] = new Queen('B');
    board[0][4] = new King('B');
    board[0][5] = new Bishop('B');
    board[0][6] = new Knight('B');
    board[0][7] = new Rook('B');
    for (int i = 0; i < 8; ++i) {
        board[1][i] = new Pawn('B');
    }

    // White pieces
    board[7][0] = new Rook('W');
    board[7][1] = new Knight('W');
    board[7][2] = new Bishop('W');
    board[7][3] = new Queen('W');
    board[7][4] = new King('W');
    board[7][5] = new Bishop('W');
    board[7][6] = new Knight('W');
    board[7][7] = new Rook('W');
    for (int i = 0; i < 8; ++i) {
        board[6][i] = new Pawn('W');
    }

    // Empty squares
    for (int i = 2; i < 6; ++i) {
        for (int j = 0; j < 8; ++j) {
            board[i][j] = nullptr;
        }
    }
}

std::string Board::view(const std::string& position) const { 
    int row = '8' - position[1];
    int col = position[0] - 'a';
    if (board[row][col]) {
        return std::string(1, board[row][col]->getColor()) + board[row][col]->getType();
    }
    return "";
}

bool Board::move(const std::string& before, const std::string& after, char promotion) {
    int before_row = '8' - before[1];
    int before_col = before[0] - 'a';
    int after_row = '8' - after[1];
    int after_col = after[0] - 'a';

    if (board[before_row][before_col] && board[before_row][before_col]->move(after)) {
        Piece* temp = board[after_row][after_col];
        board[after_row][after_col] = board[before_row][before_col];
        board[before_row][before_col] = temp;
        move_history.push_back(before + after + promotion);
        return true;
    }
    return false;
}

bool Board::isSquareUnderAttack(const std::string& position, char attackerColor) const {
    // Iterate over all pieces of the specified attacker color and check if any of them can move to the specified position
    int row = '8' - position[1];
    int col = position[0] - 'a';

    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            if (board[i][j] && board[i][j]->getColor() == attackerColor) {
                std::string currentPos = std::string(1, 'a' + j) + std::to_string(i + 1);
                if (board[i][j]->move(position)) {
                    return true;
                }
            }
        }
    }
    return false;
}

bool Board::check(const std::string& kingPosition) const {
    char kingColor = view(kingPosition)[0];
    char attackerColor = (kingColor == 'W') ? 'B' : 'W';
    return isSquareUnderAttack(kingPosition, attackerColor);
}

bool Board::checkmate(char kingColor) const {
    std::string kingPosition;
    for (int i = 0; i < 8; ++i) {
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
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            if (board[i][j] && board[i][j]->getColor() == kingColor) {
                std::string currentPos = std::string(1, 'a' + j) + std::to_string(i + 1);
                for (int r = 0; r < 8; ++r) {
                    for (int c = 0; c < 8; ++c) {
                        std::string newPos = std::string(1, 'a' + c) + std::to_string(r + 1);
                        Piece* temp = board[r][c];
                        if (board[i][j]->move(newPos)) {
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
    for (int i = 0; i < 8; ++i) {
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
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            if (board[i][j] && board[i][j]->getColor() == kingColor) {
                for (int r = 0; r < 8; ++r) {
                    for (int c = 0; c < 8; ++c) {
                        std::string newPos = std::string(1, 'a' + c) + std::to_string(r + 1);
                        if (board[i][j]->move(newPos)) {
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
