#pragma once
#include"TrainingMode.h"
#include "Sentence.h"
class TopicTraining: public TrainingMode
{
public:
	static void printMenu();
	static void startTraining(int count);
	static void startTopicTraining(int topicMode);
	static void printResult(string expected, string actual);
	static void printHint(int input, Sentence sentence);
	static bool checkTranslation(int intInput, string input, Sentence sentence);
};

