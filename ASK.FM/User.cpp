#include "User.h"

User::User() {
	ID =anonymousTalks= 0;
	handle = userName = password = "";
}

User::User(int ID, bool anonymousTalks, string handle, string userName, string password) {
	this->ID = ID;
	this->anonymousTalks = anonymousTalks;
	this->handle = handle;
	this->userName = userName;
	this->password = password;
}


void User::setID(int ID) {
	this->ID = ID;
}

int User::getID() {
	return ID;
}

void User::setHandle(string handle) {
	this->handle = handle;
}

string User::getHandle() {
	return handle;
}

void User::setUserName(string userName) {
	this->userName = userName;
}

string User::getUserName() {
	return userName;
}

void User::setPassword(string password) {
	this->password = password;
}

string User::getPassword() {
	return password;
}


void User::setAnonymousTalks(bool AT) {
	this->anonymousTalks = anonymousTalks;
}

bool User::getAnonymousTalks() {
	return anonymousTalks;
}