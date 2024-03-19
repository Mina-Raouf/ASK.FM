#pragma once
#include<iostream>
#include <fstream>
#include<vector>
#include<string>
#include "Message.h"
#include "User.h"
using namespace std;
class DataBase {

	vector<User>users;

	vector<Message>parentMessages;

	vector<Message>childMessages;

	int lastUserID, lastMessageID;

public:

	DataBase();

	void addUser(bool anonymousTalks,string handle,string userName,string password);

	vector<Message> getUserMessages(int userID, bool type);

	vector<Message> getChildMessages(int parentID);

	string getUserHandle(int userID);

	User getUser(string userName, string password);

	bool findUser(int userID);

	bool findUser(string userName,string password);

	bool anonymousTalks(int userID);

	bool findParentMessage(int ID);

	void addMessage(Message message);

	bool canAnswer(int userID, int questionID);

	bool isAnswered(int questionID);

	void update(int questionID, string answer);

	bool canDelete(int userID, int questionID);

	void deleteQuestion(int questionID);

	void showFeed();

	void listSystemUsers();

	~DataBase();
};
