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
    player = 'w';
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

void Board::clear() {
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            if (board[i][j]) {
                delete board[i][j];
                board[i][j] = nullptr;
            }
        }
    }
}

bool Board::valid(std::string pos) {
    if (pos[0] <= 'h' && pos[0] >= 'a' && pos[1] <= '8' && pos[1] >= '1') {
        return true;
    }
    return false;
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

bool Board::move(const std::string& before, const std::string& after, char promotion, bool CHECK) { // the CHECK variable is for detecting checks
    int before_row = '8' - before[1];
    int before_col = before[0] - 'a';
    int after_row = '8' - after[1];
    int after_col = after[0] - 'a';
    char from_piece = view(before);
    char dest_piece = view(after);

    Piece* toMove = board[before_row][before_col];
    if (board[before_row][before_col] && board[before_row][before_col]->getColor() == (player - 'a' + 'A') && board[before_row][before_col]->move(before, after) && (!board[after_row][after_col] || board[before_row][before_col]->getColor() != board[after_row][after_col]->getColor())) {
        /*Piece* temp = board[after_row][after_col];                     // A simpler version is wrote below
        board[after_row][after_col] = board[before_row][before_col];     // note the "delete temp" below is part of this"
        board[before_row][before_col] = temp;
        move_history.push_back(before + after + promotion);
        lastMovedPiece = board[after_row][after_col];*/
        move_history.push_back(before + after + from_piece + dest_piece + promotion + ' ');
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

        if (CHECK && check(player)) {
            undo();
            return false;
        } 
        
        return true;
    }
    return false;
}

bool Board::isSquareUnderAttack(const std::string& position, char attackerColor) {
    char temp = player;
    player = attackerColor; // switch the player to the attacker first
    // Iterate over all pieces of the specified attacker color and check if any of them can move to the specified position
    for (int i = 7; i >= 0; --i) {
        for (int j = 0; j < 8; ++j) {
            std::string from = "";
            from += 'a' + j;
            from += '8' - i;
            if (board[i][j] && board[i][j]->getColor() == attackerColor - 'a' + 'A') {
                if (move(from, position, '\0', false)) {
                    undo();
                    player = temp;
                    return true;
                }
            }
        }
    }
    player = temp;
    return false;
}

bool Board::check(char KingColor) {
    if (KingColor >= 'A' && KingColor <= 'Z') {
        KingColor = KingColor - 'A' + 'a';
    }
    std::string KingPosition = "";
    for (int i = 7; i >= 0; --i) {
        for (int j = 0; j < 8; ++j) {
            std::string from = "";
            from += 'a' + j;
            from += '8' - i;
            if (view(from) == 'K' && 'w' == KingColor ) {
                KingPosition = from; 
            }
            if (view(from) == 'k' && 'b' == KingColor ) {
                KingPosition = from;
            }
        }
    }
    char attackerColor = (KingColor == 'w') ? 'b' : 'w';
    return isSquareUnderAttack(KingPosition, attackerColor);
}

bool Board::checkmate(char kingColor) /*const*/ {
    char temp = player;
    player = kingColor; // switch the player to the attacker first
    if (kingColor >= 'A' && kingColor <= 'Z') {
        kingColor = kingColor - 'A' + 'a';
    }
    if (!check(kingColor)) {
        player = temp;
        return false;
    }

    // Check if any legal move
    for (int i = 7; i >= 0; --i) {
        for (int j = 0; j < 8; ++j) {
            //std::string currentPos = std::string(1, 'a' + j) + std::to_string(8 - i);
            std::string currentPos = "";
            currentPos += 'a' + j;
            currentPos += '8' - i;
            for (int r = 7; r >= 0; --r) {
                for (int c = 0; c < 8; ++c) {
                    std::string newPos = "";
                    newPos += 'a' + c;
                    newPos += '8' - r;
                    //std::string newPos = std::string(1, 'a' + c) + std::to_string(8 - r);
                    if (move(currentPos, newPos)) {
                        undo();
                        player = temp;
                        return false;
                    }
                }
            }
        }
    }
    player = temp;
    return true;
}
    
    


bool Board::stalemate(char kingColor) /*const*/ {
    char temp = player;
    player = kingColor; // switch the player to the attacker first
    if (kingColor >= 'A' && kingColor <= 'Z') {
        kingColor = kingColor - 'A' + 'a';
    }
    if (check(kingColor)) {
        player = temp;
        return false;
    }

    // Check if any legal move
    for (int i = 7; i >= 0; --i) {
        for (int j = 0; j < 8; ++j) {
            //std::string currentPos = std::string(1, 'a' + j) + std::to_string(8 - i);
            std::string currentPos = "";
            currentPos += 'a' + j;
            currentPos += '8' - i;
            for (int r = 7; r >= 0; --r) {
                for (int c = 0; c < 8; ++c) {
                    std::string newPos = "";
                    newPos += 'a' + c;
                    newPos += '8' - r;
                    //std::string newPos = std::string(1, 'a' + c) + std::to_string(8 - r);
                    if (move(currentPos, newPos)) {
                        undo();
                        player = temp;
                        return false;
                    }
                }
            }
        }
    }
    player = temp;
    return true;
}

std::string Board::undo() { // returns the position of the squares that needs to be rendered
    if (!move_history.empty()) {
        std::string last_move = move_history.back();
        move_history.pop_back();
        // Implement logic to undo the last move
        // format of a move "FromDestFrompieceDestpiecePromotionSpecial", total 8 characters, special char can be 'E' for enpassant or 'C' for castle, otherwise ' '
        // example "a2a3P   " or "a4b5Pp  "
        std::string from = "";
        std::string to = "";
        from += last_move[0];
        from += last_move[1];
        to += last_move[2];
        to += last_move[3];
        if (last_move[7] == ' ') { // no special move, note the undo for promotion and non promotion is the same, since you don't care what it promoted to
            // the from square must be empty for each undo
            replacePiece(from, last_move[4]);
            replacePiece(to, last_move[5]);
        }
        // more undos to be implemented
        // if multiple games must clear history
        return last_move.substr(0, 4);
    }
}


bool Board::replacePiece(std::string position, char piece) {
    if (!valid(position)) {
        return false;
    }
    Piece* newPiece;
    switch (piece) {
        case 'P':
            newPiece = new Pawn('W', *this);
            break;
        case 'K':
            newPiece = new King('W', *this);
            break;
        case 'Q':
            newPiece = new Queen('W', *this);
            break;
        case 'R':
            newPiece = new Rook('W', *this);
            break;
        case 'B':
            newPiece = new Bishop('W', *this);
            break;
        case 'N':
            newPiece = new Knight('W', *this);
            break;
        case 'p':
            newPiece = new Pawn('B', *this);
            break;
        case 'k':
            newPiece = new King('B', *this);
            break;
        case 'q':
            newPiece = new Queen('B', *this);
            break;
        case 'r':
            newPiece = new Rook('B', *this);
            break;
        case 'b':
            newPiece = new Bishop('B', *this);
            break;
        case 'n':
            newPiece = new Knight('B', *this);
            break;
        case ' ':
            newPiece = nullptr;
            break;
        default:
            return false;
    }
    int row = '8' - position[1];
    int col = position[0] - 'a';
    if (board[row][col]) {
        delete board[row][col];
    }
    board[row][col] = newPiece;
    return true;
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

bool Board::isValidSetup() {
    int whiteKingCount = 0;
    int blackKingCount = 0;

    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            Piece* piece = board[i][j];
            if (piece) {
                // Check for pawns on the first or last row
                if ((i == 0 || i == 7) && piece->getType() == 'P') {
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
    if (whiteKingCount != 1 || blackKingCount != 1) {
        return false;
    }

    // Check if either king is in check
    
    if (check('w') || check('b')) {
        return false;
    }
    
    // If all checks passed, the setup is valid
    return true;
}
