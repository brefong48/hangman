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
	numberWrongGuesses = 0;
	wordLength = 0;
}

void Hangman::displayMenu()											//options of Play, Enter Words, and Quit
{
	system("cls");
	cout << "Welcome to Hangman!" << endl;
	cout << "Choose the number corresponding to your choice. Then press enter." << endl;
	cout << "1) Play" << endl;
	cout << "2) Enter New Words" << endl;
	cout << "3) Quit" << endl;
}

void Hangman::enterNewWords()										//inserts contents into the vector named wordList
{
	int newWords;
	cout << "Enter words for the myfile.";							//asks the user to enter words into the myfile
	ifstream myfile("hangmanWords.txt", ios::in);
	if (myfile.is_open())											//opens myfile
	{
		myfile >> newWords;											//enters the words the user entered
		myfile.close();												//closes myfile
	}
	else cout << "Unable to open file";
}

void Hangman::readFromFile()										//selects a random from the vector wordList which is stored in the variable secretWord
{
	string line;
	const int maxSecretWords = 10;
	std::ifstream myfile("hangmanWords.txt");

	if (myfile.is_open())											//opens myfile
	{
		while (!myfile.eof())
		{
			getline(myfile, line);
			wordList.push_back(line);								//loading into wordList
			cout << line << endl;
		}
		myfile.close();												//closes myfile
	}
	else cout << "Unable to open file";

	int n = rand() % 10;
	vector<string>::iterator ind = wordList.begin() + n;
	string secretWord = *ind;
	wordLength = secretWord.size();
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

bool Hangman::letterFill(char guess, string Word, string& Placeholder)
{
	const int length = 20;															// static length of array
	char arr[length];																// char array
	strcpy_s(arr, Word.c_str());													// copy Word => arr[]
	char unarr[length];																// init
	strcpy_s(unarr, Placeholder.c_str());											// Copy string pointer to char array
	bool found = false;																// initially we assume we don't have a match
	for (int i = 0; i < length; i++)
	{
		if (arr[i] == guess)														// if guess is equal to the current indexed char, then we found it
		{
			found = true;
			unarr[i] = arr[i];
			break;
		}
	}
	Placeholder = "";
	for (int i = 0; i < length; i++) Placeholder = Placeholder + unarr[i];
	return found;																	// return bool
}

//string fillInDashes(int length) // Accept any integer length
//{
//	string temp; // init
//	for (int i = 0; i < length; i++)
//		temp = temp + "_"; // Adds _ to string
//	return temp;
//}

void Hangman::play()
{
	readFromFile();
	string unknown(wordLength, '_');															//dashes with the wordLength
	numberWrongGuesses = 0;
	string temp; // init
	while (numberWrongGuesses < attempts)														//loop until the attempts are used up
	{
		system("cls");
		cout << "\n" << unknown;
		cout << "Guess a letter: ";
		cin >> letter;
		if (!letterFill(letter, secretWord, unknown))											//fill secret word with letter if the guess is correct,  otherwise increment the number of wrong guesses.
		{
			for (int i = 0; i < letter; i++)
				temp = temp + "_"; // Adds _ to string
			cout << endl << "Whoops! That letter isn't in there!" << endl;
			numberWrongGuesses++;
		}
		else
		{
			for (int i = 0; i < letter; i++)
				temp = temp + "_"; // Adds _ to string
			cout << endl << "You found a letter! Isn't that exciting!" << endl;
		}
		cout << "You have " << attempts - numberWrongGuesses;									// Tell user how many guesses has left.
		cout << " guesses left." << endl;

		if (secretWord == unknown)																	// Check if user guessed the word.
		{
			for (int i = 0; i < letter; i++)
				temp = temp + "_"; // Adds _ to string
			cout << secretWord << endl;
			cout << "Yeah! You got it!";	//might need to change this to isWin(string guessWord, string secretWord)
			break;
		}
	}
	if (numberWrongGuesses == attempts)
	{
		cout << "Sorry, you lose...you've been hanged." << endl;
		cout << "The word was : " << word << endl;
	}
	cin.ignore();
	cin.get();
}

void Hangman::convertToUpper()										//puts letters of the variable secretWord to uppercase
{
	int i = 0;
	string secretWord;
	while (secretWord[i]) {
		letter = secretWord[i];
		printf("%c", toupper(letter));
		i++;
	}
}