#include "System.h"

void Run() {
	while (true) {
		cout << "1. Sign in\n"
			<< "2. Sign up\n"
			<< "choose a number 1-2 : ";
		string choice;
		cin >> choice;
		if (choice == "1") {
			SignIn();
		}
		else if (choice == "2") {
			SignUp();
		}
		else {
			cout << "Invalid choice.\n";
		}
	}
}

void SignIn() {
	string userName, password;
	while (true) {
		cout << "Enter username : ";
		cin >> userName;
		cout << "Enter password : ";
		cin >> password;
		DataBase DB;
		if (DB.findUser(userName, password)) {
			break;
		}
		
		cout << "Invalid username or password.\n";
	}
	system("cls");
	MainMenu(CurrentUser(userName,password));
}

void SignUp() {
	string handle, userName, password;
	bool anonymousTalks = false;
	cout << "Note : your data mustn't contain spaces .\n";
	cout << "Enter your handle : ";
	cin >> handle;
	cout << "Enter username : ";
	cin >> userName;
	cout << "Enter password : ";
	cin >> password;
	while (true) {
		cout << "Do you want anonymous talks ? (Y/N)\n";
		string choice;
		cin >> choice;
		if (choice == "Y" || choice == "y") {
			anonymousTalks = true;
			break;
		}
		if (choice == "N" || choice == "n") {
			anonymousTalks = false;
			break;
		}

		cout << "Invalid choice .\n";
	}
	DataBase DB;
	DB.addUser(anonymousTalks,handle, userName, password);
	system("cls");
}

void MainMenu(CurrentUser user) {
	string choice;
	while (true) {
		cout << "Menu : \t\t Handle : "<<user.getHandle()<<"\n"
			<< "1. Print Questions from me . \n"
			<< "2. Print Questions to me .\n"
			<< "3. Ask a Question .\n"
			<< "4. Answer a Question .\n"
			<< "5. Delete a Question .\n"
			<< "6. Show Feed . \n"
			<< "7. List system users .\n"
			<< "8. Logout .\n\n"
			<< "Enter a choice 1 - 8 : ";
		cin >> choice;
		cout << '\n';
		if (choice == "1") {
			user.printQuestionsFromMe();
		}
		else if (choice == "2") {
			user.printQuestionsToMe();
		}
		else if (choice == "3") {
			user.askQuestion();
		}
		else if (choice == "4") {
			user.answerQuestion();
		}
		else if (choice == "5") {
			user.deleteQuestoin();
		}
		else if (choice == "6") {
			DataBase DB;
			DB.showFeed();
		}
		else if (choice == "7") {
			DataBase DB;
			DB.listSystemUsers();
		}
		else if (choice == "8") {
			break;
		}
		else {
			cout << "Invalid choice .\n";
		}
		cout << '\n';
	}
	system("cls");
}
