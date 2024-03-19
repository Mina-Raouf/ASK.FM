#pragma once
#include "DataBase.h"

class CurrentUser {
	User user;
public:
	CurrentUser(string userName,string password);

	string getHandle();

	void printQuestionsToMe();

	void printQuestionsFromMe();

	void askQuestion(); 

	void answerQuestion();

	void deleteQuestoin();

};

bool validChoice(string choice);
