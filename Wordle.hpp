#include <iostream>
#include <SDL3/SDL.h>
#include <random>
#include <string>
#include <array>
#include <cctype>

bool in(char comparitor, const std::string& input);
bool in(char comparitor,const std::array<char, 5>& input);
std::string toLower(const std::string& String);
std::string printArray(const std::array<char, 5>& Array);
std::string printArray(const std::array<char, 26>& Array);
bool in(char comparitor,const std::array<char, 26>& input);

std::string wordGenerator() {
	//Generating a word using hardware or something. Hopefully will connect it to a database too.
	std::array<std::string, 50> wordArray={"apple", "beach", "cloud", "dance", "eagle", "flame", "grape", "house", "image", "juice", "koala", "lemon", "music", "night", "ocean", "piano", "queen", "river", "smile", "table", "uncle",
		"voice", "water", "xenon", "yacht", "zebra", "alarm", "bread", "candy", "dream", "earth", "field", "ghost", "heart", "ivory", "jelly", "knife", "light", "mouse", "nurse", "onion", "paper", "quiet", "radio",
		"stone", "tiger", "under", "vivid", "whale", "young"};
	random_device rd;
	mt19937 eng(rd());
	uniform_int_distribution<> distr(0,49);
	std::string word=wordArray.at(distr(eng));
	//cout<<word<<" \n";
	return word;
};

bool guessCheckLen( std::string& guess ) {
	//If length is 5 continue, probably didn't need a comment.
	if ( guess.length() == 5 ) {
		return true;
	}
	else {
		return false;
	}
}

void appendingArrays( std::string word, std::string guess, std::array<char, 5>& correctArray, std::array<char, 5>& wrongPlaceArray, std::array<char, 26>& wrongLetterArray, int& incorrectLetters, int& wrongPlace ) {
	//incorrectLetters and wrongPlace
	//Are to stop the two wrong arrays from being over written.
	for ( int x = 0; x < 5; x++ ) {
		if ( guess.at(x) == word.at(x) ) {
			correctArray.at(x) = guess.at(x);
		}
		else if ( in( guess.at(x), word ) ) {
			if ( !in( guess.at(x), wrongPlaceArray ) ) {
				wrongPlaceArray.at(wrongPlace) = guess.at(x);
				wrongPlace++;
			}
		}
		else {
			if ( !in( guess.at(x), wrongLetterArray ) ) {
				wrongLetterArray.at(incorrectLetters) = guess.at(x);
				incorrectLetters++;
			}
		}
	}

}

int wordle(){
	//The target word helpfully called word.
	std::string word = wordGenerator();

	int incorrectLetters = 0;
	int wrongPlace = 0;

	//The number of attempts called counter for some reason.
	int counter = 0;

	std::array<char, 5> correctArray={'_','_','_','_','_'};
	std::array<char, 5> wrongPlaceArray={'_','_','_','_','_'};
	std::array<char, 26> wrongLetterArray={'_','_','_','_','_','_','_','_','_','_','_','_','_','_','_','_','_','_','_','_','_','_','_','_','_','_'};

	std::string guess;

	//The main loop of the game.
	while ( counter < 6 ) {
		std::cout<<"Attempt: "<<counter<<"\n"<<"Please guess a five letter word.\n:";
		std::cin>>guess;
		//Convert the guess to lower-case
		guess = toLower(guess);

		/*If the guess isn't 5 characters long, the counter isn't updated.
		And the user is moved to the top of the while.*/
		if ( !guessCheckLen(guess) ) {
			std::cout<<"Invalid guess.\n";
			continue;
		};

		appendingArrays(word, guess, correctArray, wrongPlaceArray, wrongLetterArray, incorrectLetters, wrongPlace);
		counter++;



		//Display the arrays and go to the top of the while.
		std::cout<<"Correct letter correct place: "<<printArray(correctArray)<<"\nCorrect letter wrong place: "<<printArray(wrongPlaceArray)<<"\nWrong letter: "<<printArray(wrongLetterArray)<<"\n";
		if ( guess==word ) {
			//No error and a win!
			std::cout<<"You win in "<<counter<<" attempts!\n";
			return 0;
		}
	if ( counter == 6 ) {
		//No error and a loss.
		std::cout<<"You lose! The word was "<<word<<".\n";
	}

	}
	return 0;
}

bool in(char comparitor,const std::array<char, 5>& input){
	/*I made this, although I believe it exists in the algorithms file.
	Apparently size_t is better here?*/
	for ( size_t x=0; x < input.size(); x++ ) {
		if ( comparitor==input.at(x) ) {
			return true;
		};
	};
	return false;
}

bool in( char comparitor, const std::string& input ) {
	for ( size_t x=0; x < input.length(); x++ ) {
		if ( comparitor == input.at(x) ) {
			return true;
		};
	};
	return false;
}

bool in( char comparitor,const std::array<char, 26>& input ) {
	for ( size_t x=0; x < input.size(); x++ ) {
		if ( comparitor==input.at(x) ) {
			return true;
		};
	};
	return false;
}



std::string toLower(const std::string& String){
	std::string lowerString;
	//Make the string lower-case.
	for ( size_t x = 0; x < String.length(); x++ ) {
		lowerString = lowerString + (char)tolower(String.at(x));
	}
	return lowerString;
}

std::string printArray(const std::array<char, 5>& Array){
	std::string String;
	//Convert the array to a string, since they're only a max of 26 chars.
	for ( size_t x = 0; x < Array.size(); x++ ) {
		String = String+Array.at(x);
	};


	return String;
};

std::string printArray(const std::array<char, 26>& Array ) {
	std::string String;
	for ( size_t x = 0; x < Array.size(); x++ ) {
		String = String+Array.at(x);
	};


	return String;
};
