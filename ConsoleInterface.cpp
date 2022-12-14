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
	cout << "| ������� ����� ����:                                                   |" << endl;
	cout << "| (1) ������ ���������� � �������                                        |" << endl;
	cout << "| (2) ������ ���������� � ���������                                      |" << endl;
	cout << "| (3) ������ ���������� �� ������������ ���������� ���               |" << endl;
	cout << "| (4) ������ ���������� �� ������������ ���������� ������             |" << endl;
	cout << "| (5) ������ ��������                                                    |" << endl;
	cout << "| (6) �������� ���� � ����������                                         |" << endl;
	cout << "| (0) ��������� ������                                                   |" << endl;
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
	int input; // ������� �����
	do {
		cout << "������ �����: "; cin >> input;
		if (min <= input && input <= max) { // ���� ������� � ����� [min,max], ��������� ������� �����
			return input;
		}
		else { // � ������ ������� ���������� � ������� �����������
			cout << "���� ����� ���� ����. ��������� �� ���." << endl;
		}
	} while (true);
}