//#include <numbers>
#include <string>
#include <array>
#include <iostream>
//#include <vector>
#include <random>

	/* A connect four board is 7 rows, by 6 columns. eg:
	*
	*	| 0 | 0 | 0 | 0 | 0 | 0 | 0 |
	*	| 0 | 0 | 0 | 0 | 0 | 0 | 0 |
	*	| 0 | 0 | 0 | 0 | 0 | 0 | 0 |
	*	| 0 | 0 | 0 | 0 | 0 | 0 | 0 |
	*	| 0 | 0 | 0 | 0 | 0 | 0 | 0 |
	*	| 0 | 0 | 0 | 0 | 0 | 0 | 0 |
	*
	* I could represent this is a string. Or arrays. The issue with arrays are that they cannot be printed. Furthermore, the rows below influence the rows above.
	* An array could be represented by the following:
	* 	0,0,0,0,0,0,0
	* This would mean that you recursively check the same indice of the the decreasing numbered 'row', or array.
	* I can write a simple array printing function of the form: array[0]+" | \n"
	*/

/* GLOBAL VARIABLES */
enum gamestates {WIN, LOSS, ONGOING, TIE};
gamestates gamestat = ONGOING;

std::array<char, 3> counter{' ','X','O'};

//---------------------------------------------//
/* END OF GLOBALS   */

gamestates vector_checking(auto& Board, int column, int row, int player);


auto board() {
	std::array<std::array<char, 6>, 7> Board = {};
	//accessed by Board[column][row]
	return Board;
}

int lowest_row(int input, auto& Board) {
	for (int row = 5; row >= 0; row--) {
		if (Board[input][row] == '\0') return row;
	}
	return -1;  // column full
}

void populate_Board(int input, auto& Board, int currentPlayer) {
	int lowest = lowest_row(input, Board);
	if ( lowest == -1 ) return;
	char Counter = counter[currentPlayer];
	Board[input][lowest] = Counter;
	gamestat = vector_checking(Board, input, lowest, currentPlayer);
}

int ai(auto& Board, int currentPlayer) {
	std::random_device rd;
	std::mt19937 eng(rd());
	std::uniform_int_distribution<> distr(0, 6);

	int number;
	do {
		number = distr(eng);
	} while (lowest_row(number, Board) == -1);

	return number;
	//populate_Board(number, Board, currentPlayer);
}

//vector checking for a winning position.
gamestates vector_checking(auto& Board, int column, int row, int player) {
	//so, the vector? I don't know how it works.
	//Could think of it as this: (0,0), (0,1)... Which is already how it is!
	//Then for diagonals it is (take (0,0) as the starting point) (0+1,0+1)
	int in_a_row_diagonal   = 1;
	int in_a_row_vertical   = 1;
	int in_a_row_horizontal = 1;

	int valid_moves = 0;
	//int counter = 0;

	int original_column = column;
	int original_row = row;

	//First, I will implement checking the diagonals.
	while ( column+1 < 7 && row+1 < 6 && Board[column+1][row+1] == Board[column][row] ) {
		in_a_row_diagonal++;
		column++;row++;
	}
	column = original_column;
	row = original_row;

	while ( column-1 >= 0 && row-1 >= 0 && Board[column-1][row-1] == Board[column][row] ) {
		in_a_row_diagonal++;
		column--;row--;
	}
	column = original_column;
	row = original_row;

	while ( column+1 < 7 && Board[column+1][row] == Board[column][row] ) {
		in_a_row_vertical++;
		column++;
	}
	column = original_column;
	row = original_row;

	while ( column-1 >= 0 && Board[column-1][row] == Board[column][row] ) {
		in_a_row_vertical++;
		column--;
	}
	column = original_column;
	row = original_row;

	while ( row+1 < 6 && Board[column][row+1] == Board[column][row] ) {
		in_a_row_horizontal++;
		row++;
	}
	column = original_column;
	row = original_row;

	//changed from row > -1 to row >= -1
	while ( row-1 >= 0 && Board[column][row-1] == Board[column][row] ) {
		in_a_row_horizontal++;
		row--;
	}
	column = original_column;
	row = original_row;

	if ( in_a_row_horizontal >=4 || in_a_row_vertical >= 4 || in_a_row_diagonal >= 4 ) {
		if( player == 1 ) {
			return gamestat = gamestates::WIN;
		}
		else if (player == 2) {
			return gamestat = gamestates::LOSS;
		}
		else {
			return gamestat = gamestates::ONGOING;
		}
	}

		//Board[x][y];
		//for every seven iterations of y, there should be one of x.
	for (int x = 0; x < 7; x++) {
		for (int y = 0; y < 6; y++) {
			if (Board[x][y] == '\0') { valid_moves++; }
		}
	}

	if ( valid_moves == 0 ) {
		return gamestat = gamestates::TIE;
	}
	return gamestat = gamestates::ONGOING;
}
std::string print_board(auto& Board) {
	std::string String;
	std::string c = " ";
/*
	*********************************************
	*					    *
	*	| 0 | 0 | 0 | 0 | 0 | 0 | 0 |	    *
	*	| 0 | 0 | 0 | 0 | 0 | 0 | 0 |	    *
	*	| 0 | 0 | 0 | 0 | 0 | 0 | 0 |	    *
	*	| 0 | 0 | 0 | 0 | 0 | 0 | 0 |	    *
	*       | 0 | 0 | 0 | 0 | 0 | 0 | 0 |       *
	*	| 0 | 0 | 0 | 0 | 0 | 0 | 0 |	    *
	*					    *
	*********************************************

	zero zero is the top right.
*/
		//Board[y][x];
		//so, before each array, there should be a "| " or a " | " but the latter will work all the time and is easier.
		//So I'll do that. before each increment of y there should be a '\n'.
	for (int row = 0; row < 6; row++) {
		String+='\n';
		for (int column = 0; column < 7; column++) {
			char c = (Board[column][row] == '\0') ? ' ' : Board[column][row];
			String.append(" | ");
			String+=c;
		}
	}
	return String;
}

