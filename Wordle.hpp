#include <iostream>
#include <SDL3/SDL.h>
#include <random>
#include <string>
#include <array>
#include <cctype>

using namespace std;
bool in(char comparitor, const string& input);
bool in(char comparitor,const array<char, 5>& input);
string toLower(const string& String);
string printArray(const array<char, 5>& Array);
string printArray(const array<char, 26>& Array);
bool in(char comparitor,const array<char, 26>& input);

string wordGenerator(){
	//Generating a word using hardware or something. Hopefully will connect it to a database too.
	array<string, 50> wordArray={"apple", "beach", "cloud", "dance", "eagle", "flame", "grape", "house", "image", "juice", "koala", "lemon", "music", "night", "ocean", "piano", "queen", "river", "smile", "table", "uncle",
		"voice", "water", "xenon", "yacht", "zebra", "alarm", "bread", "candy", "dream", "earth", "field", "ghost", "heart", "ivory", "jelly", "knife", "light", "mouse", "nurse", "onion", "paper", "quiet", "radio",
		"stone", "tiger", "under", "vivid", "whale", "young"};
	random_device rd;
	mt19937 eng(rd());
	uniform_int_distribution<> distr(0,49);
	string word=wordArray.at(distr(eng));
	//cout<<word<<" \n";
	return word;
};

bool guessCheckLen(string& guess){
	//If length is 5 continue, probably didn't need a comment.
	if(guess.length() == 5){
		return true;
	}
	else{
		return false;
	}
}

void appendingArrays(string word, string guess, array<char, 5>& correctArray, array<char, 5>& wrongPlaceArray, array<char, 26>& wrongLetterArray, int& incorrectLetters, int& wrongPlace){
	//incorrectLetters and wrongPlace
	//Are to stop the two wrong arrays from being over written.
	for(int x=0;x<5;x++){
		if(guess.at(x)==word.at(x)){
			correctArray.at(x)=guess.at(x);
		}
		else if(in(guess.at(x),word)){
			if(!in(guess.at(x),wrongPlaceArray)){
				wrongPlaceArray.at(wrongPlace)=guess.at(x);
				wrongPlace++;
			}
		}
		else{
			if(!in(guess.at(x),wrongLetterArray)){
				wrongLetterArray.at(incorrectLetters)=guess.at(x);
				incorrectLetters++;
			}
		}
	}

}

int wordle(){
	//The target word helpfully called word.
	string word = wordGenerator();

	int incorrectLetters=0;
	int wrongPlace=0;

	//The number of attempts called counter for some reason.
	int counter=0;

	array<char, 5> correctArray={'_','_','_','_','_'};
	array<char, 5> wrongPlaceArray={'_','_','_','_','_'};
	array<char, 26> wrongLetterArray={'_','_','_','_','_','_','_','_','_','_','_','_','_','_','_','_','_','_','_','_','_','_','_','_','_','_'};

	string guess;

	//The main loop of the game.
	while(counter<6){
		cout<<"Attempt: "<<counter<<"\n"<<"Please guess a five letter word.\n:";
		cin>>guess;
		//Convert the guess to lower-case
		guess = toLower(guess);

		/*If the guess isn't 5 characters long, the counter isn't updated.
		And the user is moved to the top of the while.*/
		if(!guessCheckLen(guess)){
			cout<<"Invalid guess.\n";
			continue;
		};

		appendingArrays(word,guess,correctArray,wrongPlaceArray,wrongLetterArray,incorrectLetters,wrongPlace);
		counter++;



		//Display the arrays and go to the top of the while.
		cout<<"Correct letter correct place: "<<printArray(correctArray)<<"\nCorrect letter wrong place: "<<printArray(wrongPlaceArray)<<"\nWrong letter: "<<printArray(wrongLetterArray)<<"\n";
		if (guess==word){
			//No error and a win!
			cout<<"You win in "<<counter<<" attempts!\n";
			return 0;
		}
	if (counter==6){
		//No error and a loss.
		cout<<"You lose! The word was "<<word<<".\n";
	}

	}
	return 0;
}

bool in(char comparitor,const array<char, 5>& input){
	/*I made this, although I believe it exists in the algorithms file.
	Apparently size_t is better here?*/
	for(size_t x=0; x<input.size(); x++){
		if(comparitor==input.at(x)){
			return true;
		};
	};
	return false;
}

bool in(char comparitor, const string& input){
	for(size_t x=0; x<input.length(); x++){
		if(comparitor==input.at(x)){
			return true;
		};
	};
	return false;
}

bool in(char comparitor,const array<char, 26>& input){
	for(size_t x=0; x<input.size(); x++){
		if(comparitor==input.at(x)){
			return true;
		};
	};
	return false;
}



string toLower(const string& String){
	string lowerString;
	//Make the string lower-case.
	for(size_t x=0; x < String.length(); x++){
		lowerString=lowerString + (char)tolower(String.at(x));
	}
	return lowerString;
}

string printArray(const array<char, 5>& Array){
	string String;
	//Convert the array to a string, since they're only a max of 26 chars.
	for(size_t x=0; x < Array.size(); x++){
		String=String+Array.at(x);
	};


	return String;
};

string printArray(const array<char, 26>& Array){
	string String;
	for(size_t x=0; x < Array.size(); x++){
		String=String+Array.at(x);
	};


	return String;
};
