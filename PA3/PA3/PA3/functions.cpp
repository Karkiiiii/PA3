//Author: Lucius Karki
//Class : CSI 240-04
// Assignment : PA3
// Date Assigned : Febuary 14th 
// Due Date : Febuary 28th, 2023 at 2:30
// Description : Creates a vending machine that has a public interface and a secret private one
// that is accessed with a password. Has many functions associated with running the machine.
// Stores all machine data once owner of the machine shuts it down.
// Certification of Authenticity :
//I certify that this is entirely my own work, except where I have given fully documented
// references to the work of others.I understand the definition and
// consequences of plagiarism and acknowledge that the assessor of this assignment
// may, for the purpose of assessing this assignment :
// -Reproduce this assignment and provide a copy to another member of
// academic staff; and / or
// - Communicate a copy of this assignment to a plagiarism checking service
// (which may then retain a copy of this assignment on its database for
// the purpose of future plagiarism checking)

#include "VendingMachine.h"
#include "item.h"

/*     Pre:  None
*     Post:  None
*  Purpose:  Default constructor
*********************************************************/
VendingMachine::VendingMachine() {
	int i;
	ifstream fin;
	int numOfItems;
	string name;

	fin.open(DATA_FILE);

	if (fin.fail()) { //if the data file doesn't exist
		mMoney = 5;
		mPassword = "password";
		for (i = 0; i < NUMBER_OF_ITEMS; i++) {
			cout << "Please enter the name of item #" << i+1 << ": ";
			getline(cin, name);
			mItems[i].mName = name;
			mItems[i].mQuantity = 20;
			cout << "What is the price of this item? ";
			cin >> mItems[i].mPrice;
			cin.ignore();
		}
		system("cls");
	}
	else { //if the data file does exist
		fin >> numOfItems >> mMoney >> mPassword;
		for (i = 0; i < NUMBER_OF_ITEMS; i++) {
			fin.ignore();
			getline(fin, name);
			mItems[i].mName = name;
			fin>>mItems[i].mQuantity;
			fin>>mItems[i].mPrice;
		}
	}
}

/*     Pre:  None
*     Post:  None
*  Purpose:  Destructor of VendingMachine Objects
*********************************************************/
VendingMachine::~VendingMachine() {

}

/*     Pre:  None
*     Post:  Amount of money in the vending machine
*  Purpose:  To return amount of money in the vending machine
*********************************************************/
double VendingMachine::getMoney() {
	return mMoney;
}

/*     Pre:  None
*     Post:  Password of the machine
*  Purpose:  To return the password of the machine
*********************************************************/
string VendingMachine::getPassword() {
	return mPassword;
}

/*     Pre:  The new amount of money
*     Post:  None
*  Purpose:	 To change the amount of money in the vending machine
*********************************************************/
void VendingMachine::setMoney(double newMoney) {
	mMoney = newMoney;
}

/*     Pre:  The new password
*     Post:  None
*  Purpose:  To change the password of the vending machine
*********************************************************/
void VendingMachine::setPassword(string newPassword) {
	mPassword = newPassword;
}

/*     Pre:  None
*     Post:  Returns -1 if the shutdown sequence has been selected
               and -2 if the revert to regular interface sequence has been selected.
*  Purpose:  To display and complete the admin actions.
*********************************************************/
int VendingMachine::adminMenu() {
	int choice, changeNum, changeQuantity, num;
	double changePrice;
	string changeName, changePassword;
	do {
		system("cls");
		cout << "Welcome to the owner menu!" << endl;
		cout << "Your choices are:" << endl << endl;
		cout << "1. Change an item's name" << endl;
		cout << "2. Change an item's price" << endl;
		cout << "3. Change an item's quantity" << endl;
		cout << "4. Change the vending machine's admin password" << endl;
		cout << "5. Check the total money accumulated" << endl;
		cout << "6. Restock the machine" << endl;
		cout << "7. Shutdown the machine" << endl;
		cout << "8. Exit the owner menu" << endl;
		cout << endl << endl;
		cout << "What would you like to do? ";
		cin >> choice;

		switch (choice) {
		case 1: {//name change
			cout << "What item would you like to change the name of? ";
			cin >> changeNum;
			while (changeNum > 4 || changeNum < 1) {
				cout << "Please enter a valid number of an item to change";
				cin >> changeNum;
			}
			changeNum--;
			cout << "What would you like to change the name to? ";
			cin.ignore();
			getline(cin, changeName);
			mItems[changeNum].mName = changeName;
		}
			  break;
		case 2: {//price change
			cout << "What item would you like to change the price of? ";
			cin >> changeNum;
			while (changeNum > 4 || changeNum < 1) {
				cout << "Please enter a valid number of an item to change";
				cin >> changeNum;
			}
			changeNum--;
			cout << "What would you like to change the price to? ";
			cin >> changePrice;
			while (changePrice < 0) {
				cout << "Please enter a valid price (Above 0): ";
				cin >> changePrice;
			}
			mItems[changeNum].mPrice = changePrice;
		}
			  break;
		case 3: {//quantity change
			cout << "What item would you like to change the quantity of? ";
			cin >> changeNum;
			while (changeNum > 4 || changeNum < 1) {
				cout << "Please enter a valid number of an item to change";
				cin >> changeNum;
			}
			changeNum--;
			cout << "What would you like to change the name to? ";
			cin >> changeQuantity;
			while (changeQuantity > 20 || changeQuantity < 0) {
				cout << "Please enter a valid quantity (Between 0 and 20): ";
				cin >> changeQuantity;
			}
			mItems[changeNum].mQuantity = changeQuantity;
		}
			  break;
		case 4: {//password change
			cout << "What would you like to change the password of the vending machine to? ";
			cin >> changePassword;
			mPassword = changePassword;
		}
			  break;
		case 5: {//accumulated money
			cout << "The total money in the system currently is " << mMoney << endl;
			cout << "However, the machine started with 5 dollars in it so the total earned money is " << mMoney - 5 << endl;
		}
			  break;
		case 6:restock();
			break;
		case 7: {
			shutdown();
			num = -1;
			return num;
		}
			  break;
		default: {
			num = -2;
			system("cls");
		}
		}
	} while (choice < 7 && choice>0);
	return num;
}

