#include "TopicTraining.h"
#include <iostream>
#include "ConsoleInterface.h"
#include "FileService.h"
#include <vector>
#include <conio.h>
#include <algorithm>
#include <random>

using namespace std;

static vector<Sentence> sentences;

void TopicTraining::printMenu() {
	system("CLS");
	cout << "--------------------------------------------------------------------------" << endl;
	cout << "| У цьому режимі тренування вам потрібно перекладати слова чи речення    |" << endl;
	cout << "| певного розділу. Для продовження введіть назву розділу з великої букви.|" << endl;
	cout << "|                                                                        |" << endl;
	cout << "| Доступні розділи:                                                      |" << endl;
	cout << "| (1) Transport                                                          |" << endl;
	cout << "| (2) Fruits                                                             |" << endl;
	cout << "| (3) Vegetables                                                         |" << endl;
	cout << "|                                                                        |" << endl;
	cout << "| Щоб повернутися до попереднього меню введіть B                         |" << endl;
	cout << "| Щоб вийти з програми введіть S                                         |" << endl;
	cout << "--------------------------------------------------------------------------" << endl;
}

void TopicTraining::startTopicTraining(int topicMode) {
	printMenu(); 
	string input; 
	int wordsCount;
	do {
		printMenu();
		cout << "Введіть назву розділу (з великої букви): "; 
		do {
			cin >> input; 
			if (input == "B") {
				return;
			}
			if (input == "S") {
				exit(0);
			}
			sentences = FileService::loadFile(topicMode, input);
			if (sentences.size() == 0) {
				cout << "Файл пустий. Спробуйте ще раз: ";
			}
		} while (sentences.size() == 0);
		auto rng = std::default_random_engine{};
		shuffle(begin(sentences), end(sentences), rng);

		system("CLS");
		cout << "Введіть кількість слів/речень для перекладу в межах від 1 до " << sentences.size() << endl;
		wordsCount = ConsoleInterface::getInput(1, sentences.size());
		startTraining(wordsCount);
	} while (true);
}

void TopicTraining::startTraining(int wordsCount) {
	cout << "Оберіть спосіб перекладу: \n(1) з англійської на українську\n(2) з української на англійську\n";
	int translationMode = ConsoleInterface::getInput(1, 2);
	string input;
	int correctInputsCount = 0;
	for (int i = 0; i < wordsCount; ++i) {
		TopicTraining::printHint(translationMode, sentences.at(i));
		getline(cin >> ws, input);
		if (TopicTraining::checkTranslation(translationMode, input, sentences.at(i))) {
			correctInputsCount++;
		}
	}
	system("CLS");
	cout << "Результат: " << 100.0 * correctInputsCount / wordsCount << "% правильних відповідей" << endl;
	cout << "Нажміть будь яку кнопку для продовження" << endl;
	_getch();
}

bool TopicTraining::checkTranslation(int translationMode, string input, Sentence sentence) {
	if (translationMode == 1) {
		if (input == sentence.getUaTranslation()) {
			cout << "Правильно! Нажміть будь яку кнопку для продовження" << endl;
			_getch();
			return true;
		}
		else {
			printResult(sentence.getUaTranslation(), input);
			cout << "Нажміть будь яку кнопку для продовження" << endl; 
			_getch();
			return false;
		}
	}
	if (input == sentence.getEnTranslation()) {
		cout << "Правильно! Нажміть будь яку кнопку для продовження" << endl;
		_getch();
		return true;
	}
	else {
		printResult(sentence.getEnTranslation(), input);
		cout << "Нажміть будь яку кнопку для продовження" << endl;
		_getch();
		return false;
	}
}

void TopicTraining::printResult(string expected, string actual) {
	cout << "Неправильно" << endl;
	cout << "Очікувалося: " << expected << endl;
	cout << "Введено: " << actual << endl;
}

void TopicTraining::printHint(int translationMode, Sentence sentence) {
	system("CLS");
	cout << "Перекладіть  ";
	if (translationMode == 1) {
		cout << "з англійської на українську:\n'" << sentence.getEnTranslation() << "'\n";
	}
	else {
		cout << "з української на англійську:\n'" << sentence.getUaTranslation() << "'\n";
	}
	cout << "Введіть переклад: ";
}
