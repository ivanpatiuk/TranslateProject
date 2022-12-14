#include <iostream>
#include <stdlib.h>
#include <Windows.h> 
#include "ConsoleInterface.h"
#include "TopicTraining.h"
#include "TranslationService.h"
#include "MatchTraining.h"

using namespace std;

void ConsoleInterface::printMenu() {
	system("CLS");
	cout << "--------------------------------------------------------------------------" << endl;
	cout << "| Виберіть опцію меню:                                                   |" << endl;
	cout << "| (1) Почати тренування з словами                                        |" << endl;
	cout << "| (2) Почати тренування з реченнями                                      |" << endl;
	cout << "| (3) Почати тренування на встановлення відповідності слів               |" << endl;
	cout << "| (4) Почати тренування на встановлення відповідності речень             |" << endl;
	cout << "| (5) Додати переклад                                                    |" << endl;
	cout << "| (6) Показати файл з перекладом                                         |" << endl;
	cout << "| (0) Завершити роботу                                                   |" << endl;
	cout << "--------------------------------------------------------------------------" << endl;
}

void ConsoleInterface::start(){
	SetConsoleCP(1251); 
	SetConsoleOutputCP(1251); 
	int input; 
	do {
		printMenu();
		input = getInput(0, 6); 
		switch (input) {
		case 1: 
			TopicTraining::startTopicTraining(0);
			break;
		case 2:
			TopicTraining::startTopicTraining(1);
			break;
		case 3:
			MatchTraining::startMatchTraining(0);
			break;
		case 4:
			MatchTraining::startMatchTraining(1);
			break;
		case 5:
			TranslationService::addTranslation();
			break;		
		case 6:
			TranslationService::showTranslation();
			break;
		case 0: 
			exit(0);
		}
	} while (true);

}

int ConsoleInterface::getInput(int min, int max) {
	int input; // введене число
	do {
		cout << "Введіть опцію: "; cin >> input;
		if (min <= input && input <= max) { // якщо введено в межах [min,max], повернути введене число
			return input;
		}
		else { // в іншому випадку продовжити і вивести повідомлення
			cout << "Такої опції меню немає. Спробуйте ще раз." << endl;
		}
	} while (true);
}