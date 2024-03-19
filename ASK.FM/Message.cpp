#include "Message.h"

Message::Message() {
	ID = parentID = from = to = anonymous = 0;
	question = answer = "";
}

Message::Message(int ID, int parentID, int from, int to, bool anonymous, string question, string answer) {
	this->ID = ID;
	this->parentID = parentID;
	this->from = from;
	this->to = to;
	this->anonymous = anonymous;
	this->question = question;
	this->answer = answer;
}


void Message::setID(int ID) {
	this->ID = ID;
}

int Message::getID() {
	return ID;
}

void Message::setParentID(int parentID) {
	this->parentID = parentID;
}

int Message::getParentID() {
	return parentID;
}

void Message::setFrom(int from) {
	this->from = from;
}

int Message::getFrom() {
	return from;
}

void Message::setTo(int to) {
	this->to = to;
}

int Message::getTo() {
	return to;
}

void Message::setAnonymous(bool anonymous) {
	this->anonymous = anonymous;
}

bool Message::isAnonymous() {
	return anonymous;
}

void Message::setQuestion(string question) {
	this->question = question;
}

string Message::getQuestion() {
	return question;
}

void Message::setAnswer(string answer) {
	this->answer = answer;
}

string Message::getAnswer() {
	return answer;
}