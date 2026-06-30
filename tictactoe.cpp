#include <string>
#include <array>
#include <iostream>
#include <random>

//Globals
enum gameState {
	WON, LOST, DRAW, UNDETERMINED
};
gameState g = gameState::UNDETERMINED;


gameState check(std::string& board, int& counter);
void input(std::string& board, int& counter);
void ai(std::string& board, int& counter);

void game(std::string& board) {
	board = " 1 | 2 | 3\n ---------\n 4 | 5 | 6\n ---------\n 7 | 8 | 9\n";
}

int main() {
	int counter = 0;
	int player;
	std::cout<<"Player 1 or Player 2?\n: ";
	std::cin>>player;
	while (player != 1 && player != 2) {
		std::cout<<"Invalid. Please enter either '1' or '2'\n";
		std::cout<<"Player 1 or Player 2?\n: ";
		std::cin>>player;

	}
	std::string board;
	game(board);
	if (player == 1) {
		while (g == gameState::UNDETERMINED) {
			std::cout<<board;
			input(board, counter);
			g = check(board, counter);
			if (g != gameState::UNDETERMINED) break;
			ai(board, counter);
			g = check(board, counter);
		}
		if (g == gameState::WON) {
			std::cout<<"\n"<<board<<"\nYou win!\n";
		}
		else if (g == gameState::LOST) {
			std::cout<<"\n"<<board<<"\nYou lose!\n";
		}
		else if (g == gameState::DRAW) {
			std::cout<<"\n"<<board<<"\nYou draw!\n";
		}
	}

	else if (player == 2) {
		while (g == gameState::UNDETERMINED) {
			ai(board, counter);
			std::cout<<board;
			g = check(board, counter);
			if (g != gameState::UNDETERMINED) break;
			input(board, counter);
			g = check(board, counter);
		}
		if (g == gameState::WON) {
			std::cout<<"\n"<<board<<"\nYou win!\n";
		}
		else if (g == gameState::LOST) {
			std::cout<<"\n"<<board<<"\nYou lose!\n";
		}
		else if (g == gameState::DRAW) {
			std::cout<<"\n"<<board<<"\nYou draw!\n";
		}
	}
	return 0;
}

void input(std::string& board, int& counter) {

	int Input;
	std::cout<<"Where would you like to place your 'x'? (1,9)\n: ";
	std::cin>>Input;
	switch(Input){
		case 1:
			if (board[1] != '1') {
				std::cout<<"cannot overwrite a valid placement.\n";
				input(board, counter);
				break;
			}
			board[1] = 'x';
			counter++;
			break;
		case 2:
			if (board[5] != '2') {
				std::cout<<"cannot overwrite a valid placement.\n";
				input(board, counter);
				break;
			}
			board[5] = 'x';
			counter++;
			break;
		case 3:
			if (board[9] != '3') {
				std::cout<<"cannot overwrite a valid placement.\n";
				input(board, counter);
				break;
			}
			board[9] = 'x';
			counter++;
			break;
		case 4:
			if (board[23] != '4') {
				std::cout<<"cannot overwrite a valid placement.\n";
				input(board, counter);
				break;
			}
			board[23] = 'x';
			counter++;
			break;
		case 5:
			if (board[27] != '5') {
				std::cout<<"cannot overwrite a valid placement.\n";
				input(board, counter);
				break;
			}
			board[27] = 'x';
			counter++;
			break;
		case 6:
			if (board[31] != '6') {
				std::cout<<"cannot overwrite a valid placement.\n";
				input(board, counter);
				break;
			}
			board[31] = 'x';
			counter++;
			break;
		case 7:
			if (board[45] != '7') {
				std::cout<<"cannot overwrite a valid placement.\n";
				input(board, counter);
				break;
			}
			board[45] = 'x';
			counter++;
			break;
		case 8:
			if (board[49] != '8') {
				std::cout<<"cannot overwrite a valid placement.\n";
				input(board, counter);
				break;
			}
			board[49] = 'x';
			counter++;
			break;
		case 9:
			if (board[53] != '9') {
				std::cout<<"cannot overwrite a valid placement.\n";
				input(board, counter);
				break;
			}
			board[53] = 'x';
			counter++;
			break;
		default:
			std::cout<<"Invalid, must be integer 1 - 9\n";
			input(board, counter);
			break;

	}
}

