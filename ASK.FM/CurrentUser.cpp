#include "CurrentUser.h"

CurrentUser::CurrentUser(string userName,string password) {
	DataBase DB;
	this->user = DB.getUser(userName, password);
}

string CurrentUser::getHandle() {
	return user.getHandle();
}

void CurrentUser::printQuestionsToMe() {
	DataBase DB;
	vector<Message>myParentMessages;
	myParentMessages = DB.getUserMessages(user.getID(), 1);
	for (int i = 0; i < myParentMessages.size(); i++) {
		cout << "Question (" << myParentMessages[i].getID() << ") from ";
		if (myParentMessages[i].isAnonymous()) {
			cout << "Anonymous : ";
		}
		else {
			cout << DB.getUserHandle(myParentMessages[i].getFrom()) << " (" << myParentMessages[i].getFrom() << ") : ";
		}
		cout << myParentMessages[i].getQuestion() << '\n';
		if (myParentMessages[i].getAnswer().size()) {
			cout << "Answer : "<< myParentMessages[i].getAnswer() << "\n";
		}
		else {
			cout << "\t - NOT ANSWERED YET -\n";
		}
		vector<Message>myChildMessages;
		myChildMessages = DB.getChildMessages(myParentMessages[i].getID());

		if (myChildMessages.size() == 0) {
			cout << '\n';
			continue;
		}
			
		cout << "Threads : \n";
		for (int j = 0; j < myChildMessages.size(); j++) {
			cout << "\tQuestion (" << myChildMessages[j].getID() << ") from ";
			if (myChildMessages[j].isAnonymous()) {
				cout << "Anonymous : ";
			}
			else {
				cout << DB.getUserHandle(myChildMessages[j].getFrom()) << " (" << myChildMessages[j].getFrom() << ") : ";
			}
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

void CurrentUser::printQuestionsFromMe() {
	DataBase DB;
	vector<Message>myMessages;
	myMessages = DB.getUserMessages(user.getID(),0);
	for (int i = 0; i < myMessages.size(); i++) {
		if (myMessages[i].isAnonymous()) {
			cout << " - AQ -  ";
		}
		else {
			cout << "\t ";
		}
		cout << "Question (" << myMessages[i].getID() << ") to " << DB.getUserHandle(myMessages[i].getTo()) << " (" << myMessages[i].getTo() << ") : "<<myMessages[i].getQuestion()<<"\n";
		if (myMessages[i].getAnswer().size()) {
			cout << "\t Answer : " << myMessages[i].getAnswer() << "\n\n";
		}
		else {
			cout << "\t - NOT ANSWERED YET -\n\n";
		}
	}
}

void CurrentUser::askQuestion() {
	DataBase DB;
	Message newMessage;
	int ID;
	newMessage.setFrom(user.getID());
	while (true) {
		cout << "Enter user ID or -1 to cancel : ";
		string choice;
		cin >> choice;
		if (choice=="-1") {
			return;
		}
		if (!validChoice(choice)) {
			cout << "Invalid choice\n";
			continue;
		}
		ID = stoi(choice);
		if (DB.findUser(ID) == 0) {
			cout << "Invalid user ID\n";
		}
		else {
			newMessage.setTo(ID);
			break;
		}
	}
	bool AT = DB.anonymousTalks(ID);
	if (AT == false) {
		cout << "Note : this user doesn't allow to talk anonymously .\n";
	}
	else {
		string choice;
		while (true) {
			cout << "do you want to ask anonymously ? (Y/N) : ";
			cin >> choice;
			if (choice == "Y" || choice == "y") {
				newMessage.setAnonymous(1);
				break;
			}
			if (choice == "N" || choice == "n") {
				newMessage.setAnonymous(0);
				break;
			}
			cout << "Invalid choice \n";
		}
	}
	int parentID = 0;
	while (true) {
		cout << "Enter question ID for thread question or -1 for a new question : ";
		string choice;
		cin >> choice;
		if (choice == "-1") {
			break;
		}
		if (!validChoice(choice)) {
			cout << "Invalid choice\n";
			continue;
		}
		parentID = stoi(choice);
		if (DB.findParentMessage(parentID) == 0) {
			cout << "Invalid question ID\n";
		}
		else {
			break;
		}
	}
	newMessage.setParentID(parentID);
	cout << "Enter question text : ";
	cin.ignore();
	string question;
	getline(cin, question);
	newMessage.setQuestion(question);
	DB.addMessage(newMessage);
	cout << "Question sent successfully.\n";
}

void CurrentUser::answerQuestion() {
	
	DataBase DB;
	int questionID;
	while (true) {
		cout << "Enter Question ID or -1 to cancel : ";
		string choice;
		cin >> choice;
		if (choice == "-1") {
			return;
		}
		if (!validChoice(choice)) {
			cout << "Invalid choice\n";
			continue;
		}
		questionID = stoi(choice);
		if (DB.canAnswer(user.getID(), questionID)) {
			break;
		}
		cout << "Question doesn't exist or doesn't belong to you .\n";
	}
	if (DB.isAnswered(questionID)) {
		while (true) {
			cout << "Question is already answered do you want to override ? (Y/N)\n";
			string choice;
			cin >> choice;
			if (choice == "N" or choice == "n") {
				return;
			}
			if (choice == "Y" or choice == "y") {
				break;
			}
			cout << "Invalid choice.\n";
		}
	}
	cout << "Enter answer text : ";
	cin.ignore();
	string answer;
	getline(cin, answer);
	DB.update(questionID, answer);
	cout << "Question answered successfully.\n";
}
void CurrentUser::deleteQuestoin() {

	DataBase DB;
	int questionID;
	while (true) {
		cout << "Enter Question ID or -1 to cancel : ";
		string choice;
		cin >> choice;
		if (choice == "-1") {
			return;
		}
		if (!validChoice(choice)) {
			cout << "Invalid choice\n";
			continue;
		}
		questionID = stoi(choice);
		if (DB.canDelete(user.getID(), questionID)) {
			break;
		}
		cout << "Question doesn't exist or doesn't belong to you .\n";
	}
	DB.deleteQuestion(questionID);
	cout << "Question deleted successfully.\n";
}

bool validChoice(string choice) {
	for (int i = 0; i < choice.size(); i++) {
		if (choice[i] < '0' or choice[i]>'9') {
			return false;
		}
	}
	return true;
}