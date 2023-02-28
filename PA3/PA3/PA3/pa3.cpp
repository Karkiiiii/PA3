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

int main() {
	VendingMachine machine;
	int choice;
	do {
		system("cls");
		choice = machine.menu();
		if (choice == -1) {
			exit(3);
		}
		while (choice == -2) {
			choice = machine.menu();
			if (choice == -1) {
				exit(3);
			}
		}
		choice--;
		machine.vend(choice);
	} while (choice < NUMBER_OF_ITEMS && choice >= 0);

	return 0;
}