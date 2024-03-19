#pragma once
#include<iostream>
using namespace std;

class Message {
	int ID, parentID, from, to;
	bool anonymous;
	string question, answer;
public:

	Message();

	Message(int ID, int parentID, int from, int to, bool anonymous, string question, string answer);

	void setID(int ID);

	int getID();

	void setParentID(int parentID);

	int getParentID();

	void setFrom(int from);

	int getFrom();

	void setTo(int to);

	int getTo();

	void setAnonymous(bool anonymous);

	bool isAnonymous();

	void setQuestion(string question);

	string getQuestion();

	void setAnswer(string answer);

	string getAnswer();
};
