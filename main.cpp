#include "Wordle.hpp"
#include "tictactoe.hpp"
#include <iostream>
#include <string>

bool select(int& input, bool& play);
bool menu(bool& play) {
	int input;
	std::string message = "Which game would you like to play?\n--------------------------------------------------\n1 for wordle, 2 for tic-tac-toe. (3 to quit.)\n--------------------------------------------------\n>";
	std::cout<<message;
	std::cin>>input;
	while (input != 3) {
		while (input != 1 && input != 2 && input != 3) {
			std::cout<<"Please input either 1 or 2 (3 to quit).\n\n"<<message;
			std::cin>>input;
		}

		play = select(input, play);
		break;
	}
	std::cout<<"\nGoodbye!\n";
	return play = false;
}

bool select(int& input, bool& play) {
	if (input == 1) {
		wordle();
		return true;
	}
	else if (input == 2) {
		tictactoe();
		return true;
	}
	else if (input == 3) {
		return false;
	}
	else return true;
}




int main() {
	bool play = true;
	while (play) {
		menu(play);
	}
	return 0;
}
