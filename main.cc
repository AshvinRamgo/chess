#include "board.h"
#include "text_display.h"
#include "window.h"
#include <unistd.h>
#include <string>
#include <iostream>


char next(char current) { // returns the next player to move
    if (current == ‘w’) {
        return ‘b’;
    }
    return ‘w’;
}


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
    // Create a Board object
    Board chessBoard;
    chessBoard.initialize();


    // Create a Text_Display object
    Text_Display textDisplay(chessBoard);
    textDisplay.render();


    // Create a Graphical_Display object
    Graphical_Display graphicalDisplay(chessBoard);


    // Initialize scores for black and white
    int bwin = 0;
    int wwin = 0;
	
    // Other variables
    char player = ‘w’;


    // implement prompts last
    /* std::cout << “Welcome to our chess game!\nFor starting a new game, enter “game”.\nFor making a move, enter “move pos1 pos2”.\nFor undoing a move, enter “undo”.\nFor resigning, enter “resign”.\nFor setup mode, enter “setup”\n” */


    while (!std::cin.eof()) {
        std::string input = "";
        while (std::cin >> input) {
            if (input == "game") {
                // Set up the game
		   player = ‘w’;
                std::string p1 = "";
                std::string p2 = "";
                std::cin >> p1;
                std::cin >> p2;
                // chessBoard.setPlayers(p1, p2);
            }
            else if (input == “move”){
		   std::string pos, dest;
		   char promotion = 0;
		   std::cin >> pos >> dest;
		   if (std::cin.peek() == ‘ ‘){
			std::cin >> promotion;
		   }
		   if (!board.move(pos, dest, promotion)){
			std::cout << “invalid move” << std::endl;
		   } else {
			// render	
			textDisplay.render();
			graphicalDisplay.render(pos[1] - ‘0’, pos[0] - ‘a’ + 1, dest[1] - ‘0’, dest[0] - ‘a’ + 1);
			// check for checkmate, stalemate
			if (chessBoard.checkmate(next(player) + ‘A’ - ‘a’)) {
			    if (player == ‘w’) {
				wwin += 1;
				textDisplay.checkmate(‘w’);
				graphicalDisplay.checkmate(‘w’);
				sleep(1);
				textDisplay.score(bwin, wwin);
				graphicalDisplay.score(bwin, wwin);
				sleep(2);
				chessBoard.initialize();
				break;
			    }
			    bwin+= 1;
			    textDisplay.checkmate(‘b’);
			    graphicalDisplay.checkmate(‘b’);
			    sleep(1);
			    textDisplay.score(bwin, wwin);
			    graphicalDisplay.score(bwin, wwin);
			    sleep(2);
			    chessBoard.initialize();
			    break;
			} else if (chessBoard.stalemate(next(player) + ‘A’ - ‘a’)) {
			    textDisplay.stalemate()
			    graphicalDisplay.stalemate()
			    sleep(1);
			    textDisplay.score(bwin, wwin);
			    graphicalDisplay.score(bwin, wwin);
			    sleep(2);
			    chessBoard.initialize();
			    break;
			} else {
			    player = next(player);
			}
			// switch players
		   }
            }
            else if (input == "undo") {
                // Undo a move
                chessBoard.undo(); // not implemented yet
            }
            else if (input == "resign") {
                // Resign the game
                if (player == ‘b’) {
                    bwin += 1;
                }
                else {
                    wwin += 1;
                }
	   	   // resign and display scores
                textDisplay.resign(player);
		   graphicalDisplay.resign(player);
		   sleep(1); // pauses execution for 1 second from unistd.h
		   textDisplay.score(bwin, wwin);
		   graphicalDisplay.score(bwin, wwin);
		   sleep(2);
		   chessBoard.initialize();
                break;
            }
            else if (input == "setup") {
                // Enter setup mode
                std::string op;
                while (std::cin >> op) {
                    if (op == "+") {
                        char piece;
                        std::string pos;
                        std::cin >> piece >> pos;
                        chessBoard.replacePiece(pos, new Piece(piece));
			    textDisplay.render()
			    graphicalDisplay.render_square(pos[1] - ‘0’, pos[0] - ‘a’ + 1);
                    }
                    else if (op == "-") {
                        std::string pos;
                        std::cin >> pos;
                        chessBoard.replacePiece(pos, nullptr);
                        textDisplay.render()
			    graphicalDisplay.render_square(pos[1] - ‘0’, pos[0] - ‘a’ + 1);
                    }
                    else if (op == "=") {
                        std::string color;
			    std::cout << “Enter the color of the player to go next
			    (black or white): “ ; 
                        std::cin >> color;
			    while (color != “white” || “color != “black) {
			    std::cout << “Invalid color. Please enter ‘white’ or
    ‘black’. ;
    std::cin >> color;
}
std::cout “Please make a move” << color; 
                    }
                    else if (op == "done") {
                        if (chessBoard.isValidSetup()) {
                            break;
                        } else {
                            std::cout << "Invalid setup. Please try again." << std::endl;
                        }
                    }
                }
            }
            else {
                std::cout << "Invalid command. Please try again." << std::endl;
            }
        }
    }


    return 0;
}
