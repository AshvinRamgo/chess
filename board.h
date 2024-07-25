#ifndef BOARD_H
#define BOARD_H

#include <string>
#include <vector>
#include "pieces.h"

class Board {
private:
    /*static*/ Piece* board[8][8];
    std::vector<std::string> move_history;
    Piece* lastMovedPiece;  

    bool isSquareUnderAttack(const std::string& position, char attackerColor) const;

public:
    Board();
    ~Board();

    void initialize();
    char view(const std::string& position) const;
    bool move(const std::string& before, const std::string& after, char promotion = '\0');
    bool check(const std::string& kingPosition) const;
    bool checkmate(char kingColor) /*const*/;
    bool stalemate(char kingColor) const;
    void undo();
    void replacePiece(std::string position, Piece* newPiece);
    bool isPathClear(int startX, int startY, int endX, int endY) const;
    Piece* getLastMovedPiece() const {return lastMovedPiece;}; 
    bool isValidSetup() const;
};

#endif
