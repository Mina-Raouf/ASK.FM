#pragma once
#include<iostream>
using namespace std;
class User {
	int ID;
	bool anonymousTalks;
	string handle, userName, password;
public:

	User();

	User(int ID, bool anonymousTalks, string handle, string userName, string password);

	void setID(int ID);

	int getID();

	void setHandle(string handle);

	string getHandle();

	void setUserName(string userName);

	string getUserName();

	void setPassword(std::string password);

	string getPassword();

	void setAnonymousTalks(bool AT);

	bool getAnonymousTalks();

};