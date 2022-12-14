#pragma once
#include <string>

using namespace std;
class Sentence
{
private:
	string uaTranslation;
	string enTranslation;

public:
	Sentence(string uaTranslation, string enTranslation) {
		this->uaTranslation = uaTranslation;
		this->enTranslation = enTranslation;
	}

	string getUaTranslation();
	string getEnTranslation();
	
	void setUaTranslation(string uaTranslation);
	void setEnTranslation(string enTranslation);
};

