#pragma once
#include "Sentence.h"
#include <vector>

using namespace std;

class FileService
{
public:
	static vector<Sentence> loadFile(int topicMode, string topic);
	static void addTranslation(int topicMode, string topic, string ua, string en);
};

