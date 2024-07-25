#include <iostream>
#include <string>
#include "board.h"

void printHelp() {
    std::cout << "Commands:\n";
    std::cout << "  game <white-player> <black-player>\n";
    std::cout << "  move <from> <to> [promotion]\n";
    std::cout << "  resign\n";
    std::cout << "  setup\n";
    std::cout << "  + <piece> <position>\n";
    std::cout << "  - <position>\n";
    std::cout << "  = <color>\n";
    std::cout << "  done\n";
    std::cout << "  quit\n";
}

int main() {
    Board board;
    std::string command;
    bool gameRunning = false;

    std::cout << "Welcome to Chess!" << std::endl;
    printHelp();

    while (true) {
        std::cout << "Enter command: ";
        std::cin >> command;

        if (command == "game") {
            std::string whitePlayer, blackPlayer;
            std::cin >> whitePlayer >> blackPlayer;
            board.initialize();
            gameRunning = true;
            std::cout << "New game started between " << whitePlayer << " (White) and " << blackPlayer << " (Black)" << std::endl;
        } else if (command == "move") {
            if (gameRunning) {
                std::string from, to;
                char promotion = '\0';
                std::cin >> from >> to;
                if (std::cin.peek() == ' ') {
                    std::cin >> promotion;
                }
                if (board.move(from, to, promotion)) {
                    std::cout << "Moved from " << from << " to " << to << std::endl;
                } else {
                    std::cout << "Invalid move" << std::endl;
                }
            } else {
                std::cout << "No game is currently running." << std::endl;
            }
        } else if (command == "resign") {
            if (gameRunning) {
                std::cout << "Player resigned. Game over." << std::endl;
                gameRunning = false;
            } else {
                std::cout << "No game is currently running." << std::endl;
            }
        } else if (command == "setup") {
            std::string setupCommand;
            while (true) {
                std::cout << "setup> ";
                std::cin >> setupCommand;
                if (setupCommand == "+") {
                    char piece;
                    std::string position;
                    std::cin >> piece >> position;
                    // Code to add piece to the board
                } else if (setupCommand == "-") {
                    std::string position;
                    std::cin >> position;
                    // Code to remove piece from the board
                } else if (setupCommand == "=") {
                    char color;
                    std::cin >> color;
                    // Code to set turn to color
                } else if (setupCommand == "done") {
                    // Code to validate and exit setup mode
                    break;
                } else {
                    std::cout << "Invalid setup command" << std::endl;
                }
            }
        } else if (command == "quit") {
            break;
        } else {
            std::cout << "Invalid command" << std::endl;
            printHelp();
        }
    }

    std::cout << "Game over" << std::endl;
    return 0;
}
