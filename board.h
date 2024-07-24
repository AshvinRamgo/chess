#ifndef BOARD_H
#define BOARD_H

#include <string>
#include <vector>
#include "pieces.h"
#include "queen.h"
#include "pawn.h"
#include "rook.h"
#include "queen.h"
#include "knight.h"
#include "king.h"
#include "bishop.h"

class Board {
private:
    static Piece* board[8][8];
    std::vector<std::string> move_history;

    bool isSquareUnderAttack(const std::string& position, char attackerColor) const;

public:
    Board();
    ~Board();

    void initialize();
    std::string view(const std::string& position) const;
    bool move(const std::string& before, const std::string& after, char promotion = '\0');
    bool check(const std::string& kingPosition) const;
    bool checkmate(char kingColor) const;
    bool stalemate(char kingColor) const;
    void undo();
};

#endif
