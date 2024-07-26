#include <vector>
#include <cstdlib>  // for std::rand
#include "computer.h"
#include "board.h"

/*
// Helper function to generate all possible moves
std::vector<std::string> Computer::generateAllMoves(Board *board, char color) {
    std::vector<std::string> allMoves;
    // Loop over all squares on the board
    for (char i = 'a'; i <= 'h'; ++i) {
        for (char j = '1'; j <= '8'; ++j) {
            std::string from = std::string() + i + j;
            // If the square is not empty and contains a piece of the computer's color
            char f = board->view(from);
            if (f != ' ' && ((f >= 'A' && f <= 'Z' && color == 'w') || (f >= 'a' && f <= 'z' && color == 'b'))) {
                // Loop over all squares to which this piece might move
                for (char k = 'a'; k <= 'h'; ++k) {
                    for (char l = '1'; l <= '8'; ++l) {
                        std::string to = std::string() + k + l;
                        // Try the move and see if it's legal
                        if (board->move(from, to)) {
                            // If the move is legal, add it to the list of possible moves
                            allMoves.push_back(from + to);
                            // Undo the move
                            board->undo();         //NOT IMPLEMENTED
                        }
                    }
                }
            }
        }
    }
    return allMoves;
}


// Helper function to evaluate a move
int Computer::evaluateMove(Board *board, std::string move, char color) {
    // Extract the 'from' and 'to' positions from the move
    std::string from = move.substr(0, 2);
    std::string to = move.substr(2, 2);

    // Get the piece at the 'to' position
    char capturedPiece = board->view(to);

    // Initialize the score for the move
    int score = 0;

    // If the move captures an opponent's piece, increase the score
    if (capturedPiece != ' ' && ((capturedPiece >= 'A' && capturedPiece <= 'Z' && color != 'w') || (capturedPiece >= 'a' && capturedPiece <= 'z' && color != 'b'))) {
        // Increase the score based on the type and value of the captured piece
        char pieceType = capturedPiece;
        if (pieceType <= 'z' && pieceType >= 'a') {pieceType = pieceType - 'a' + 'A';}
        switch (pieceType) {
            case 'P': score += 10; break;  // Pawn
            case 'N': score += 30; break;  // Knight
            case 'B': score += 30; break;  // Bishop
            case 'R': score += 50; break;  // Rook
            case 'Q': score += 90; break;  // Queen
            case 'K': score += 900; break;  // King
        }
    }

    // If the move results in a check, increase the score
    if (board->move(from, to)) {
        if (board->check(color == 'W' ? "BK" : "WK")) {
            score += 5;
        }
        // Undo the move
        board->undo();
    }

    return score;
}



int Computer::minimax(Board *board, int depth, bool isMaximizingPlayer, char color) {
    // If the depth is 0 or the game is over, return the evaluation of the board
    if (depth == 0 || board->checkmate() || board->stalemate()) {
        return evaluateBoard(board, color);
    }

    if (isMaximizingPlayer) {
        int maxEval = -9999;
        std::vector<std::string> allMoves = generateAllMoves(board, color);
        for (std::string move : allMoves) {
            if (board->move(move.substr(0, 2), move.substr(2, 2))) {
                int eval = minimax(board, depth - 1, false, color);
                maxEval = std::max(maxEval, eval);
                board->undo();
            }
        }
        return maxEval;
    } else {
        int minEval = 9999;
        std::vector<std::string> allMoves = generateAllMoves(board, color == 'W' ? 'B' : 'W');
        for (std::string move : allMoves) {
            if (board->move(move.substr(0, 2), move.substr(2, 2))) {
                int eval = minimax(board, depth - 1, true, color);
                minEval = std::min(minEval, eval);
                board->undo();
            }
        }
        return minEval;
    }
}


Computer::Computer(int level, Board *board, char color) : level(level), board(board), color(color) {}

std::string Computer::level1() {
    // Generate all possible moves
    std::vector<std::string> allMoves = generateAllMoves(board, color);
    // Choose a random move
    int randomIndex = std::rand() % allMoves.size();
    return allMoves[randomIndex];
}




std::string Computer::level2() {
    // Generate all possible moves
    std::vector<std::string> allMoves = generateAllMoves(board, color);

    // Initialize the best score and an empty string for the best move
    int bestScore = -9999;
    std::string bestMove = "";

    // Evaluate each move using the minimax algorithm
    for (std::string move : allMoves) {
        if (board->move(move.substr(0, 2), move.substr(2, 2))) {
            int score = minimax(board, 2, false, color);
            board->undo();
            if (score > bestScore) {
                bestScore = score;
                bestMove = move;
            }
        }
    }

    return bestMove;
}

std::string Computer::level3() {
    // Generate all possible moves
    std::vector<std::string> allMoves = generateAllMoves(board, color);

    // Initialize the best score and an empty string for the best move
    int bestScore = -9999;
    std::string bestMove = "";

    // Evaluate each move using the minimax algorithm
    for (std::string move : allMoves) {
        if (board->move(move.substr(0, 2), move.substr(2, 2))) {
            int score = minimax(board, 3, false, color);
            board->undo();
            if (score > bestScore) {
                bestScore = score;
                bestMove = move;
            }
        }
    }

    return bestMove;
}


// Logic 
//  Minimax Algorithm: The minimax algorithm is a recursive algorithm simulates all possible moves up to a certain depth,
//  evaluates the resulting board positions, and chooses the move that 
//  maximizes the minimum value of the opponent’s possible following moves.
// Maximizing and Minimizing Player: In the context of your chess game, the computer is the maximizing player and the opponent is the minimizing player. 
// The computer tries to maximize its score, while the opponent tries to minimize the computer’s score.
*/
