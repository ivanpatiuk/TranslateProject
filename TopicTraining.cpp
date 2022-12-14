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
	cout << "| � ����� ����� ���������� ��� ������� ����������� ����� �� �������    |" << endl;
	cout << "| ������� ������. ��� ����������� ������ ����� ������ � ������ �����.|" << endl;
	cout << "|                                                                        |" << endl;
	cout << "| ������� ������:                                                      |" << endl;
	cout << "| (1) Transport                                                          |" << endl;
	cout << "| (2) Fruits                                                             |" << endl;
	cout << "| (3) Vegetables                                                         |" << endl;
	cout << "|                                                                        |" << endl;
	cout << "| ��� ����������� �� ������������ ���� ������ B                         |" << endl;
	cout << "| ��� ����� � �������� ������ S                                         |" << endl;
	cout << "--------------------------------------------------------------------------" << endl;
}

void TopicTraining::startTopicTraining(int topicMode) {
	printMenu(); 
	string input; 
	int wordsCount;
	do {
		printMenu();
		cout << "������ ����� ������ (� ������ �����): "; 
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
				cout << "���� ������. ��������� �� ���: ";
			}
		} while (sentences.size() == 0);
		auto rng = std::default_random_engine{};
		shuffle(begin(sentences), end(sentences), rng);

		system("CLS");
		cout << "������ ������� ���/������ ��� ��������� � ����� �� 1 �� " << sentences.size() << endl;
		wordsCount = ConsoleInterface::getInput(1, sentences.size());
		startTraining(wordsCount);
	} while (true);
}

void TopicTraining::startTraining(int wordsCount) {
	cout << "������ ����� ���������: \n(1) � ��������� �� ���������\n(2) � ��������� �� ���������\n";
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
	cout << "���������: " << 100.0 * correctInputsCount / wordsCount << "% ���������� ��������" << endl;
	cout << "������ ���� ��� ������ ��� �����������" << endl;
	_getch();
}

bool TopicTraining::checkTranslation(int translationMode, string input, Sentence sentence) {
	if (translationMode == 1) {
		if (input == sentence.getUaTranslation()) {
			cout << "���������! ������ ���� ��� ������ ��� �����������" << endl;
			_getch();
			return true;
		}
		else {
			printResult(sentence.getUaTranslation(), input);
			cout << "������ ���� ��� ������ ��� �����������" << endl; 
			_getch();
			return false;
		}
	}
	if (input == sentence.getEnTranslation()) {
		cout << "���������! ������ ���� ��� ������ ��� �����������" << endl;
		_getch();
		return true;
	}
	else {
		printResult(sentence.getEnTranslation(), input);
		cout << "������ ���� ��� ������ ��� �����������" << endl;
		_getch();
		return false;
	}
}

void TopicTraining::printResult(string expected, string actual) {
	cout << "�����������" << endl;
	cout << "�����������: " << expected << endl;
	cout << "�������: " << actual << endl;
}

void TopicTraining::printHint(int translationMode, Sentence sentence) {
	system("CLS");
	cout << "����������  ";
	if (translationMode == 1) {
		cout << "� ��������� �� ���������:\n'" << sentence.getEnTranslation() << "'\n";
	}
	else {
		cout << "� ��������� �� ���������:\n'" << sentence.getUaTranslation() << "'\n";
	}
	cout << "������ ��������: ";
}
