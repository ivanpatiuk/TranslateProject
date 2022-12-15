#pragma once
#include "TrainingMode.h"
#include <string>
#include <vector>

using namespace std;

class MatchTraining : public TrainingMode
{
public:
	static void startMatchTraining(int topicMode);
	static void printMenu();
	static void startTraining(int count);
	static bool checkTranslation(string ua, string en);
	static int checkAllTranslation(vector<string> uaTranslation, vector<string> enTranslation, vector<int> answers);
};
