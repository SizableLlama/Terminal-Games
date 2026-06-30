#include "Wordle.hpp"
#include "tictactoe.hpp"
#include <iostream>
#include <string>


int main() {
	int input;
	std::cout<<"Which game would you like to play?\n---------------\n1 for wordle, 2 for tic-tac-toe\n---------------\n>";
	std::cin>>input;

	while (input != 1 && input != 2) {
		std::cout<<"Please input either 1 or 2.\nWhich game would you like to play?\n---------------\n1 for wordle, 2 for tic-tac-toe\n---------------\n>";
		std::cin>>input;
	}

	if (input == 1) {
		wordle();
	}
	else if (input == 2) {
		tictactoe();
	}
	return 0;
}
