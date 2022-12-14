#pragma once
#include "TrainingMode.h"
#include <string>

using namespace std;

class MatchTraining : public TrainingMode
{
public:
	static void startMatchTraining(int topicMode);
	static void printMenu();
	static void startTraining(int count);
	static bool checkTranslation(string ua, string en);
};
