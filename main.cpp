#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <cmath>
#include <windows.h>
#include "personalInfo.h"
#include "fitnessInfo.h"
#include "dataStorage.h"
#include "function.h"
using namespace std;

int main() {
	cout << fixed << showpoint << setprecision(2);
	const int SIZE = 500;
	dataStorage staff[SIZE];
	int numData = 0, numData2 = 0, numAdd = 0, choice1 = 0, i = 0, index[SIZE];
	
	system("COLOR B");
	title();
	cout << "Welcome to Let's Get Fit!\nTo use this program you need to input 2 text file. First text file must contain USM staffs' staff IC, name and gender. Below are the format for first text file:\n";
	SetColor(15,0);
	cout << "\t\t\t------------------------------" << endl;
	cout << "\t\t\t(staff IC)tab(name)tab(gender)" << endl;
	cout << "\t\t\t..........tab......tab........" << endl;
	cout << "\t\t\t------------------------------" << endl << endl;
	SetColor(11,0);
	cout << "Second text file must contain the respective staffs' staff IC, weight and height. Below are the format for the second text file:\n";
	SetColor(15,0);
	cout << "\t\t\t--------------------------------" << endl;
	cout << "\t\t\t(staff IC)tab(weight)tab(height)" << endl;
	cout << "\t\t\t..........tab........tab........" << endl;
	cout << "\t\t\t--------------------------------" << endl << endl;
	SetColor(11,0);
	cout << "Format for each data input from text file:" << endl;
	SetColor(15,0);
	cout << "1  Name\t\tmax 31 characters long including space, no digit or punctuation mark (', -, @, ...)\n";
	cout << "2  Staff IC\t12 characters long, no alphabet or punctuation mark (', -, @, ...)\n";
	cout << "3  Gender\teither 'Male' or 'Female'\n";
	cout << "4  Weight\tmore than or equal to 25kg and less than 140\n";
	cout << "5  Height\tmore than or equal to 140cm and less than or equal to 210)\n";
	SetColor(11,0);
	system("pause");
	system("CLS");
	system("COLOR B");
	openFile(staff, numData, numData2);		//Call openFile function
	cout << fixed << showpoint << setprecision(2);
	sortName(staff, numData);		//Call sortName function
	for (int i = 0; i < numData; i++) {		//for-loop to calculate all data
		staff[i].calData();
	}
	
	do {
		system("COLOR B");
		mainMenu(choice1);		//Call mainMenu function
		while (cin.fail() || choice1 > 7 || choice1 <= 0) {	//Input validation
			SetColor(4,0);
			cout << "Invalid input! Please enter a valid choice: ";
			cin.clear();
			cin.ignore(INT_MAX, '\n');
			cin >> choice1;
			SetColor(11,0);
		}
		system("CLS");
		system("COLOR B");
		switch (choice1) {
		case 1: {displayInfo(staff, numData);		//Call displayInfo function
			break;
		}
		case 2: {addModHeader(staff, numData);		//Call addModHeader function
			sortName(staff, numData);		//Call sortName function
			break;
		}
		case 3: {searchInfo(staff, numData, index);		//Call searchInfo function
			break;
		}
		case 4: {overallInfo(staff, numData);		//Call overallInfo function
			break;
		}
		case 5: {targetInfo(staff, numData);		//Call targetInfo function
			break;
		}
		case 6:	{deleteInfo(staff, numData);		//Call deleteInfo function
			break;
		}
		case 7: {
			break;
		}
		}
	} while (choice1 != 7);
	system("CLS");
	system("COLOR B");
	title();
	closeFile(staff, numData);		//Output all data to a text file
	return 0;
}
