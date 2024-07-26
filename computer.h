// In computer.h
#ifndef COMPUTER_H
#define COMPUTER_H

#include <string>
#include <vector>
#include "board.h"


class Computer {
public:
    // Constructor
    Computer(int level, Board *board, char color);

    // Method to make a move based on the computer's level
    std::string move();

private:
    // The level of difficulty for the computer player
    int level;

    // Pointer to the game board
    Board *board;

    // The color of the pieces the computer is playing ('W' for white, 'B' for black)
    char color; 
   
    // Helper function to generate all possible moves for the computer player
    std::vector<std::string> generateAllMoves(Board *board, char color);  
    
    // Helper function to evaluate a move
    int evaluateMove(Board *board, std::string move, char color);   
    // Minimax function 
    int minimax(Board *board, int depth, bool isMaximizingPlayer, char color);    

    // Method for level 1,2,3 difficulty
    std::string level1();
    std::string level2();
    std::string level3();

};


#endif // COMPUTER_H
