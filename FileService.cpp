#include "FileService.h"
#include <vector>
#include <fstream>
#include <iostream>

using namespace std;

vector<Sentence> FileService::loadFile(int topicMode, string topic) {
	vector<Sentence> vector;
	topic = topicMode == 0 ? topic + "_words.txt" : topic + "_sentences.txt";
	ifstream file{ topic };
	if (!file) {
		cout << "Такого файлу не існує" << endl;
		exit(1);
	}
	string word;
	while (getline(file, word)){
		vector.push_back(Sentence{ word.substr(0,word.find('=')) ,word.substr(word.find('=') + 1) });
	}
	file.close();
	return vector;
}

void FileService::addTranslation(int topicMode, string topic, string ua, string en) {
	ofstream outfile;
	if (!outfile) {
		cout << "Такого файлу не існує" << endl;
		exit(1);
	}
	topic = topicMode == 0 ? topic + "_words.txt" : topic + "_sentences.txt";
	outfile.open(topic, ios_base::app); // append instead of overwrite
	outfile << endl << ua << "=" << en;
	outfile.close();
}
