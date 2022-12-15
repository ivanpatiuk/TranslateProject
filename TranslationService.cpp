#include "TranslationService.h"
#include <string>
#include <iostream>
#include <conio.h>
#include "FileService.h"
#include "ConsoleInterface.h"

using namespace std;

void TranslationService::addTranslation() {
	system("CLS");
	string ua;
	string en;
	string topic;
	int translationType;
	cout << "--------------------------------------------------------------------------" << endl;
	ConsoleInterface::printAvailableTopics();
	cout << "--------------------------------------------------------------------------" << endl;
	cout << "Введіть назву розділу на англійській з великої букви: "; cin >> topic;
	cout << "Виберіть тип перекладу: " << endl;
	cout << "(0) Слово" << endl;
	cout << "(1) Речення" << endl;
	translationType = ConsoleInterface::getInput(0, 1);
	cout << "Введіть український переклад: "; getline(cin >> ws, ua);
	cout << "Введіть англійський переклад: "; getline(cin >> ws, en);
	FileService::addTranslation(translationType, topic, ua, en);
}

void TranslationService::showTranslation() {
	system("CLS");
	vector<Sentence> vector;
	string topic;
	int translationType;
	cout << "--------------------------------------------------------------------------" << endl;
	ConsoleInterface::printAvailableTopics();
	cout << "|                                                                        |" << endl;
	ConsoleInterface::printReturnHint();
	cout << "--------------------------------------------------------------------------" << endl;
	cout << "Введіть назву розділу на англійській з великої букви: ";
	cin >> topic; 
	if (topic == "B") {
		return;
	}
	if (topic == "S") {
		exit(0);
	}
	system("CLS");
	cout << "Виберіть тип перекладу: " << endl;
	cout << "(0) Слово" << endl;
	cout << "(1) Речення" << endl;
	translationType = ConsoleInterface::getInput(0, 1);
	vector = FileService::loadFile(translationType, topic);
	system("CLS");
	for (int i = 0; i < vector.size(); ++i) {
		cout << vector.at(i).getUaTranslation() << " - " << vector.at(i).getEnTranslation() << endl;
	}
	cout << "Нажміть будь яку кнопку для продовження" << endl;
	_getch();
}
