#include <iostream>
#include <algorithm>
#include <array>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

string userGuess;


void printChoice(string word, string guesses) {
	/*
	This function prints the user current guesses for letters in the random hangman word.
	*/
	// Prinitng out the guesses
	for (int i = 0; i < word.length(); i++) {
		// The character is a slash it means the user hasn't input anything so it will be an empty space.
		if (guesses[i] == '/') {
			std::cout << " \t";
		}
		else {
			std::cout << guesses[i] << "\t";
		}
	}
	std::cout << "\n";
	// Printing the line under
	for (int i = 0; i < word.length(); i++) {
		std::cout << "________";
	}
	std::cout << "\n";
}

vector<int> findIndex(string word, char guessChar) {
	/*Searches for the indexes where that guessed character appears in the word and adds them to the vector and returns the vector */
	vector<int> index;
	int index1 = -1;

	int counter = 0;
	// Find the charcter in the word from the first index.
	while (true) {
		index1 = word.find(guessChar, index1 + 1);
		// If the index is the end index then it will break the loop
		if (index1 == string::npos) {
			break;
		}
		// Adding the position of the found character to the vector
		index.push_back(index1);
		counter += 1;
	}

	if (counter == 0) {
		// If no indexes are found it returns with a -1 element.
		index.push_back(-100);
	}
	// Returning the vector containing the indexes of where the guessed character appears in the original word.
	return index;
}

int updateGuess(string word, string guess, char guessChar) {
	/*
	Function that update the users current guess based on the recent char they guessed */

	// Calling the function to return a vector containing the indexes of the locations of the characters in the word and setting it as our variable, they are vectors containing integers.
	vector<int> index = findIndex(word, guessChar);

	// If the vector has a negative 100  then it is empty
	if (index[0] == -100) {
		// If no characters of the guessChar were found in the random word then it will return -1, denoting a bad guess.
		return -1;

	}
	// If vector is not replace characters.
	else {
		// Loop through the vector and replace the characters in the users guess with the guessed character
		for (int i : index) {
			// Changing the char at the index of where the users guessed char appears to the guessed character.
			userGuess[i] = guessChar;
		}
	}
	// Returns 0 if the user guessed correctly.
	return 0;
}

array<string, 220> createRandomListWord() {
	/*Function that returns a list of random words*/
	array<string, 220> words;
	string line = "";
	// Creating an input file stream
	ifstream inputFile;
	inputFile.open("words.txt");
	for (int i = 0; i < 220; i++) {
		// Taking the input from the file putting it into the 
		getline(inputFile, line);
		// Making the first character lowercase in each word.
		line[0] = tolower(line[0]);
		// Adding the lowercased line from the text file to the array of words.
		words[i] = line;
		// Inputted the nextline to go over the empty line.
		getline(inputFile, line);
	}
	inputFile.close();
	return words;
}

//
//string createImages() {
//	;
//}


int triesChecker(int output, char userGuess, int turns, string word, string guess, array<string, 7>images) {
	/*According to if the user got their guess wrong or right the function will print different things*/

	// If the users guess was incorrect.
	if (output == -1) {
		std::cout << "\n\nYour guess was incorrect for the character " << userGuess << ".\nYou have: " << 7 - turns << " guesses left.\n\n";
		// Printing the image for their turns
		std::cout << images[turns - 1] << "\n";
		printChoice(word, guess);
		// Returns 1 to add to the turns variable
		return 1;

	}
	// If the user guess was correct.
	else {
		// Telling the user his guess was correct
		std::cout << "\n\nYour guess was correct" << "\nYou have: " << 7 - turns + 1 << " guesses left.\n\n";
		// Printing the user's guess.
		printChoice(word, guess);
		return 0;
	}
}


bool ifWon(string guess, string word) {
	/*
	Takes in the guess and the random word and if they are equal the user has won, if they are not the user lost.
	*/
	// If the guess and the random word are the same
	if (guess == word) {
		return true;
	}
	// If both words are not the same
	else {
		return false;
	}
}


