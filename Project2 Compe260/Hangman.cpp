#include "HangWord.h"
#include <vector>
#include <ctype.h>
#include <fstream>
#include <string>
#include <ctime>
#include <cstdlib>
#include <stdlib.h>
#include <time.h> 
//#include <bits/stdc++.h> // for string copy

Hangman::Hangman() {
	letter = 0;
	wrongGuesses = 0;
	wordLength = 0;
}

void Hangman::displayMenu()													//options of Play, Enter Words, and Quit
{
	system("cls");
	cout << "Welcome to Hangman!" << endl;
	cout << "Choose the number corresponding to your choice. Then press enter." << endl;
	cout << "1) Play" << endl;
	cout << "2) Enter New Words" << endl;
	cout << "3) Quit" << endl;
}

void Hangman::enterNewWords()												//inserts contents into the vector named wordList
{
	ofstream myfile;														//opens file
	myfile.open("..\\hangmanGameWords.txt", std::ios_base::app);			//asks the user to enter words into the myfile
	string newWord;
	while (1)
	{
		cout << "Enter a word for the myfile.It has to be 5 letters or more. Then press enter (type EXIT to exit): ";	//lets user input new words
		cin >> newWord;														//collects the new word from user
		if (newWord == "EXIT")												//exits for function choosen by user
			break;
		newWord = "\n" + newWord;											//inserts a new line for the text file
		myfile << newWord;													//puts the new word in hangmanGameWords.txt
	}
	myfile.close();															//closes myfile
	cin.clear();
	cin.ignore();
}

void Hangman::readFromFile()										//selects a random from the vector wordList which is stored in the variable secretWord
{
	string line;
	std::ifstream myfile("..\\hangmanGameWords.txt");
	if (myfile.is_open())											//opens myfile
	{
		std::string line;
		while (getline(myfile, line))
		{
			wordList.push_back(line);								//loading into wordList
		}
			int i = rand() % 10;									//picks a random word from the wordList
			vector<string>::iterator itr = wordList.begin() + i;	//iterator helps to index the variable
			secretWord = *itr;
			wordLength = secretWord.size();							//kength of the secretWord
		myfile.close();												//closes myfile
	}
	else cout << "Unable to open file";								//fails to open file
}

void Hangman::setSecretWord(string word)							//store the random word from the wordList which would be the guessWord
{
	secretWord = word;
}

string Hangman::getSecretWord()
{
	return secretWord;
}

void Hangman::setWordLength(int length)								//used to store the length of the variable secretWord
{
	wordLength = length;
}

int Hangman::getWordLength()
{
	return wordLength;
}

bool Hangman::isWin(char guess, string Word, string& secretWord)					//helps to check if the user won or not
{
	const int wordLength = 20;														//static length of array
	char arr[wordLength];															//char array
	strcpy_s(arr, Word.c_str());													//copy Word => arr[]
	char unarr[wordLength];															//init
	strcpy_s(unarr, secretWord.c_str());											//Copy string pointer to char array
	bool found = false;																//initially we assume we don't have a match
	for (int i = 0; i < wordLength; i++)
	{
		if (arr[i] == guess)														//if guess is equal to the current indexed char, then we found it
		{
			found = true;
			unarr[i] = arr[i];
		}
	}
	secretWord = "";
	for (int i = 0; i < wordLength; i++) secretWord = secretWord + unarr[i];
	return found;																	// return bool
}

void Hangman::play()
{
	readFromFile();																				//uses this function to select a word from wordList for the secretWord
	string unknown(wordLength, '-');															//dashes with the wordLength
	wrongGuesses = 0;
	while (wrongGuesses < attempts)																//loop until the attempts are used up
	{
		cout << "\n" << unknown;
		cout << "\nGuess a letter: ";															//asks user for letter
		cin >> letter;																			//collects user's letter
		if (!isalpha(letter))
		{
			cout << "Invalid letter, try again." << endl;
		}

		else if (!isWin(letter, secretWord, unknown))											//fill secret word with letter if the guess is correct,  otherwise increment the number of wrong guesses.
		{
			cout << endl << "OH NO! That letter isn't in there!" << endl;						//wrong letter
			wrongGuesses++;
		}

		else
		{
			cout << endl << "You found a letter!" << endl;					//right letter
		}
		cout << "You have " << attempts - wrongGuesses;											//tell user how many guesses has left.
		cout << " guesses left." << endl;

		if (unknown.find(secretWord) != std::string::npos)										//checks if user guessed the word.
		{
			convertToUpper();																	//uppercase secretWord
			cout << "\nYeah! You got it!" << endl;	
			cout << "Press enter to go back to Main Menu." << endl;
			break;
		}
	}
	if (wrongGuesses == attempts)																//when the attempts run out
	{
		cout << "\nSorry, you lose. YOU HAVE BEEN HANGED!" << endl;
		cout << "The word was : ";
		convertToUpper();																		//reveals the secretWord in uppercase
		cout << "\nPress enter to go back to Main Menu." << endl;
	}
	cin.ignore();
	cin.clear();
	cin.get();
}

void Hangman::convertToUpper()										//puts letters of the variable secretWord to uppercase
{
	int i = 0;
	while (secretWord[i]) {
		letter = secretWord[i];
		printf("%c",toupper(letter));
		i++;
	}
}