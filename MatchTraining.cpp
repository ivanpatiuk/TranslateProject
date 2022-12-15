#include "MatchTraining.h"
#include <iostream>
#include "ConsoleInterface.h"
#include "FileService.h"
#include <vector>
#include <conio.h>
#include <algorithm>
#include <iomanip>
#include <random>
#include <chrono>

using namespace std;

static vector<Sentence> sentences;

void MatchTraining::printMenu() {
	system("CLS");
	cout << "--------------------------------------------------------------------------" << endl;
	cout << "| � ����� ����� ���������� ��� ������� ���������� ���������� �����- |" << endl;
	cout << "| ���� ���.                                                             |" << endl;
	cout << "|                                                                        |" << endl;
	ConsoleInterface::printAvailableTopics();
	cout << "|                                                                        |" << endl;
	ConsoleInterface::printReturnHint();
	cout << "--------------------------------------------------------------------------" << endl;
}

void MatchTraining::startMatchTraining(int topicMode) {
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

void MatchTraining::startTraining(int sentenceCount) {
	string input;
	vector<string> uaTranslation{};
	vector<string> enTranslation{};
	int longest = 0;
	for (int i = 0; i < sentenceCount; ++i) {
		if (sentences.at(i).getUaTranslation().length() > longest) {
			longest = sentences.at(i).getUaTranslation().length();
		}
		uaTranslation.push_back(sentences.at(i).getUaTranslation());
		enTranslation.push_back(sentences.at(i).getEnTranslation());
	}
	shuffle(begin(uaTranslation), end(uaTranslation), default_random_engine(chrono::system_clock::now().time_since_epoch().count()));
	shuffle(begin(enTranslation), end(enTranslation), default_random_engine(chrono::system_clock::now().time_since_epoch().count()*31));

	vector<int> answers{};
	int answerInput;
	char approve;
	do {
		system("CLS");
		cout << setw(longest) << left << "UA" << "     EN" << endl;
		for (int i = 0; i < sentenceCount; ++i) {
			cout << i << ": " << setw(longest) << left << uaTranslation.at(i) << " - " << i << ": " << enTranslation.at(i) << endl;
		}
		vector<int> notApprovedAnswers{};
		for (int i = 0; i < sentenceCount; ++i) {
			cout << "������ [EN:] ����� ���������� ��� [UA: " << i << "]: ";
			cin >> answerInput;
			notApprovedAnswers.push_back(answerInput);
		}
		cout << "ϳ��������? (y/n): ";
		cin >> approve;
		if (approve == 'y' || approve == 'Y') {
			answers = notApprovedAnswers;
			break;
		}
	} while (true);
	int correctAnswersCount = checkAllTranslation(uaTranslation, enTranslation, answers);
	cout << "���������: " << 100.0 * correctAnswersCount / sentenceCount << "% ���������� ��������" << endl;
	cout << "������ ���� ��� ������ ��� �����������" << endl;
	_getch();
}

bool MatchTraining::checkTranslation(string ua, string en) {
	for (int i = 0; i < sentences.size(); ++i) {
		if (sentences.at(i).getUaTranslation() == ua) {
			if (sentences.at(i).getEnTranslation() == en) {
				return true;
			}
			return false;
		}
	}
	return false;
}

int MatchTraining::checkAllTranslation(vector<string> uaTranslation, vector<string> enTranslation, vector<int> answers) {
	system("CLS");
	int correctAnswersCount = 0;
	for (int i = 0; i < uaTranslation.size(); ++i) {
		if (checkTranslation(uaTranslation.at(i), enTranslation.at(answers.at(i)))) {
			correctAnswersCount++;
		}
		else {
			cout << "����������� ����������: " << uaTranslation.at(i) << " - " << enTranslation.at(answers.at(i)) << endl;
		}
	}
	return correctAnswersCount;
}

