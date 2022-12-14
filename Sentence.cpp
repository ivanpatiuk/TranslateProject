#include "Sentence.h"
#include <string>

using namespace std;

string Sentence::getUaTranslation() {
	return uaTranslation;
}
string Sentence::getEnTranslation() {
	return enTranslation;
}

void Sentence::setUaTranslation(string uaTranslation) {
	this->uaTranslation = uaTranslation;
}
void Sentence::setEnTranslation(string enTranslation) {
	this->enTranslation = enTranslation;
}