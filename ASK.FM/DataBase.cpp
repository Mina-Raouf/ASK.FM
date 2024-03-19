#include "DataBase.h"

DataBase::DataBase() {

	lastUserID = 0;
	lastMessageID = 0;

	ifstream usersFile("usersData.txt");

	if (usersFile.fail()) {
		cerr << "can't open file\n";
		return;
	}

	int ID;
	bool anonymousTalks;
	string handle, userName, password;

	while (usersFile >> ID >>anonymousTalks>> handle >> userName >> password) {
		users.push_back(User(ID,anonymousTalks, handle, userName, password));
		lastUserID = max(lastUserID, ID);
	}

	usersFile.close();


	ifstream parentMessagesFile("parentMessagesData.txt");

	if (parentMessagesFile.fail()) {
		cerr << "can't open file\n";
		return;
	}
	
	int parentID, from, to;
	bool anonymous;
	string question, answer;
	while (parentMessagesFile >> ID >> parentID >> from >> to>> anonymous) {
		getline(parentMessagesFile, question);
		getline(parentMessagesFile, question);
		getline(parentMessagesFile, answer);
		parentMessages.push_back(Message(ID, parentID, from, to, anonymous, question, answer));
		lastMessageID = max(lastMessageID, ID);
	}

	parentMessagesFile.close();

	ifstream childMessagesFile("childMessagesData.txt");

	if (childMessagesFile.fail()) {
		cerr << "can't open file\n";
		return;
	}


	while (childMessagesFile >> ID >> parentID >> from >> to >> anonymous) {
		getline(childMessagesFile, question);
		getline(childMessagesFile, question);
		getline(childMessagesFile, answer);
		childMessages.push_back(Message(ID, parentID, from, to, anonymous, question, answer));
		lastMessageID = max(lastMessageID, ID);
	}

	childMessagesFile.close();

}

void DataBase::addUser(bool anonymousTalks, string handle, string userName, string password) {
	users.push_back(User(++lastUserID, anonymousTalks, handle, userName, password));
}


vector<Message> DataBase::getUserMessages(int userID, bool type) {
	vector<Message>messages;
	for (int i = 0; i < parentMessages.size(); i++) {
		if (type == 1 && parentMessages[i].getTo() == userID) {
			messages.push_back(parentMessages[i]);
		}
		if (type == 0 && parentMessages[i].getFrom() == userID) {
			messages.push_back(parentMessages[i]);
		}
	}
	if (type == 0) {
		for (int i = 0; i < childMessages.size(); i++) {
			if ( childMessages[i].getFrom() == userID) {
				messages.push_back(childMessages[i]);
			}
		}
	}
	return messages;
}

vector<Message> DataBase::getChildMessages(int parentID) {
	vector<Message>messages;
	for (int i = 0; i < childMessages.size(); i++) {
		if (childMessages[i].getParentID()==parentID) {
			messages.push_back(childMessages[i]);
		}
	}
	return messages;
}

string DataBase::getUserHandle(int userID) {
	string handle = "";
	for (int i = 0; i < users.size(); i++) {
		if (users[i].getID() == userID) {
			handle = users[i].getHandle();
			break;
		}
	}
	return handle;
}

User DataBase::getUser(string userName, string password) {
	User user;
	for (int i = 0; i < users.size(); i++) {
		if (users[i].getUserName() == userName && users[i].getPassword() == password) {
			user = users[i];
			break;
		}
	}
	return user;
}

bool DataBase::findUser(int userID) {
	for (int i = 0; i < users.size(); i++) {
		if (users[i].getID() == userID) {
			return true;
		}
	}
	return false;
}

bool DataBase::findUser(string userName, string password) {
	for (int i = 0; i < users.size(); i++) {
		if (users[i].getUserName() == userName && users[i].getPassword() == password) {
			return true;
		}
	}
	return false;
}

bool DataBase::anonymousTalks(int userID) {
	bool AT = 0;
	for (int i = 0; i < users.size(); i++) {
		if (users[i].getID() == userID) {
			AT = users[i].getAnonymousTalks();
			break;
		}
	}
	return AT;
}

bool DataBase::findParentMessage(int ID) {
	bool found = false;
	for (int i = 0; i < parentMessages.size(); i++) {
		if (parentMessages[i].getID() == ID) {
			found = true;
			break;
		}
	}
	return found;
}

void DataBase::addMessage(Message message) {
	message.setID(++lastMessageID);
	if (message.getParentID() == 0) {
		parentMessages.push_back(message);
	}
	else {
		childMessages.push_back(message);
	}
}

bool DataBase::canAnswer(int userID, int questionID) {
	for (int i = 0; i < parentMessages.size(); i++) {
		if (parentMessages[i].getID() == questionID && parentMessages[i].getTo() == userID) {
			return true;
		}
	}

	for (int i = 0; i < childMessages.size(); i++) {
		if (childMessages[i].getID() == questionID && childMessages[i].getTo() == userID) {
			return true;
		}
	}

	return false;
}

bool DataBase::isAnswered(int questionID) {
	bool answered = false;
	for (int i = 0; i < parentMessages.size(); i++) {
		if (parentMessages[i].getID() == questionID) {
			if (parentMessages[i].getAnswer().size()) {
				answered = true;
			}
			break;
		}
	}

	for (int i = 0; i < childMessages.size(); i++) {
		if (childMessages[i].getID() == questionID) {
			if (childMessages[i].getAnswer().size()) {
				answered = true;
			}
			break;
		}
	}

	return answered;
}

