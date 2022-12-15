#pragma once
class ConsoleInterface
{
public:
	static void start();
	static void printMenu();	
	static int getInput(int min, int max);
	static void printAvailableTopics();
	static void printReturnHint();
};

