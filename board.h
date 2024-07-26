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

    bool isSquareUnderAttack(const std::string& position, char attackerColor);

public:
    char player;
    Board();
    ~Board();

    void initialize();
    void clear();
    bool valid(std::string pos);
    char view(const std::string& position) const;
    bool move(const std::string& before, const std::string& after, char promotion = '\0');
    bool check(char KingColor);
    bool checkmate(char kingColor) /*const*/;
    bool stalemate(char kingColor) ;
    std::string undo();
    bool replacePiece(std::string position, char piece);
    bool isPathClear(int startX, int startY, int endX, int endY) const;
    Piece* getLastMovedPiece() const {return lastMovedPiece;}; 
    bool isValidSetup();
};

#endif
