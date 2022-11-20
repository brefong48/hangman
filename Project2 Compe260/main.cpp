#include "HangWord.h"

int main()
{
	Hangman obj;
	char choice;
	while (true) {
		obj.displayMenu();
		cin >> choice;

		if (choice == '1') {
			obj.play();
			obj.convertToUpper();
		}
		else if (choice == '2') {
			obj.readFromFile();
			obj.enterNewWords();
		}
		else if (choice == '3') {
			cout << "Thanks for playing!" << endl;
			break;
		}
	}
	system("pause");
};