void DataBase::update(int questionID, string answer) {
	for (int i = 0; i < parentMessages.size(); i++) {
		if (parentMessages[i].getID() == questionID) {
			parentMessages[i].setAnswer(answer);
			return;
		}
	}

	for (int i = 0; i < childMessages.size(); i++) {
		if (childMessages[i].getID() == questionID) {
			childMessages[i].setAnswer(answer);
			return;
		}
	}
}

bool DataBase::canDelete(int userID, int questionID) {
	for (int i = 0; i < parentMessages.size(); i++) {
		if (parentMessages[i].getID() == questionID) {
			if (parentMessages[i].getFrom() == userID || parentMessages[i].getTo() == userID) {
				return true;
			}
			
		}
	}

	for (int i = 0; i < childMessages.size(); i++) {
		if (childMessages[i].getID() == questionID) {
			if (childMessages[i].getFrom() == userID || childMessages[i].getTo() == userID) {
				return true;
			}
		}
	}

	return false;
}

void DataBase::deleteQuestion(int questionID) {
	vector<Message>newParentMessages;
	for (int i = 0; i < parentMessages.size(); i++) {
		if (parentMessages[i].getID() == questionID) {
			continue;
		}
		newParentMessages.push_back(parentMessages[i]);
	}

	vector<Message>newChildMessages;
	for (int i = 0; i < childMessages.size(); i++) {
		if (childMessages[i].getID() == questionID || childMessages[i].getParentID() == questionID) {
			continue;
		}
		newChildMessages.push_back(childMessages[i]);
	}
	parentMessages = newParentMessages;
	childMessages = newChildMessages;
}

void DataBase::showFeed() {

	for (int i = 0; i < parentMessages.size(); i++) {
		cout << "Question (" << parentMessages[i].getID() << ") from ";
		if (parentMessages[i].isAnonymous()) {
			cout << "Anonymous  ";
		}
		else {
			cout << getUserHandle(parentMessages[i].getFrom()) << " (" << parentMessages[i].getFrom() << ")";
		}

		cout<<" to "<<getUserHandle(parentMessages[i].getTo()) << " (" << parentMessages[i].getTo() << ") : ";

		cout << parentMessages[i].getQuestion() << '\n';
		if (parentMessages[i].getAnswer().size()) {
			cout << "Answer : " << parentMessages[i].getAnswer() << "\n";
		}
		else {
			cout << "\t - NOT ANSWERED YET -\n";
		}
		vector<Message>myChildMessages;
		myChildMessages = getChildMessages(parentMessages[i].getID());

		if (myChildMessages.size() == 0) {
			cout << '\n';
			continue;
		}

		cout << "Threads : \n";
		for (int j = 0; j < myChildMessages.size(); j++) {
			cout << "\tQuestion (" << myChildMessages[j].getID() << ") from ";
			if (myChildMessages[j].isAnonymous()) {
				cout << "Anonymous  ";
			}
			else {
				cout << getUserHandle(myChildMessages[j].getFrom()) << " (" << myChildMessages[j].getFrom() << ")";
			}

			cout << " to " << getUserHandle(childMessages[i].getTo()) << " (" << childMessages[i].getTo() << ") : ";

			cout << myChildMessages[j].getQuestion() << '\n';
			if (myChildMessages[j].getAnswer().size()) {
				cout << "\tAnswer : " << myChildMessages[j].getAnswer() << '\n';
			}
			else {
				cout << "\t- NOT ANSWERED YET -\n";
			}
		}
		cout << '\n';
	}
}
void DataBase::listSystemUsers() {

	for (int i = 0; i < users.size(); i++) {
		cout << "ID : " << users[i].getID() << "  Handle : " << users[i].getHandle() << '\n';
	}
}
DataBase::~DataBase() {

	ofstream usersFile("usersData.txt");

	if (usersFile.fail()) {
		cerr << "can't open file\n";
		return;
	}

	for (int i = 0; i < users.size(); i++) {

		usersFile 
			<< users[i].getID() << ' ' 
			<< users[i].getAnonymousTalks() << ' ' 
			<< users[i].getHandle() << ' ' 
			<< users[i].getUserName() << ' ' 
			<< users[i].getPassword() << '\n';
	}

	usersFile.close();

	ofstream parentMessagesFile("parentMessagesData.txt");

	if (parentMessagesFile.fail()) {
		cerr << "can't open file\n";
		return;
	}
	for (int i = 0; i < parentMessages.size(); i++) {

		parentMessagesFile
			<< parentMessages[i].getID() << ' '
			<< parentMessages[i].getParentID() << ' '
			<< parentMessages[i].getFrom() << ' '
			<< parentMessages[i].getTo() << ' ' 
			<< parentMessages[i].isAnonymous() << '\n'
			<< parentMessages[i].getQuestion() << '\n'
			<< parentMessages[i].getAnswer() << '\n';
	}

	parentMessagesFile.close();

	ofstream childMessagesFile("childMessagesData.txt");

	if (childMessagesFile.fail()) {
		cerr << "can't open file\n";
		return;
	}
	for (int i = 0; i < childMessages.size(); i++) {

		childMessagesFile
			<< childMessages[i].getID() << ' '
			<< childMessages[i].getParentID() << ' '
			<< childMessages[i].getFrom() << ' '
			<< childMessages[i].getTo() << ' '
			<< childMessages[i].isAnonymous() << '\n'
			<< childMessages[i].getQuestion() << '\n'
			<< childMessages[i].getAnswer() << '\n';
	}

	childMessagesFile.close();

}