int connect_four() {
	gamestat = gamestates::ONGOING;
	auto Board = board();
	int input;
	int player;
	std::cout<<"Which player would you like to be? <1 for p1, 2 for p2> ";
	std::cin>>player;
	while (player != 1 && player != 2) {std::cout<<"Invalid. 1, or 2. > "; std::cin>>player;}
	if (player == 1) {
		while ( gamestat == gamestates::ONGOING ) {
			std::cout<<"\n-------------------------\n"<<print_board(Board)<<"\n   ^1  ^2  ^3  ^4  ^5  ^6  ^7";
			std::cout<<"\n-------------------------\n"<<"\nWhich column would you like to drop a ("<<counter[player]<<")\t> ";
			std::cin>>input; input--;
			while ( input >= 7 || input < 0 || lowest_row(input, Board) == -1 ) {
				std::cout<<"Invalid placement. Try again > "; std::cin>>input; input--;
			}
			//Player one shall be the first input. Two shall be the second where the ai (rng) has the first move.

			//Populate the lowest row, at selected column using the new 'lowest' variable.
			populate_Board(input, Board, player);
			if ( gamestat != gamestates::ONGOING ) break;
			//vector_checking(Board, input, lowest_row(input, Board), player);
			//std::cout<<print_board(Board)<<"\n   ^1  ^2  ^3  ^4  ^5  ^6  ^7";
			int number = ai(Board, 3-player);
			populate_Board(number, Board, 3-player);
			if ( gamestat != gamestates::ONGOING ) break;
		}
		if (gamestat == gamestates::WIN) {std::cout<<"\n"<<print_board(Board)<<"\n You win!\n";}

		else if (gamestat == gamestates::LOSS) {std::cout<<"\n"<<print_board(Board)<<"\n You lose!\n";}

		else if (gamestat == gamestates::ONGOING) {std::cout<<"\n"<<print_board(Board)<<"\n You draw!\n";}
	}
	if (player == 2) {
		while (gamestat == gamestates::ONGOING) {
			std::cout<<"\n-------------------------\n"<<print_board(Board)<<"\n   ^1  ^2  ^3  ^4  ^5  ^6  ^7";
			int number = ai(Board, 3-player);
			populate_Board(number, Board, 3-player);
			if ( gamestat != gamestates::ONGOING ) break;
			//std::cout<<"\n-------------------------\n"<<print_board(Board)<<"\n   ^1  ^2  ^3  ^4  ^5  ^6  ^7";
			std::cout<<"\n-------------------------\n"<<"\nWhich column would you like to drop a ("<<counter[player]<<")\t> ";
			std::cin>>input; input--;
			while ( input >= 7 || input < 0 || lowest_row(input, Board) == -1 ) {
				std::cout<<"Invalid placement. Try again > "; std::cin>>input; input--;
			}
			populate_Board(input, Board, player);
			if ( gamestat != gamestates::ONGOING ) break;
			//vector_checking(Board, input, lowest_row(input, Board), player);
		}
		if (gamestat == gamestates::WIN) {std::cout<<"\n"<<print_board(Board)<<"\n You lose!\n";}

		else if (gamestat == gamestates::LOSS) {std::cout<<"\n"<<print_board(Board)<<"\n You win!\n";}

		else if (gamestat == gamestates::ONGOING) {std::cout<<"\n"<<print_board(Board)<<"\n You draw!\n";}
	}
	return 0;
}
