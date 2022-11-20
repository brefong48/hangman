#include <iostream>
#include <vector>
#ifndef HangWord_H
#define HangWord_H

using namespace std;

class Hangman
{
public:
	void enterNewWords();
	void readFromFile();
	void setSecretWord(string word);
	string getSecretWord();
	void setWordLength(int length);
	int getWordLength();
	void displayMenu();
	void convertToUpper();
	bool isWin(char guess, string Word, string& secretWord);
	void play();
	Hangman();

protected:
	vector<string>wordList;

private:
	int attempts = 6;
	string secretWord;
	int wordLength;
	string word;
	int wrongGuesses;
	char letter;
	string guessWord;
};
#endif