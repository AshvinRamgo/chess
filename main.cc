#include "board.h"
#include "text_display.h"
#include "graphical_display.h"
#include "window.h"
#include <unistd.h>
#include <string>
#include <iostream>


char next(char current) { // returns the next player to move
    if (current == 'w') {
        return 'b';
    }
    return 'w';
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
    printHelp();
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
    chessBoard.player = 'w';


    // implement prompts last
    /* std::cout << “Welcome to our chess game!\nFor starting a new game, enter “game”.\nFor making a move, enter “move pos1 pos2”.\nFor undoing a move, enter “undo”.\nFor resigning, enter “resign”.\nFor setup mode, enter “setup”\n” */


    while (!std::cin.eof()) {
        std::string input = "";
        while (std::cin >> input) {
            if (input == "game") {
                // Set up the game (unimplemented)
                /*
                std::string p1 = "";
                std::string p2 = "";
                std::cin >> p1;
                std::cin >> p2;
                */
                if (chessBoard.player == 'w') {
                    std::cout << "\nWhite First\n";
                } else {
                    std::cout << "\nBlack First\n";
                }
                graphicalDisplay.draw_board();
                textDisplay.render();
                
                // chessBoard.setPlayers(p1, p2);
            } else if (input == "move"){
		        std::string pos, dest;
		        char promotion = 0;
		        std::cin >> pos >> dest;
		        if (std::cin.peek() == ' '){
			        std::cin >> promotion;
		        } else {
                    promotion = ' ';
                }
		        if (!chessBoard.move(pos, dest, promotion)){
			        std::cout << "invalid move" << std::endl;
		        } else {
			        // render	
			        textDisplay.render();
                    if (pos == "e1") {
                        if (dest == "h1") {
                            graphicalDisplay.render(1, 6, 1, 7);
                        } else if (dest == "a1") {
                            graphicalDisplay.render(1, 3, 1, 4);
                        }
                    } else if (pos == "e8") {
                        if (dest == "h8") {
                            graphicalDisplay.render(8, 6, 8, 7);
                        } else if (dest == "a8") {
                            graphicalDisplay.render(8, 3, 8, 4);
                        }
                    }
			        graphicalDisplay.render(pos[1] - '0', pos[0] - 'a' + 1, dest[1] - '0', dest[0] - 'a' + 1);
			        // check for checkmate, stalemate
                    //std::cout << chessBoard.checkmate(next(chessBoard.player)) << std::endl;
                    
			        if (chessBoard.checkmate(next(chessBoard.player))) {
			            if (chessBoard.player == 'w') {
				            wwin += 1;
				            textDisplay.checkmate('w');
				            graphicalDisplay.checkmate('w');
				            sleep(1);
				            textDisplay.score(bwin, wwin);
				            graphicalDisplay.score(bwin, wwin);
				            sleep(2);
				            chessBoard.initialize();
				            break;
			            }
			            bwin+= 1;
			            textDisplay.checkmate('b');
			            graphicalDisplay.checkmate('b');
			            sleep(1);
			            textDisplay.score(bwin, wwin);
			            graphicalDisplay.score(bwin, wwin);
			            sleep(2);
			            chessBoard.initialize();
			            break;
			        } else if (chessBoard.stalemate(next(chessBoard.player))) {
			            textDisplay.stalemate();
			            graphicalDisplay.stalemate();
			            sleep(1);
			            textDisplay.score(bwin, wwin);
			            graphicalDisplay.score(bwin, wwin);
			            sleep(2);
			            chessBoard.initialize();
			            break;
            
			        } else {
                        
                        chessBoard.player = next(chessBoard.player);
                        if (chessBoard.player == 'w') {
                            std::cout << "\nWhite Next\n";
                        } else {
                            std::cout << "\nBlack Next\n";
                        }
                    }
			// switch players
		        }
            }
            else if (input == "undo") {
                // Undo a move
                std::string pos = chessBoard.undo();
                chessBoard.player = next(chessBoard.player);
                textDisplay.render();
                int index = 0;
                while (index < pos.length()) {
                    graphicalDisplay.render_square(pos[index + 1] - '0', pos[index] - 'a' + 1);
                    index += 2;
                }
            }
            else if (input == "resign") {
                // Resign the game
                if (chessBoard.player == 'b') {
                    wwin += 1;
                }
                else {
                    bwin += 1;
                }
	   	        // resign and display scores
                textDisplay.resign(chessBoard.player);
		        graphicalDisplay.resign(chessBoard.player);
		        sleep(1); // pauses execution for 1 second from unistd.h
		        textDisplay.score(bwin, wwin);
		        graphicalDisplay.score(bwin, wwin);
		        sleep(2);
                chessBoard.clear();
		        chessBoard.initialize();
                break;
            }
            else if (input == "setup") {
                // Enter setup mode
                chessBoard.clear();
                textDisplay.render();
                graphicalDisplay.draw_board();
                std::string op;
                while (std::cin >> op) {
                    if (op == "+") {
                        char piece;
                        std::string pos;
                        std::cin >> piece >> pos;
                        if (piece == ' ' || !chessBoard.replacePiece(pos, piece)) {
                            std::cout << "Invalid add. Please try again." << std::endl;
                        } else {
			                textDisplay.render();
			                graphicalDisplay.render_square(pos[1] - '0', pos[0] - 'a' + 1);
                        }
                    }
                    else if (op == "-") {
                        std::string pos;
                        std::cin >> pos;
                        if (!chessBoard.replacePiece(pos, ' ')) {
                            std::cout << "Invalid remove. Please try again." << std::endl;
                        } else {
			                textDisplay.render();
			                graphicalDisplay.render_square(pos[1] - '0', pos[0] - 'a' + 1);
                        }
                    }
                    else if (op == "=") {
                        std::string color;
			            std::cout << "Enter the color of the player to go next (black or white): "; 
                        std::cin >> color;
			            while (color != "white" && color != "black") {
			                std::cout << "Invalid color. Please enter 'white' or 'black'. ";
                            std::cin >> color;
                        }
                        if (color == "white") {
                            chessBoard.player = 'w';
                        } else {
                            chessBoard.player = 'b';
                        }
                        std::cout << "First Move: " << color << std::endl;
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