int main() {
	// String containing an array of random words
	// array<string, 220>words = createRandomListWord();
	// string line = "";
	// // Creating an input file stream
	array<string, 218>words;
	ifstream inputFile;
	inputFile.open("words_images.txt");
	string line = "";
	// Importing the words from the text and adding them into the array
	for (int i = 0; i < 218; i++) {
		// Taking the input from the file putting it into the 
		getline(inputFile, line);
		// Making the first character lowercase in each word.
		line[0] = tolower(line[0]);
		// Adding the lowercased line from the text file to the array of words.
		words[i] = line;
		// Inputted the nextline to go over the empty line.
		getline(inputFile, line);
	}

	// String of the alphabet
	string alphabet = "abcdefghijklmnopqrstuvwxyz";


	// for (int i = 0 ; i < 220; i++){
	// 	std::cout << words[i] << "\n";
	// }

	// Choosing a random index
	srand(time(NULL));
	int random_index = rand() % 218 + 1;

	// Choosing the random word and storing userGuess
	string randomWord = words[random_index];
	// Making the first character lower case
	// randomWord[0]

	// string userGuess;

	// Setting up the user guess string, the guessed characters will replace the slashes
	for (int i = 0; i < randomWord.length(); i++) {
		userGuess += '/';
	}


	int guess = 0;
	// Storing the images in the array.
	array<string, 7>images;


	string templine = "";
	// Looping through 7 images
	for (int i = 0; i < 7; i++) {
		// Resetting it after every image
		line = "";
		// Making the images
		for (int i = 0; i < 7; i++) {
			// Getting the input for the temporary line
			templine = "";
			getline(inputFile, templine);
			// Adding a new character to the end
			templine = templine + "\n";
			line += templine;
		}
		// Adding the current hangman into the array.
		images[i] = line;
	}
	// Closing the input file
	inputFile.close();
	// Introductory statement
	std::cout << "\nHello! Welcome to Hangman, by Michael Fedotov.\nIn this game you will be asked to guess a letter from the randomly generated word.\nYour previous letters will show up in the console.\nTo win the game you need to guess all the letters in the word within 7 guesses.\nYou lose if you do not guess the word within 7 guesses.\nThe secret word chosen has " << randomWord.length() << " letters.\n";

	// Game variables

	// If the guess was correct or not
	int guessCorrect = 0;
	// Stores the user guess
	char guessChar;
	// Counts the number of attemps the user had made guessing, 7 is the max.
	int triesCounter = 1;
	// Boolean for if the user has won or not.
	bool won = false;

	// Asking the user for their guess
	std::cout << "\nPlease enter your guess for a letter in the word: ";
	std::cin >> guessChar;
	cin.ignore(324, '\n');

	// Updating the guess and returning -1 if the user guessed incorrectly or 0 if the user guessed correctly.
	guessCorrect = updateGuess(randomWord, userGuess, guessChar);
	triesCounter += triesChecker(guessCorrect, guessChar, triesCounter, randomWord, userGuess, images);

	// printChoice(randomWord, userGuess);

	// While loop for the only runs for 7 turns. (Turns start at 1)
	while (triesCounter < 8) {
		std::cout << "\nPlease enter your guess for a letter in the word: ";
		std::cin >> guessChar;
		cin.ignore(324, '\n');

		// Updating the guess and returning -1 if the user guessed incorrectly or 0 if the user guessed correctly.
		guessCorrect = updateGuess(randomWord, userGuess, guessChar);

		// Checking if the user guessed right or wrong and printing the appropriate messages
		// Also adds 1 or 0 to the counter of turns depending on if you got the right guess or not.
		triesCounter += triesChecker(guessCorrect, guessChar, triesCounter, randomWord, userGuess, images);

		// Checking if the user won
		won = ifWon(userGuess, randomWord);
		// If the user has won, then the game will stop.
		if (won){
			std::cout << "YOU HAVE GUESSED THE WORD CORRECTLY!\nYOU HAVE WON THE GAME!\nTHE WORD TO GUESS WAS: ";
			std::cout << randomWord << "\nYou took: " << triesCounter << " turns to guess the word.\n";
			break;
		}
		

	}
	// If the user did not win.
	if (!won) {
		std::cout << "\n\nYOU DID NOT GUESS THE WORD CORRECTLY IN 7 TRIES\nTHE WORD WAS: " << randomWord;
	}

	cout << "\n\n\n<PRESS ENTER>";
	cin.clear();
	cin.ignore(32767, '\n');
}