/*     Pre:  None
*     Post:  None
*  Purpose:  To set the amount of money to the orginal starting value of the machine which is 5
*********************************************************/
void VendingMachine::collectMoney() {
	mMoney = 5;
}

/*     Pre:  A String of user input that needs to be tested on if it is a numeric string or not
*     Post:  True if the string is a number and false if the string is not a number
*  Purpose:  To check if the string passed in is a number
*********************************************************/
bool isNumber(string line) {
	bool isNum = true;
	for (int i = 0; i < line.length(); i++) {//checks each character of the string
		if (!isdigit(line[i])) {
			isNum=false;
		}
	}
	return isNum;
}

/*     Pre:  None
*     Post:  The selection the user chose
*  Purpose:  To output a menu and return the choice the user made
*********************************************************/
int VendingMachine::menu() {
	string choice;
	int num;
	cout << "Welcome to the vending machine!" << endl;
	cout << "Your choices are: " << endl << endl;
	for (int i = 0; i < NUMBER_OF_ITEMS; i++) {//lists the items and their prices
		cout << i+1 << ". " << mItems[i].mName << " " << mItems[i].mPrice << endl; 
	}
	cout << endl;
	cout << "What would you like to choose? ";
	cin >> choice;
	if (choice == mPassword) {
		num = adminMenu();
	}
	else if (isNumber(choice)) {
		num = stoi(choice);
		while (num < 1 || num>4) {//catches improper input
			cout << "Please enter a valid selection: ";
			cin >> choice;
			if (choice == mPassword) {
				num = adminMenu();
			}
			else
				if (isNumber(choice))
					num = stoi(choice);
				else
					num = 0;
		}
	}
	return num;
}

/*     Pre:  None
*     Post:  None
*  Purpose:  To set the quantities of the items in the vending machine to the max number of 20
*********************************************************/
void VendingMachine::restock() {
	for (int i = 0; i < NUMBER_OF_ITEMS; i++) {
		mItems[i].mQuantity = 20;
	}
}

/*     Pre:  None
*     Post:  None
*  Purpose:  To output all the data of the vending machine into a text file so it can be read when started again
*********************************************************/
void VendingMachine::shutdown() {
	fstream fout;

	fout.open(DATA_FILE, ios::out);
	if (fout.fail()) {
		cout << "failed to open " << DATA_FILE << endl;
		exit(1);
	}

	fout << NUMBER_OF_ITEMS << " " << mMoney << " " << mPassword << endl;
	for (int i = 0; i < NUMBER_OF_ITEMS; i++) {
		fout << mItems[i].mName << endl;
		fout << mItems[i].mQuantity << " " << mItems[i].mPrice << endl;
	}

	fout.close();
}

/*     Pre:  A choice of item the user has made to buy
*     Post:  None
*  Purpose:  To make sure the actual vending of the item happens, payment, change in quantity of items,
             and making sure that there are safegaurds from people underpaying
*********************************************************/
void VendingMachine::vend(int choice) {
	double pay, change;

	if (mItems[choice].mQuantity <= 0) {
		cout << "That item is out of stock" << endl;
		return;
	}

	cout << "How much are you paying? ";
	cin >> pay;
	change = pay - mItems[choice].mPrice;
	if (change < 0) {//if user doesn't enter enough money
		cout << "you did not enter enough money to pay for the item"<<endl;
		system("pause");
		return;
	}
	if (change > mMoney) {//if the machine does have enough money to give change
		cout<<"The machine does not have enough money to give you change for that amount of money."<<endl;
		system("pause");
		return;
	}
	cout << "Thank you for your service, your change is " << change << endl;
	mMoney -= change;
	mMoney += mItems[choice].mPrice;
	mItems[choice].mQuantity--;
	system("pause");
}