gameState check(std::string& board, int& counter) {

	/*

		[1]   [5]   [9]

		[23]  [27]  [31]

		[45]  [49]  [53]
	*/

	if (board[1] == 'o' && board[5] == 'o' && board[9] == 'o') return g =gameState::LOST;
	else if (board[1] == 'o' && board[23] == 'o' && board[45] == 'o') return g = gameState::LOST;
	else if (board[1] == 'o' && board[27] == 'o' && board[53] == 'o') return g = gameState::LOST;
	else if (board[5] == 'o' && board[27] == 'o' && board[49] == 'o') return g = gameState::LOST;
	else if (board[9] == 'o' && board[31] == 'o' && board[53] == 'o') return g = gameState::LOST;
	else if (board[23] == 'o' && board[27] == 'o' && board[31] == 'o') return g = gameState::LOST;
	else if (board[45] == 'o' && board[49] == 'o' && board[53] == 'o') return g = gameState::LOST;
	else if (board[9] == 'o' && board[27] == 'o' && board[45] == 'o') return g = gameState::LOST;



	if (board[1] == 'x' && board[5] == 'x' && board[9] == 'x') return g = gameState::WON;
	else if (board[1] == 'x' && board[23] == 'x' && board[45] == 'x') return g = gameState::WON;
	else if (board[1] == 'x' && board[27] == 'x' && board[53] == 'x') return g = gameState::WON;
	else if (board[5] == 'x' && board[27] == 'x' && board[49] == 'x') return g = gameState::WON;
	else if (board[9] == 'x' && board[31] == 'x' && board[53] == 'x') return g = gameState::WON;
	else if (board[23] == 'x' && board[27] == 'x' && board[31] == 'x') return g = gameState::WON;
	else if (board[45] == 'x' && board[49] == 'x' && board[53] == 'x') return g = gameState::WON;
	else if (board[9] == 'x' && board[27] == 'x' && board[45] == 'x') return g = gameState::WON;


	/*
	int x = 0;
	for (int z = 0; z < board.size(); z++) {
		if (board[z] == '1' || board[z] == '2' || board[z] == '3' || board[z] == '4' || board[z] == '5' || board[z] == '6' || board[z] == '7' || board[z] == '8' || board[z] == '9') x++;
	}
	*/

	if (counter == 9) {
		return g = gameState::DRAW;
	}
	else {
		return g = gameState::UNDETERMINED;
	}
}

void ai(std::string& board, int& counter) {
	std::array<int, 9>ran = {1, 2, 3, 4, 5, 6, 7, 8, 9};
	std::random_device rd;
	std::mt19937 eng(rd());
	std::uniform_int_distribution<> distr(0,8);
	int number = ran.at(distr(eng));

	switch(number){
		case 1:
			if (board[1] != '1') {
				ai(board, counter);
				break;
			}
			board[1] = 'o';
			counter++;
			break;
		case 2:
			if (board[5] != '2') {
				ai(board, counter);
				break;
			}
			board[5] = 'o';
			counter++;
			break;
		case 3:
			if (board[9] != '3') {
				ai(board, counter);
				break;
			}
			board[9] = 'o';
			counter++;
			break;
		case 4:
			if (board[23] != '4') {
				ai(board, counter);
				break;
			}
			board[23] = 'o';
			counter++;
			break;
		case 5:
			if (board[27] != '5') {
				ai(board, counter);
				break;
			}
			board[27] = 'o';
			counter++;
			break;
		case 6:
			if (board[31] != '6') {
				ai(board, counter);
				break;
			}
			board[31] = 'o';
			counter++;
			break;
		case 7:
			if (board[45] != '7') {
				ai(board, counter);
				break;
			}
			board[45] = 'o';
			counter++;
			break;
		case 8:
			if (board[49] != '8') {
				ai(board, counter);
				break;
			}
			board[49] = 'o';
			counter++;
			break;
		case 9:
			if (board[53] != '9') {
				ai(board, counter);
				break;
			}
			board[53] = 'o';
			counter++;
			break;
		default:
			std::cout<<"There was an error generating an ai response.\n";

	}
}
