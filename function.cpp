#include "function.h"

void SetColor(int f = 16, int b = 0) {			    //Function use to set colour of the word
    unsigned short ForeColor = f + 16 * b;
    HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hCon,ForeColor);
}

void title() {
	SetColor(3,0);
	cout << "======================================================================================================================================================================================" << endl;
	cout << "||                                                                               Let's Get Fit!                                                                                     ||" << endl;
	cout << "======================================================================================================================================================================================" << endl;
	SetColor(11,0);
}

void openFile(dataStorage staff[], int& numData, int& numData2) {
	const int SIZE = 500;
	ifstream personalInfo, fitnessInfo;
	bool found = false;
	string fileName, fileName2, fileExt = ".txt", name, gender, inputIC , weight, height, temp = "", lostData[SIZE];
	long long int tempIC[SIZE];
	double tempW[SIZE], tempH[SIZE];
	int lostData2[SIZE], numLD2 = 0, numLD = 0;
	title();
	cout << "Enter the file name that contain personal info for every USM Staff: ";
	getline(cin, fileName);		//Enter text file name specified by user to input USM staff personal info
	fileName += fileExt;
	personalInfo.open(fileName.c_str(), ios::in);
	while (!personalInfo) { 		//while-loop to test valid text file name
		SetColor(4,0);
		cout << "Personal info file not found! Please enter again: ";
		getline(cin, fileName);
		fileName += fileExt;
		personalInfo.open(fileName.c_str(), ios::in);
		SetColor(11,0);
	}
	while (!personalInfo.eof()) {		//while-loop to test end-of-file to input data from text file
		if (temp != "") {
			inputIC = temp;
		}
		else if(temp == "") {
			personalInfo >> inputIC;
		}
		temp = "";
		if (validIC(inputIC) == false) {		//Invalid IC
			if (inputIC == "Male" || inputIC == "Female") {		//Missing IC and name
				continue;
			}
			else if(validName(inputIC) == true) {		//Missing IC but getting name
				temp = inputIC;
				inputIC = "111111111111";
			}
			else {		//Invalid IC
				inputIC = "111111111111";
			}
			personalInfo.ignore();
			getline(personalInfo, name, '\n');
			gender = name.substr(name.find_last_of("\t ",name.length()));
    		gender = gender.erase(0, gender.find_first_not_of("\t "));
    		name = name.substr(0,name.find_last_of("\t "));
    		name = name.erase(name.find_last_not_of("\t ") +1, name.length());
    		if (temp != "" && validName(temp) == true) {		//Getting name process
				name = temp + " " + name;
			}
    		if(gender != "Male" && gender !="Female") {		//Invalid IC, valid name but missing gender
    			name += " " + gender;
    			gender = "M/F?";
    			lostData[numLD] = name;
    			numLD++;
    			found = true;
			}
			else{
				lostData[numLD] = name;
    			numLD++;
    			found = true;
			}
			if (validName(name) == false){
				continue;
			}
			staff[numData].setPersonalData(name, gender, realNum(inputIC));
			temp = "";
			numData++;
		}
		else{		//Valid IC
			personalInfo.ignore();
			personalInfo >> name;
			if (name == "Male" || name == "Female") {		//Valid IC but missing name
				gender = name;
				name = "STAFF NO NAME";
				temp = "";
				lostData[numLD] = inputIC;
    			numLD++;
    			found = true;
			}
			else if (validIC(name) == true) {		//Valid IC but missing name and gender
				temp = name;
				name = "STAFF NO NAME";
				if ((realNum(inputIC) % 10) % 2 == 1) {
					gender = "Male";
				}
				else if ((realNum(inputIC) % 10) % 2 == 0) {
					gender = "Female";
				}
				lostData[numLD] = inputIC;
    			numLD++;
    			found = true;
			}
			else {		//Valid IC
				getline(personalInfo, temp, '\n');
				gender = temp.substr(temp.find_last_of("\t ",temp.length()));
	    		gender = gender.erase(0, gender.find_first_not_of("\t "));
	    		temp = temp.substr(0,temp.find_last_of("\t "));
	    		name = name + temp;
	    		name = name.erase(name.find_last_not_of("\t ") + 1, name.length());
				if(gender != "Male" && gender !="Female") {		//Valid IC and name but invalid gender
					name += " " + gender;
					if ((realNum(inputIC) % 10) % 2 == 1) {
						gender = "Male";
					}
					else if ((realNum(inputIC) % 10) % 2 == 0) {
						gender = "Female";
					}
				}
				if (validName(name) == false){		//Valid IC but invalid name
					name = "STAFF NO NAME";
		    		lostData[numLD] = inputIC;
	    			numLD++;
	    			found = true;
				}
				temp = "";
			}
			staff[numData].setPersonalData(name, gender, realNum(inputIC));
			numData++;
		}
	}
	personalInfo.close();
	system("CLS");
	if (found == true) {		//Display the staff with incomplete information input from first file
		title();
		cout << "The following staff input from the file " << fileName << " has incomplete Name/Staff IC information:\n";
		cout << "=================================================\n\tNAME\t\t\tSTAFF IC\n=================================================\n\n";
		for (int i = 0; i < numLD; i++) {
			if (validIC(lostData[i]) == true) {
				SetColor(4,0);
				cout << i + 1 << "\t" << "STAFF NO NAME";
				cout << setw(10);
				if (realNum(lostData[i]) / 1000000000 == 0) {
				cout << "\t000" << realNum(lostData[i]);
				}
				else if (realNum(lostData[i]) / 10000000000 == 0) {
					cout << "\t00" << realNum(lostData[i]);
				}
				else if (realNum(lostData[i]) / 100000000000 == 0) {
					cout << "\t0" << realNum(lostData[i]);
				}
				else if (realNum(lostData[i]) / 1000000000000 == 0) {
					cout << "\t" << realNum(lostData[i]);
				}
			}
			else {
				SetColor(4,0);
				cout << i + 1 << "\t" << lostData[i];
				cout << setw(23 - (lostData[i].size())) << "\t111111111111";
			}
			cout << endl << endl;
		}
		SetColor(11,0);
		cout << "Do check on 'DISPLAY ALL STAFF INFORMATION' and search by name(STAFF NO NAME) / staff IC(111111111111) in 'ADD/MODIFY STAFF INFORMATION' to add information." << endl << endl;
		system("pause");
		system("CLS");
	}
	title();
	cout << "Personal info input completed. Enter the file name that contain fitness info for every USM Staff: ";
	getline(cin, fileName2);		//Enter text file name specified by user to input USM staff fitness info
	fileName2 += fileExt;
	fitnessInfo.open(fileName2.c_str(), ios::in);
	while (!fitnessInfo) {		//while loop to test valid text file name
		SetColor(4,0);
		cout << "Fitness info file not found! Please enter again: ";
		getline(cin, fileName2);
		fileName2 += fileExt;
		fitnessInfo.open(fileName2.c_str(), ios::in);
		SetColor(11,0);
	}
	temp = "";
	found = false;
	numLD = 0;
	while (!fitnessInfo.eof()) {		//while-loop to test end-of-file to input all data from text file
		if (temp != ""){
			inputIC= temp;
		}
		else if(temp == "") {
			fitnessInfo >> inputIC;
		}
		temp = "";
		if (validIC(inputIC) == false) {		//Invalid IC
			fitnessInfo >> weight;
			if(realNum(weight) >= 25 &&  realNum(weight) < 140) {		//Invalid IC but valid weight
				fitnessInfo >> height;
				if(validIC(height) == true) {		//Invalid IC, valid weight but missing height
					temp = height;
					continue; 
				}
				else{		//Invalid IC, valid weight but invalid height
					continue;
				}
			}
			else if(validIC(weight) == true) {		//Invalid IC and missing weight and height
				temp = weight;
				continue;
			}
			else if (realNum(weight) >= 140 &&  realNum(weight) <= 210) {		//Invalid IC, missing weight but valid height
				continue;
			}
			else{
				fitnessInfo >> height;
				if (validIC(height) == true) {		//Invalid IC and weight and missing height
					temp = height;
					continue;
				}
				else {
					continue;
				}
			}
		}
		else if(realNum(inputIC) >= 25 && realNum(inputIC) < 140) {		//Missing IC, getting weight
			fitnessInfo >> height;
			if (validIC(height) == true) {		//Missing IC, getting weight but missing height
				temp = height;
				continue;
			}
			else {		//Missing IC, getting weight but invalid height
				continue;
			}
		}
		else if (realNum(inputIC) >= 140 && realNum(inputIC) <= 210) {		//Missing IC and weight but getting height
			continue;
		}
		else{		//Valid IC
			fitnessInfo >> weight;
			if (realNum(weight) >= 25 &&  realNum(weight) < 140){		//Valid IC and weight
				fitnessInfo >> height;
				{
					if (realNum(height) >= 140 &&  realNum(height) <= 210) {		//Valid IC, weight and height
						temp = "";
					}
					else if (validIC(height) == true) {		//Valid IC and weight but missing height
						temp = height;
						height = "0000";
						lostData[numLD] = inputIC;
		    			numLD++;
		    			found = true;
					}
					else{		//Valid IC and weight but invalid height
						height = "0000";
						temp = "";
						lostData[numLD] = inputIC;
		    			numLD++;
		    			found = true;
					}
				}
			}
			else if (validIC(weight) == true) {		//Valid IC, missing weight and height
				temp = weight;
				weight = "0000";
				height = "0000";
				lostData[numLD] = inputIC;
		    	numLD++;
		    	found = true;
			}
			else if(realNum(weight) >= 140 &&  realNum(weight) <= 210) {		//Valid IC, missing weight and height
				height = weight;
				weight = "0000";
				temp = "";
				lostData[numLD] = inputIC;
		    	numLD++;
		    	found = true;
			}
			else{		//Valid IC, invalid weight
				weight = "0000";
				fitnessInfo >> height;
				{
					if (realNum(height) >= 140 &&  realNum(height) <= 210) {		//Valid IC, invalid weight and valid height
						temp = "";
						lostData[numLD] = inputIC;
				    	numLD++;
				    	found = true;
					}
					else if (validIC(height) == true) {		//Valid IC, invalid weight but missing height
						temp = height;
						height = "0000";
						lostData[numLD] = inputIC;
				    	numLD++;
				    	found = true;
					}
					else{	//IC valid, invalid weight and height
						height = "0000";
						temp = "";
						lostData[numLD] = inputIC;
				    	numLD++;
				    	found = true;
					}
				}
			}
			tempIC[numData2] = realNum(inputIC);
			tempW[numData2] = static_cast<double>(realNum(weight));
			tempH[numData2] = static_cast<double>(realNum(height));
			numData2++;
		}
	}
	fitnessInfo.close();
	system("CLS");
	title();
	cout << "Fitness info input completed." << endl; 
	if (found == true) {		//Display the staff with incomplete information input from second file
		cout << "The following staff input from the file " << fileName2 << " has incomplete either weight,height or both information:\n";
		cout << "====================================================\n\tNAME\t\t\t\tSTAFF IC\n====================================================\n\n";
		SetColor(4,0);
		for (int i = 0; i < numLD; i++) {
			for (int j = 0; j < numData; j++){
				if (realNum(lostData[i]) == staff[j].getStaffIC()){
					cout << i + 1 << "\t" << staff[j].getName();
					cout << setw(31 - (staff[j].getName().size()));
					if (realNum(lostData[i]) / 1000000000 == 0) {
					cout << "\t000" << realNum(lostData[i]);
					}
					else if (realNum(lostData[i]) / 10000000000 == 0) {
						cout << "\t00" << realNum(lostData[i]);
					}
					else if (realNum(lostData[i]) / 100000000000 == 0) {
						cout << "\t0" << realNum(lostData[i]);
					}
					else if (realNum(lostData[i]) / 1000000000000 == 0) {
						cout << "\t" << realNum(lostData[i]);
					}
					cout << endl << endl;
				}
			}
		}
		SetColor(11,0);
		cout << "Do check on 'DISPLAY ALL STAFF INFORMATION' and search by name/staff IC/value 0 for weight and height in 'ADD/MODIFY STAFF INFORMATION' to add information." << endl << endl;
		system("pause");
	}
	for (int i = 0; i < numData; i++) {		//To store relevant weight and height information according to staff IC
		if (staff[i].getStaffIC() == tempIC[i]) {
			staff[i].setFitnessData(tempW[i], tempH[i]);
		}
		else {
			found = false;
			for (int j = 0; j < max(numData, numData2); j++) {
				if (staff[i].getStaffIC() == tempIC[j]) {
					found = true;
					staff[i].setFitnessData(tempW[j], tempH[j]);
					break;
				}
			}
			if (found == false) {
				lostData2[numLD2] = i;
				numLD2++;
			}
		}
	}
	if(numData > numData2){		//Display staff with incomplete weight and height information from second file
		cout << "\nThere are missing weight and height information for the following staff:\n====================================================\n";
		cout << "\tNAME\t\t\t\tSTAFF IC\n====================================================\n\n";
		for (int i = 0; i < numLD2; i++) {
			SetColor(4,0);
			cout << i + 1 << "\t" << staff[lostData2[i]].getName();
			cout << setw(31 - staff[lostData2[i]].getName().size());
			if (staff[lostData2[i]].getStaffIC() / 1000000000 == 0) {
				cout << "\t000" << staff[lostData2[i]].getStaffIC();
			}
			else if (staff[lostData2[i]].getStaffIC() / 10000000000 == 0) {
				cout << "\t00" << staff[lostData2[i]].getStaffIC();
			}
			else if (staff[lostData2[i]].getStaffIC() / 100000000000 == 0) {
				cout << "\t0" << staff[lostData2[i]].getStaffIC();
			}
			else if (staff[lostData2[i]].getStaffIC()/ 1000000000000 == 0) {
				cout << "\t" << staff[lostData2[i]].getStaffIC();
			}
			cout << endl << endl;
			}
		SetColor(11,0);
		cout << "Do check on 'DISPLAY ALL STAFF INFORMATION' and search by name/staff IC/value 0 for weight and height in 'ADD/MODIFY STAFF INFORMATION' to add information." << endl << endl;
	}
	int num = 0;
	if (numData < numData2) {		//Display staff with important personal information missing from first file
		cout << "\nThere are fitness information input but lost of its staff IC in the file " << fileName << ".\n\n";
		for (int i = 0; i < numData2; i++){
			SetColor(4,0);
			found = false;
			for (int j = 0; j < numData; j++){
				if(tempIC[i] == staff[j].getStaffIC()){
					found = true;
					break;
				}
			}
			if (found == false){
				cout << num + 1;
				if (tempIC[i] / 1000000000 == 0) {
					cout << "\t000" << tempIC[i];
				}
				else if (tempIC[i] / 10000000000 == 0) {
					cout << "\t00" << tempIC[i];
				}
				else if (tempIC[i] / 100000000000 == 0) {
					cout << "\t0" << tempIC[i];
				}
				else if (tempIC[i] / 1000000000000 == 0) {
					cout << "\t" << tempIC[i];
				}
				cout << endl << endl;
				if ((tempIC[i] % 10) % 2 == 1) {
					gender = "Male";
				}
				else if ((tempIC[i] % 10) % 2 == 0) {
					gender = "Female";
				}
				staff[numData+num].setPersonalData("STAFF NO NAME", gender, tempIC[i]);
				staff[numData+num].setFitnessData(tempW[i], tempH[i]);
				num++;
			}
		}
		numData += num + 1;
		SetColor(11,0);
		cout << "Do check on 'DISPLAY ALL STAFF INFORMATION' and search by name 'STAFF NO NAME'/staff IC in 'ADD/MODIFY STAFF INFORMATION' to add information." << endl << endl;
	}
	cout << "Opening LET'S GET FIT program..." << endl;
	system("pause");
	system("CLS");
}

void sortName(dataStorage staff[], int& numData){		//Sort all the staff names according to alphabetical order
	string name1, name2, tempG;
	long long int tempIC = 0;
	double tempW = 0, tempH = 0;
	for (int i = 1; i < numData; i++){
		name1 = staff[i-1].getName();
		name2 = staff[i].getName();
		int j = 0;
		while (name1[j] == name2[j]){
			j++;
		}
		if(name1[j] > name2[j]){
			tempIC = staff[i-1].getStaffIC();
			tempG = staff[i-1].getGender();
			tempW = staff[i-1].getWeight();
			tempH = staff[i-1].getHeight();
			staff[i-1].setPersonalData(name2, staff[i].getGender(), staff[i].getStaffIC());
			staff[i-1].setFitnessData(staff[i].getWeight(), staff[i].getHeight());
			staff[i].setPersonalData(name1, tempG, tempIC);
			staff[i].setFitnessData(tempW, tempH);
			i = 0;
		}
	}
}

void mainMenu(int& choice1) {
	title();
	cout << "MENU" << endl;
	cout << "1  DISPLAY ALL STAFF INFORMATION" << endl;
	cout << "2  ADD/MODIFY STAFF INFORMATION" << endl;
	cout << "3  SEARCH STAFF INFORMATION (WITH BMI DISTRIBUTION)" << endl;
	cout << "4  OVERALL USM STAFF BMI DISTRIBUTION" << endl;
	cout << "5  CALORIES TARGET INFORMATION" << endl;
	cout << "6  DELETE STAFF INFORMATION" << endl;
	cout << "7  EXIT" << endl;
	cout << "Choice: ";
	cin >> choice1;
}

long long int realNum(string str) {		//Convert a string-type number to int
	long long int n = 0;
	for (char i : str){
		if (i >= '0' && i <= '9') {
			n = n * 10 + (i - '0');
		}
	}
	return n;
}

bool validIC (string inputIC) {
	for (int j = 0; inputIC[j] != '\0'; j++){		//Input validation
		if (inputIC.length() != 12 || isalpha(inputIC[j]) != 0 || ispunct(inputIC[j]) != 0) {
			return false;
		}
	}
	return true;
}

bool validName (string name) {
	for (int j = 0; name[j] != '\0'; j++){		//Input validation
		if (name.length() >= 32 || isdigit(name[j]) != 0 || ispunct(name[j]) != 0) {
			return false;
		}
	}
	return true;
}

void displayInfo(dataStorage staff[], int numData) {		//Display all staff information in a table
	title();
	string line = "======================================================================================================================================================================================";
	cout << "                                                                         DISPLAY ALL STAFF INFORMATION" << endl;
	cout << line << "\n\n";
	cout << setw(8) << "NAME\t\t\t\tSTAFF IC\tGENDER\t\tAGE\tDATE OF BIRTH\tWEIGHT(kg)\tHEIGHT(cm)\tBMI\t\tBMR\t\tRMR\t\tWEIGHT CATEGORY" << endl;
	cout << "\t\t\t\t\t\t\t\t\t(dd/mm/yy)" << endl;
	cout << line << "\n";
	cout << "TOTAL NUMBER OF USM STAFF: " << numData << endl;
	cout << line << "\n\n";
	for (int i = 0; i < numData; i++) {
		cout << staff[i].getName();
		cout << setw(31 - staff[i].getName().size());
		if (staff[i].getStaffIC() / 1000000000 == 0) {
			cout << "\t000" << staff[i].getStaffIC();
		}
		else if (staff[i].getStaffIC() / 10000000000 == 0) {
			cout << "\t00" << staff[i].getStaffIC();
		}
		else if (staff[i].getStaffIC() / 100000000000 == 0) {
			cout << "\t0" << staff[i].getStaffIC();
		}
		else if (staff[i].getStaffIC() / 1000000000000 == 0) {
			cout << "\t" << staff[i].getStaffIC();
		}
		cout << "\t" << staff[i].getGender();
		cout << "\t\t" << staff[i].getAge();
		cout << "\t" << staff[i].getDD();
		cout << "/" << staff[i].getMM();
		cout << "/" << staff[i].getYYYY();
		cout << "\t" << staff[i].getWeight();
		cout << "\t\t" << staff[i].getHeight();
		cout << "\t\t" << staff[i].getBMI();
		cout << "\t\t" << staff[i].getBMR();
		cout << "\t\t" << staff[i].getRMR();
		cout << "\t\t" << staff[i].getWeightCategory() << endl << endl;
		if ((i+1)%15 == 0){
			cout << "Press to go to next page . . . " << endl;
			system("pause");
			system("CLS");
			title();
			cout << "                                                                         DISPLAY ALL STAFF INFORMATION" << endl;
			cout << line << "\n\n";
			cout << setw(8) << "NAME\t\t\t\tSTAFF IC\tGENDER\t\tAGE\tDATE OF BIRTH\tWEIGHT(kg)\tHEIGHT(cm)\tBMI\t\tBMR\t\tRMR\t\tWEIGHT CATEGORY" << endl;
			cout << "\t\t\t\t\t\t\t\t\t(dd/mm/yy)" << endl;
			cout << line << "\n\n";
		}
	}
	cout << line << "\n";
	system("pause");
	system("CLS");
	title();
	cout << "Back to main programme..." << endl;
	system("pause");
	system("CLS");
}

void addModHeader(dataStorage staff[], int& numData) {
	int choice = 0;
	title();
	cout << "                                                                         ADD/MODIFY STAFF INFORMATION" << endl;
	cout << "======================================================================================================================================================================================\n\n";
	cout << "1  Add new staff information\n2  Edit staff information\nChoice: ";
	cin >> choice;
	while (cin.fail() || choice > 2 || choice <= 0) {		//Input validation
		SetColor(4,0);
		cout << "Invalid input! Please enter a valid choice: ";
		cin.clear();
		cin.ignore(INT_MAX, '\n');
		cin >> choice;
		SetColor(11,0);
	}
	system("CLS");
	title();
	switch (choice) {
	case 1: {addInfo(staff, numData);		//Call addInfo function
		break;
	}
	case 2: {modInfoMenu(staff, numData);		//Call modInfo function
		break;
	}
	}
	system("CLS");
	title();
	cout << "Back to main programme..." << endl;
	system("pause");
	system("CLS");
}

void addInfo(dataStorage staff[], int& numData) {		//Add staff information and store
	int oldTotal = numData, newTotal = 0, numAdd = 0, j = 1;
	string name, gender, inputIC;
	string line = "======================================================================================================================================================================================";
	long long int IC = 0;
	double weight = 0, height = 0;
	cout << "                                                                             ADD STAFF INFORMATION" << endl;
	cout << line << "\n\n";
	cout << "Number of staff to be added: ";
	cin >> numAdd;
	while (cin.fail() || numAdd <= 0) {		//Input validation
		SetColor(4,0);
		cout << "Invalid input! Please enter a valid number: ";
		cin.clear();
		cin.ignore(INT_MAX, '\n');
		cin >> numAdd;
		SetColor(11,0);
	}
	newTotal = numData + numAdd;		//Calculate new total number of staff
	for (numData; numData < newTotal; numData++){		//for-loop to allow user to add the staff information one-by-one
		cout << "=======\nStaff " << (j) << "\n=======";
		cout << "\nName (max 31 characters including space): ";
		cin.ignore(INT_MAX, '\n');
		getline(cin, name, '\n');
		for (int i = 0, j = 0; i < numData || name[j] != '\0'; i++, j++) {
			if (name.length() >= 32 || isdigit(name[j]) != 0 || ispunct(name[j]) != 0) {		//Input validation
				SetColor(4,0);
				cout << "Invalid name format input! Please enter a valid name: ";
				cin.clear();
				getline(cin, name);
				i = -1;
				j = -1;
				SetColor(11,0);
			}
			else if (staff[i].getName() == name) {		//Test if name entered is repeated
				SetColor(4,0);
				cout << "This name belongs to another staff, please re-enter a valid name: ";
				cin.clear();
				getline(cin, name);
				i = -1;
				j = -1;
				SetColor(11,0);
			}
		}
		cout << "\nStaff IC(without '-'): ";
		getline(cin, inputIC);
		for (int i = 0, j = 0; i < numData || inputIC[j] != '\0'; i++, j++) {		//Input validation
			if (inputIC.length() != 12 || isalpha(inputIC[j]) != 0 || ispunct(inputIC[j]) != 0) {
				SetColor(4,0);
				cout << "Invalid IC! Please enter a valid Staff IC: ";
				cin.clear();
				getline(cin, inputIC);
				i = -1;
				j = -1;
				SetColor(11,0);
			}
			else if (staff[i].getStaffIC() == realNum(inputIC)) {		//Test if staff IC entered is repeated
				SetColor(4,0);
				cout << "This IC belongs to another staff, please re-enter a valid staff IC:";
				cin.clear();
				getline(cin, inputIC);
				i = -1;
				j = -1;
				SetColor(11,0);
			}
		}
		IC = realNum(inputIC);
		if ((IC % 10) % 2 == 1) {		//Use staff IC to get gender
			gender = "Male";
		}
		else if ((IC % 10) % 2 == 0) {
			gender = "Female";
		}
		cout << "\nWeight(kg): ";
		cin >> weight;
		while (cin.fail() || weight < 25 || weight >=140) {		//Input validation
			SetColor(4,0);
			cout << "Invalid input! Please enter a valid weight(kg): ";
			cin.clear();
			cin.ignore(INT_MAX, '\n');
			cin >> weight;
			SetColor(11,0);
		}
		cout << "\nHeight(cm): ";
		cin >> height;
		while (cin.fail() || height < 140 || height > 210) {		//Input validation
			SetColor(4,0);
			cout << "Invalid input! Please enter a valid height(cm): ";
			cin.clear();
			cin.ignore(INT_MAX, '\n');
			cin >> height;
			SetColor(11,0);
		}
		cout << endl;
		staff[numData].setPersonalData(name, gender, IC);		//Set all information into programme
		staff[numData].setFitnessData(weight, height);
		staff[numData].calData();
		j++;
	}
}
void modInfoMenu(dataStorage staff[], int& numData) {
	int choice = 0;
	string name, inputIC;
	string line = "======================================================================================================================================================================================";
	double weight = 0, height = 0;
	bool found = false;
	cout << "                                                                          MODIFY STAFF INFORMATION" << endl;
	cout << line << "\n\n";
	cout << "Modify by searching:\n1  Name\n2  Staff IC\n3  Weight\n4  Height\nChoice: ";
	cin >> choice;
	while (cin.fail() || choice > 4 || choice <= 0)	{		//Input validation
		SetColor(4,0);
		cout << "Invalid input! Please enter a valid choice: ";
		cin.clear();
		cin.ignore(INT_MAX, '\n');
		cin >> choice;
		SetColor(11,0);
	}
	system("CLS");
	title();
	cout << "                                                                          MODIFY STAFF INFORMATION" << endl;
	cout << line << "\n\n";
	switch (choice) {
	case 1: {
		cout << "\nSearch Name (max 31 characters including blank space): ";
		cin.clear();
		cin.ignore(INT_MAX, '\n');
		getline(cin, name);
		while (found == false) {
			for (int j = 0; name[j] != '\0'; j++) {
				if (name.length() >= 32 || isdigit(name[j]) != 0 || ispunct(name[j]) != 0) {		//Input validation
					SetColor(4,0);
					cout << "Invalid name format input! Please enter a valid name: ";
					cin.clear();
					getline(cin, name);
					j = -1;
					SetColor(11,0);
				}
			}
			for (int i = 0; i < numData; i++) {
				if (staff[i].getName() == name) {		//Find the specific staff using name
					found = true;
					modInfo(staff, numData, i);
					break;
				}
			}
			if (found == false) {
				SetColor(4,0);
				cout << "Name not found, please re-enter a valid name: ";
				cin.clear();
				getline(cin, name);
				SetColor(11,0);
			}
		}
		break;
	}
	case 2: {
		cout << "\nSearch Staff IC(without '-'): ";
		cin.ignore(INT_MAX, '\n');
		getline(cin, inputIC);
		while (found == false) {
			for (int j = 0; inputIC[j] != '\0'; j++) {		//Input validation
				if (inputIC.length() != 12 || isalpha(inputIC[j]) != 0 || ispunct(inputIC[j]) != 0) {
					SetColor(4,0);
					cout << "Invalid IC! Please enter a valid Staff IC: ";
					cin.clear();
					getline(cin, inputIC);
					j = -1;
					SetColor(11,0);
				}
			}
			for (int i = 0; i < numData; i++) {
				if (staff[i].getStaffIC() == realNum(inputIC)) {		//Find the specific staff using staff IC
					found = true;
					modInfo(staff, numData, i);
					break;
				}
			}
			if (found == false) {
				SetColor(4,0);
				cout << "IC not found, please re-enter a valid IC: ";
				cin.clear();
				getline(cin, inputIC);
				SetColor(11,0);
			}
		}
		break;
	}
	case 3: {
		cout << "\nSearch Weight: ";
		cin.ignore(INT_MAX, '\n');
		cin >> weight;
		while (found == false) {
			while (cin.fail() || (weight > 0 && weight < 25) || weight >= 140 || weight < 0) {		//Input validation
				SetColor(4,0);
				cout << "Invalid input! Please enter a valid weight: ";
				cin.clear();
				cin.ignore(INT_MAX, '\n');
				cin >> weight;
				SetColor(11,0);
			}
			int j = 1;
			for (int i = 0; i < numData; i++) {
				if (staff[i].getWeight() == weight) {		//Find the specific staff using staff IC
					cout << "\nLoading Staff " << j << " information..." << endl;
					system("pause");
					found = true;
					modInfo(staff, numData, i);
					j++;
				}
			}
			if (found == false) {
				SetColor(4,0);
				cout << "Weight not found, please re-enter a valid weight: ";
				cin.clear();
				cin >> weight;
				SetColor(11,0);
			}
		}
		break;
	}
	case 4: {
		cout << "\nSearch Height: ";
		cin.ignore(INT_MAX, '\n');
		cin >> height;
		while (found == false) {
			while (cin.fail() || (height > 0 && height < 140) || height > 210 || height < 0) {		//Input validation
				SetColor(4,0);
				cout << "\nInvalid input! Please enter a valid height: ";
				cin.clear();
				cin.ignore(INT_MAX, '\n');
				cin >> height;
				SetColor(11,0);
			}
			int j = 1;
			for (int i = 0; i < numData; i++) {
				if (staff[i].getHeight() == height) {		//Find the specific staff using staff IC
					cout << "Loading Staff " << j << " information..." << endl;
					system("pause");
					found = true;
					modInfo(staff, numData, i);
					j++;
				}
			}
			if (found == false) {
				SetColor(4,0);
				cout << "Height not found, please re-enter a valid height: ";
				cin.clear();
				cin >> height;
				SetColor(11,0);
			}
		}
		break;
	}
	}
}

void modInfo(dataStorage staff[], int& numData, int i) {
	int choice = 0, choice2 = 0;
	string name, gender, inputIC;
	long long int IC = 0;
	double weight = 0, height = 0;
	string line = "======================================================================================================================================================================================";

	name = staff[i].getName();
	gender = staff[i].getGender();
	IC = staff[i].getStaffIC();
	weight = staff[i].getWeight();
	height = staff[i].getHeight();
	do {
		system("CLS");
		title();
		cout << "                                                                          MODIFY STAFF INFORMATION" << endl;
		cout << line << "\n\n";
		cout << "Name: " << name;
		cout << "\t\tStaff IC: ";
		if (IC / 1000000000 == 0) {
			cout << "000" << IC << endl;
		}
		else if (IC / 10000000000 == 0) {
			cout << "00" << IC << endl;
		}
		else if (IC / 100000000000 == 0) {
			cout << "0" << IC << endl;
		}
		else if (IC / 1000000000000 == 0) {
			cout << IC << endl;
		}
		cout << "Gender: " << gender << "\t\tWeight: " << weight << "\t\tHeight: " << height << endl << endl;
		cout << "Choose information to be modified:\n1  Name\n2  Staff IC\n3  Weight\n4  Height\nChoice: ";
		cin >> choice;
		while (cin.fail() || choice > 4 || choice <= 0)	{		//Input validation
			SetColor(4,0);
			cout << "Invalid input! Please enter a valid choice: ";
			cin.clear();
			cin.ignore(INT_MAX, '\n');
			cin >> choice;
			SetColor(11,0);
		}
		cout << endl;
		if (choice == 1) {
			cout << "New Name: ";
			cin.clear();
			cin.ignore(INT_MAX, '\n');
			getline(cin, name);
			for (int i = 0, j = 0; i < numData || name[j] != '\0'; i++, j++) {
				if (name.length() >= 32 || isdigit(name[j]) != 0 || ispunct(name[j]) != 0) {		//Input validation
					SetColor(4,0);
					cout << "Invalid name format input! Please enter a valid name: ";
					cin.clear();
					getline(cin, name);
					i = -1;
					j = -1;
					SetColor(11,0);
				}
				else if (staff[i].getName() == name) {		//Test if the name entered is repeated
					SetColor(4,0);
					cout << "This name belongs to another staff, please re-enter a valid name: ";
					cin.clear();
					getline(cin, name);
					i = -1;
					j = -1;
					SetColor(11,0);
				}
			}
		}
		else if (choice == 2) {
			cout << "\nNew Staff IC(without '-'): ";
			cin.clear();
			cin.ignore(INT_MAX, '\n');
			getline(cin, inputIC);
			for (int i = 0, j = 0; i < numData || inputIC[j] != '\0'; i++, j++) {		//Input validation
				if (inputIC.length() != 12 || isalpha(inputIC[j]) != 0 || ispunct(inputIC[j]) != 0) {
					SetColor(4,0);
					cout << "Invalid IC! Please enter a valid Staff IC: ";
					cin.clear();
					getline(cin, inputIC);
					i = -1;
					j = -1;
					SetColor(11,0);
				}
				else if (staff[i].getStaffIC() == realNum(inputIC)) {		//Test if staff IC entered is repeated
					SetColor(4,0);
					cout << "This IC belongs to another staff, please re-enter a valid staff IC:";
					cin.clear();
					getline(cin, inputIC);
					i = -1;
					j = -1;
					SetColor(11,0);
				}
			}
			IC = realNum(inputIC);
			if ((IC % 10) % 2 == 1) {		//Use staff IC to get gender
				gender = "Male";
			}
			else if ((IC % 10) % 2 == 0) {
				gender = "Female";
			}
		}
		else if (choice == 3) {
			cout << "New weight(kg): ";
			cin >> weight;
			while (cin.fail() || weight < 25 || weight >= 140)	{		//Input validation
				SetColor(4,0);
				cout << "Invalid input! Please enter a valid weight(kg): ";
				cin.clear();
				cin.ignore(INT_MAX, '\n');
				cin >> weight;
				SetColor(11,0);
			}
		}
		else if (choice == 4) {
			cout << "New height(cm): ";
			cin >> height;
			while (cin.fail() || height < 140 || height > 210) {		//Input validation
				SetColor(4,0);
				cout << "Invalid input! Please enter a valid weight(kg): ";
				cin.clear();
				cin.ignore(INT_MAX, '\n');
				cin >> weight;
				SetColor(11,0);
			}
		}
		cout << "\n=====================================" << endl;
		cout << "Edit done." << endl;
		staff[i].setPersonalData(name, gender, IC);
		staff[i].setFitnessData(weight, height);
		staff[i].calData();
		cout << "=====================================" << endl << endl;
		cout << "Do you want to modify any other information for this staff again:\n1  Yes\n2  No\nChoice: ";
		cin >> choice2;
		while (cin.fail() || choice2 > 2 || choice2 <= 0)	{		//Input validation
			SetColor(4,0);
			cout << "Invalid input! Please enter a valid choice: ";
			cin.clear();
			cin.ignore(INT_MAX, '\n');
			cin >> choice2;
			SetColor(11,0);
		}
	} while (choice2 == 1);
}

void searchFormula(dataStorage staff[], int& numData, int choice, bool& found, int index[], string name, long long int IC, string gender, int maxAge, int minAge, double maxWeight,
	double minWeight, double maxHeight, double minHeight, int& j) {
	j = 0;
	if (choice == 1) {
		for (int i = 0; i < numData; i++) {
			if (staff[i].getName() == name) {		//Find the specific staff using name and return the location
				found = true;
				index[j] = i;
				j++;
			}
		}
	}
	else if (choice == 2) {
		for (int i = 0; i < numData; i++) {
			if (staff[i].getStaffIC() == IC) {		//Find the specific staff using staff IC and return the location
				found = true;
				index[j] = i;
				j++;
			}
		}
	}
	else if (choice == 3) {
		for (int i = 0; i < numData; i++) {
			if (staff[i].getGender() == gender) {		//Find staff using gender and return the location
				found = true;
				index[j] = i;
				j++;
			}
		}
	}
	else if (choice == 4) {
		for (int i = 0; i < numData; i++) {
			if (staff[i].getAge() <= maxAge && staff[i].getAge() >= minAge) {		//Find staff using range of age and return the location
				found = true;
				index[j] = i;
				j++;
			}
		}
	}
	else if (choice == 5) {
		for (int i = 0; i < numData; i++) {
			if (staff[i].getWeight() <= maxWeight && staff[i].getWeight() >= minWeight) {		//Find staff using range of weight and return the location
				found = true;
				index[j] = i;
				j++;
			}
		}
	}
	else if (choice == 6) {
		for (int i = 0; i < numData; i++) {
			if (staff[i].getHeight() <= maxHeight && staff[i].getHeight() >= minHeight) {		//Find staff using range of height and return the location
				found = true;
				index[j] = i;
				j++;
			}
		}
	}
	else if (choice == 7) {
		for (int i = 0; i < numData; i++) {		//Find staff using gender and range of age and return the location
			if (staff[i].getGender() == gender && staff[i].getAge() <= maxAge && staff[i].getAge() >= minAge) {
				found = true;
				index[j] = i;
				j++;
			}
		}
	}
	else if (choice == 8) {
		for (int i = 0; i < numData; i++) {		//Find staff using gender and range of weight and return the location
			if (staff[i].getGender() == gender && staff[i].getWeight() <= maxWeight && staff[i].getWeight() >= minWeight) {
				found = true;
				index[j] = i;
				j++;
			}
		}
	}
	else if (choice == 9) {
		for (int i = 0; i < numData; i++) {		//Find staff using gender and range of height and return the location
			if (staff[i].getGender() == gender && staff[i].getHeight() <= maxHeight && staff[i].getHeight() >= minHeight) {
				found = true;
				index[j] = i;
				j++;
			}
		}
	}
	else if (choice == 10) {		//Find staff using gender, range of age, weight and height and return the location
		for (int i = 0; i < numData; i++) {
			if (staff[i].getGender() == gender && staff[i].getAge() <= maxAge && staff[i].getAge() >= minAge && staff[i].getWeight() <= maxWeight &&
				staff[i].getWeight() >= minWeight && staff[i].getHeight() <= maxHeight && staff[i].getHeight() >= minHeight) {
				found = true;
				index[j] = i;
				j++;
			}
		}
	}
}

void searchByWC(dataStorage staff[], int& numData, int index[], int& j, int& option) {
	bool found = false;
	j = 0;
	cout << "\n\nChoose one of the following:";
	while (found == false) {
		cout << "\n1  Underweight\n2  Normal weight\n3  Overweight\n4  Obese\n5  Underweight and Normal Weight\n6  Overweight and Obese:\nChoice: ";
		cin >> option;
		while (cin.fail() || option > 6 || option <= 0) {		//Input validation
			SetColor(4,0);
			cout << "Invalid input! Please enter a valid choice: ";
			cin.clear();
			cin.ignore(INT_MAX, '\n');
			cin >> option;
			SetColor(15,0);
		}
		if (option == 1) {
			for (int i = 0; i < numData; i++) {
				if (staff[i].getWeightCategory() == "Underweight") {		//Find staff using weight category and return the location
					found = true;
					index[j] = i;
					j++;
				}
			}
		}
		else if (option == 2) {
			for (int i = 0; i < numData; i++) {
				if (staff[i].getWeightCategory() == "Normal Weight") {
					found = true;
					index[j] = i;
					j++;
				}
			}
		}
		else if (option == 3) {
			for (int i = 0; i < numData; i++) {
				if (staff[i].getWeightCategory() == "Overweight") {
					found = true;
					index[j] = i;
					j++;
				}
			}
		}
		else if (option == 4) {
			for (int i = 0; i < numData; i++) {
				if (staff[i].getWeightCategory() == "Obese") {
					found = true;
					index[j] = i;
					j++;
				}
			}
		}
		else if (option == 5) {
			for (int i = 0; i < numData; i++) {
				if (staff[i].getWeightCategory() == "Underweight" || staff[i].getWeightCategory() == "Normal Weight") {
					found = true;
					index[j] = i;
					j++;
				}
			}
		}
		else if (option == 6) {
			for (int i = 0; i < numData; i++) {
				if (staff[i].getWeightCategory() == "Overweight" || staff[i].getWeightCategory() == "Obese") {
					found = true;
					index[j] = i;
					j++;
				}
			}
		}
		if (found == false) {
			SetColor(4,0);
			cout << "\nNo staff information falls in this category, please choose again: ";
			SetColor(11,0);
		}
	}
}

void searchInfo(dataStorage staff[], int& numData, int index[]) {
	string line = "======================================================================================================================================================================================";
	string name = " ", inputIC = " ", gender = " ";
	char inputGender;
	int choice = 0, maxAge = 0, minAge = 0, total = 0, num = 0, totalU = 0, totalN = 0, totalV = 0, totalO = 0, option = 0;
	long long int IC = 0;
	bool found = false;
	double maxWeight = 0, minWeight = 0, maxHeight = 0, minHeight = 0;
	title();
	cout << "                                                                          SEARCH STAFF INFORMATION" << endl;
	cout << line << endl;
	cout << "Choose one of the following criteria to search:\n1   Name\n2   Staff IC\n3   Gender\n4   Range of age\n5   Range of weight\n6   Range of height\n7   Gender and range of age" << endl;
	cout << "8   Gender and range of weight\n9   Gender and range of height\n10  Gender and range of age, weight and height\n11  Weight category\n\nChoice: ";
	cin >> choice;
	while (cin.fail() || choice > 11 || choice <= 0) {		//Input validation
		SetColor(4,0);
		cout << "Invalid input! Please enter a valid choice: ";
		cin.clear();
		cin.ignore(INT_MAX, '\n');
		cin >> choice;
		SetColor(11,0);
	}
	system("CLS");
	title();
	cout << "                                                                          SEARCH STAFF INFORMATION" << endl;
	cout << line << endl;
	switch (choice) {
	case 1: {
		cout << "\nSearch by name:\n\nName (max 31 characters including blank space): ";
		cin.clear();
		cin.ignore(INT_MAX, '\n');
		getline(cin, name);
		while (found == false) {
			for (int j = 0; name[j] != '\0'; j++) {
				if (name.length() >= 32 || isdigit(name[j]) != 0 || ispunct(name[j]) != 0) {		//Input validation
					SetColor(4,0);
					cout << "Invalid name format input! Please enter a valid name: ";
					cin.clear();
					getline(cin, name);
					j = -1;
					SetColor(11,0);
				}
			}
			searchFormula(staff, numData, choice, found, index, name, IC, gender, maxAge, minAge, maxWeight, minWeight, maxHeight, minHeight, total);
			if (found == false) {		//Name entered not found, ask user to input again
				SetColor(4,0);
				cout << "Name not found, please re-enter a valid name: ";
				cin.clear();
				getline(cin, name);
				SetColor(11,0);
			}
		}
		break;
	}
	case 2: {
		cout << "\nSearch by Staff IC:\n\nStaff IC(without '-'): ";
		cin.ignore(INT_MAX, '\n');
		getline(cin, inputIC);
		while (found == false) {
			for (int j = 0; inputIC[j] != '\0'; j++) {
				if (inputIC.length() != 12 || isalpha(inputIC[j]) != 0 || ispunct(inputIC[j]) != 0) {		//Input validation
					SetColor(4,0);
					cout << "Invalid IC! Please enter a valid Staff IC: ";
					cin.clear();
					getline(cin, inputIC);
					j = -1;
					SetColor(11,0);
				}
			}
			searchFormula(staff, numData, choice, found, index, name, IC, gender, maxAge, minAge, maxWeight, minWeight, maxHeight, minHeight, total);
			if (found == false) {
				SetColor(4,0);
				cout << "IC not found, please re-enter a valid IC: ";		//Staff IC entered not found, ask user to input again
				cin.clear();
				getline(cin, inputIC);
				SetColor(11,0);
			}
		}
		break;
	}
	case 3: {
		cout << "\nSearch by Gender:";
		while (found == false) {
			cout << "\n\nGender(M/F): ";
			cin.ignore(INT_MAX, '\n');
			cin >> inputGender;
			while (cin.fail() || (inputGender != 'M' && inputGender != 'm' && inputGender != 'F' && inputGender != 'f')) {		//Input validation
				SetColor(4,0);
				cout << "Invalid input! Please enter a valid gender: ";
				cin.clear();
				cin.ignore(INT_MAX, '\n');
				cin >> inputGender;
				SetColor(11,0);
			}
			if (inputGender == 'M' || inputGender == 'm') {
				gender = "Male";
			}
			else if (inputGender == 'F' || inputGender == 'f') {
				gender = "Female";
			}
			searchFormula(staff, numData, choice, found, index, name, IC, gender, maxAge, minAge, maxWeight, minWeight, maxHeight, minHeight, total);
			if (found == false) {
				SetColor(4,0);
				cout << "Gender not found, please re-enter ";
				SetColor(11,0);
			}
		}
		break;
	}
	case 4: {
		cout << "\nSearch by Range of Age:";
		while (found == false) {
			cout << "\n\nMin Age (21 - 79): ";
			cin.ignore(INT_MAX, '\n');
			cin >> minAge;
			while (cin.fail() || minAge < 21 || minAge >= 80) {		//Input validation
				SetColor(4,0);
				cout << "Invalid input! Please enter a valid age: ";
				cin.clear();
				cin.ignore(INT_MAX, '\n');
				cin >> minAge;
				SetColor(11,0);
			}
			cout << "Max Age (21 - 79): ";
			cin >> maxAge;
			while (cin.fail() || maxAge < 21 || maxAge >= 80) {		//Input validation
				SetColor(4,0);
				cout << "Invalid input! Please enter a valid age: ";
				cin.clear();
				cin.ignore(INT_MAX, '\n');
				cin >> maxAge;
				SetColor(11,0);
			}
			searchFormula(staff, numData, choice, found, index, name, IC, gender, maxAge, minAge, maxWeight, minWeight, maxHeight, minHeight, total);
			if (found == false) {
				SetColor(4,0);
				cout << "Invalid range of age. Please re-enter a valid range of age: ";
				SetColor(11,0);
			}
		}
		break;
	}
	case 5: {
		cout << "\nSearch by Range of Weight:";
		while (found == false) {
			cout << "\n\nMin Weight: ";
			cin.ignore(INT_MAX, '\n');
			cin >> minWeight;
			while (cin.fail() || minWeight < 25 || minWeight >= 140) {		//Input validation
				SetColor(4,0);
				cout << "Invalid input! Please enter a valid weight: ";
				cin.clear();
				cin.ignore(INT_MAX, '\n');
				cin >> minWeight;
				SetColor(11,0);
			}
			cout << "Max Weight: ";
			cin >> maxWeight;
			while (cin.fail() || maxWeight < 25 || maxWeight >= 140) {		//Input validation
				SetColor(4,0);
				cout << "Invalid input! Please enter a valid weight: ";
				cin.clear();
				cin.ignore(INT_MAX, '\n');
				cin >> maxWeight;
				SetColor(11,0);
			}
			searchFormula(staff, numData, choice, found, index, name, IC, gender, maxAge, minAge, maxWeight, minWeight, maxHeight, minHeight, total);
			if (found == false) {
				SetColor(4,0);
				cout << "Invalid range of weight. Please re-enter a valid range of weight: ";
				SetColor(11,0);
			}
		}
		break;
	}
	case 6: {
		cout << "\nSearch by Range of Height:";
		while (found == false) {
			cout << "\n\nMin Height: ";
			cin.ignore(INT_MAX, '\n');
			cin >> minHeight;
			while (cin.fail() || minHeight < 140 || minHeight > 210) {		//Input validation
				SetColor(4,0);
				cout << "Invalid input! Please enter a valid height: ";
				cin.clear();
				cin.ignore(INT_MAX, '\n');
				cin >> minHeight;
				SetColor(11,0);
			}
			cout << "Max Height: ";
			cin >> maxHeight;
			while (cin.fail() || maxHeight < 140 || maxHeight > 210) {		//Input validation
				SetColor(4,0);
				cout << "Invalid input! Please enter a valid height: ";
				cin.clear();
				cin.ignore(INT_MAX, '\n');
				cin >> maxHeight;
				SetColor(11,0);
			}
			searchFormula(staff, numData, choice, found, index, name, IC, gender, maxAge, minAge, maxWeight, minWeight, maxHeight, minHeight, total);
			if (found == false) {
				SetColor(4,0);
				cout << "Invalid range of height. Please re-enter a valid range of height: ";
				SetColor(11,0);
			}
		}
		break;
	}
	case 7: {
		cout << "\nSearch by Gender and range of age:";
		while (found == false) {
			cout << "\n\nGender(M/F): ";
			cin.ignore(INT_MAX, '\n');
			cin >> inputGender;
			while (cin.fail() || (inputGender != 'M' && inputGender != 'm' && inputGender != 'F' && inputGender != 'f')) {		//Input validation
				SetColor(4,0);
				cout << "Invalid input! Please enter a valid gender: ";
				cin.clear();
				cin.ignore(INT_MAX, '\n');
				cin >> inputGender;
				SetColor(11,0);
			}
			if (inputGender == 'M' || inputGender == 'm') {
				gender = "Male";
			}
			else if (inputGender == 'F' || inputGender == 'f') {
				gender = "Female";
			}
			cout << "\nMin Age (21 - 79): ";
			cin.ignore(INT_MAX, '\n');
			cin >> minAge;
			while (cin.fail() || minAge < 21 || minAge >= 80) {		//Input validation
				SetColor(4,0);
				cout << "Invalid input! Please enter a valid age: ";
				cin.clear();
				cin.ignore(INT_MAX, '\n');
				cin >> minAge;
				SetColor(11,0);
			}
			cout << "Max Age (21 - 79): ";
			cin >> maxAge;
			while (cin.fail() || maxAge < 21 || maxAge >= 80) {		//Input validation
				SetColor(4,0);
				cout << "Invalid input! Please enter a valid age: ";
				cin.clear();
				cin.ignore(INT_MAX, '\n');
				cin >> maxAge;
				SetColor(11,0);
			}
			searchFormula(staff, numData, choice, found, index, name, IC, gender, maxAge, minAge, maxWeight, minWeight, maxHeight, minHeight, total);
			if (found == false) {
				SetColor(4,0);
				cout << "No staff information falls in this range, please re-enter: ";
				SetColor(11,0);
			}
		}
		break;
	}
	case 8: {
		cout << "\nSearch by Gender and range of weight:";
		while (found == false) {
			cout << "\n\nGender(M/F): ";
			cin.ignore(INT_MAX, '\n');
			cin >> inputGender;
			while (cin.fail() || (inputGender != 'M' && inputGender != 'm' && inputGender != 'F' && inputGender != 'f')) {		//Input validation
				SetColor(4,0);
				cout << "Invalid input! Please enter a valid gender: ";
				cin.clear();
				cin.ignore(INT_MAX, '\n');
				cin >> inputGender;
				SetColor(11,0);
			}
			if (inputGender == 'M' || inputGender == 'm') {
				gender = "Male";
			}
			else if (inputGender == 'F' || inputGender == 'f') {
				gender = "Female";
			}
			cout << "\nMin Weight: ";
			cin.ignore(INT_MAX, '\n');
			cin >> minWeight;
			while (cin.fail() || minWeight < 25 || minWeight >= 140) {		//Input validation
				SetColor(4,0);
				cout << "Invalid input! Please enter a valid weight: ";
				cin.clear();
				cin.ignore(INT_MAX, '\n');
				cin >> minWeight;
				SetColor(11,0);
			}
			cout << "Max Weight: ";
			cin >> maxWeight;
			while (cin.fail() || maxWeight < 25 || maxWeight >= 140) {		//Input validation
				SetColor(4,0);
				cout << "Invalid input! Please enter a valid weight: ";
				cin.clear();
				cin.ignore(INT_MAX, '\n');
				cin >> maxWeight;
				SetColor(11,0);
			}
			searchFormula(staff, numData, choice, found, index, name, IC, gender, maxAge, minAge, maxWeight, minWeight, maxHeight, minHeight, total);
			if (found == false) {
				SetColor(4,0);
				cout << "No staff information falls in this range, please re-enter: ";
				SetColor(11,0);
			}
		}
		break;
	}
	case 9: {
		cout << "\nSearch by Gender and range of height:";
		while (found == false) {
			cout << "\n\nGender(M/F): ";
			cin.ignore(INT_MAX, '\n');
			cin >> inputGender;
			while (cin.fail() || (inputGender != 'M' && inputGender != 'm' && inputGender != 'F' && inputGender != 'f')) {		//Input validation
				SetColor(4,0);
				cout << "Invalid input! Please enter a valid gender: ";
				cin.clear();
				cin.ignore(INT_MAX, '\n');
				cin >> inputGender;
				SetColor(11,0);
			}
			if (inputGender == 'M' || inputGender == 'm') {
				gender = "Male";
			}
			else if (inputGender == 'F' || inputGender == 'f') {
				gender = "Female";
			}
			cout << "\nMin Height: ";
			cin.ignore(INT_MAX, '\n');
			cin >> minHeight;
			while (cin.fail() || minHeight < 140 || minHeight > 210) {		//Input validation
				SetColor(4,0);
				cout << "Invalid input! Please enter a valid height: ";
				cin.clear();
				cin.ignore(INT_MAX, '\n');
				cin >> minHeight;
				SetColor(11,0);
			}
			cout << "Max Height: ";
			cin >> maxHeight;
			while (cin.fail() || maxHeight < 140 || maxHeight > 210) {		//Input validation
				SetColor(4,0);
				cout << "Invalid input! Please enter a valid height: ";
				cin.clear();
				cin.ignore(INT_MAX, '\n');
				cin >> maxHeight;
				SetColor(11,0);
			}
			searchFormula(staff, numData, choice, found, index, name, IC, gender, maxAge, minAge, maxWeight, minWeight, maxHeight, minHeight, total);
			if (found == false) {
				SetColor(4,0);
				cout << "No staff information falls in this range, please re-enter: ";
				SetColor(11,0);
			}
		}
		break;
	}
	case 10: {
		cout << "\nSearch by Gender and range of age:";
		while (found == false) {
			cout << "\n\nGender(M/F): ";
			cin.ignore(INT_MAX, '\n');
			cin >> inputGender;
			while (cin.fail() || (inputGender != 'M' && inputGender != 'm' && inputGender != 'F' && inputGender != 'f')) {		//Input validation
				SetColor(4,0);
				cout << "Invalid input! Please enter a valid gender: ";
				cin.clear();
				cin.ignore(INT_MAX, '\n');
				cin >> inputGender;
				SetColor(11,0);
			}
			if (inputGender == 'M' || inputGender == 'm') {
				gender = "Male";
			}
			else if (inputGender == 'F' || inputGender == 'f') {
				gender = "Female";
			}
			cout << "\nMin Age (21 - 79): ";
			cin.ignore(INT_MAX, '\n');
			cin >> minAge;
			while (cin.fail() || minAge < 21 || minAge >= 80) {		//Input validation
				SetColor(4,0);
				cout << "Invalid input! Please enter a valid age: ";
				cin.clear();
				cin.ignore(INT_MAX, '\n');
				cin >> minAge;
				SetColor(11,0);
			}
			cout << "Max Age (21 - 79): ";
			cin >> maxAge;
			while (cin.fail() || maxAge < 21 || maxAge >= 80) {		//Input validation
				SetColor(4,0);
				cout << "Invalid input! Please enter a valid age: ";
				cin.clear();
				cin.ignore(INT_MAX, '\n');
				cin >> maxAge;
				SetColor(11,0);
			}
			cout << "\nMin Weight: ";
			cin.ignore(INT_MAX, '\n');
			cin >> minWeight;
			while (cin.fail() || minWeight < 25 || minWeight >= 140) {		//Input validation
				SetColor(4,0);
				cout << "Invalid input! Please enter a valid weight: ";
				cin.clear();
				cin.ignore(INT_MAX, '\n');
				cin >> minWeight;
				SetColor(11,0);
			}
			cout << "Max Weight: ";
			cin >> maxWeight;
			while (cin.fail() || maxWeight < 25 || maxWeight >= 140) {		//Input validation
				SetColor(4,0);
				cout << "Invalid input! Please enter a valid weight: ";
				cin.clear();
				cin.ignore(INT_MAX, '\n');
				cin >> maxWeight;
				SetColor(11,0);
			}
			cout << "\nMin Height: ";
			cin.ignore(INT_MAX, '\n');
			cin >> minHeight;
			while (cin.fail() || minHeight < 140 || minHeight > 210) {		//Input validation
				SetColor(4,0);
				cout << "Invalid input! Please enter a valid height: ";
				cin.clear();
				cin.ignore(INT_MAX, '\n');
				cin >> minHeight;
				SetColor(11,0);
			}
			cout << "Max Height: ";
			cin >> maxHeight;
			while (cin.fail() || maxHeight < 140 || maxHeight > 210) {		//Input validation
				SetColor(4,0);
				cout << "Invalid input! Please enter a valid height: ";
				cin.clear();
				cin.ignore(INT_MAX, '\n');
				cin >> maxHeight;
				SetColor(11,0);
			}
			searchFormula(staff, numData, choice, found, index, name, IC, gender, maxAge, minAge, maxWeight, minWeight, maxHeight, minHeight, total);
			if (found == false) {
				SetColor(4,0);
				cout << "No staff information falls in this range, please re-enter: ";
				SetColor(11,0);
			}
		}
		break;
	}
	case 11: {
		cout << "\nSearch by weight category:";
		searchByWC(staff, numData, index, total, option);		//Call searchByWC function
		break;
	}
	}
	cout << "\nLoading information...\n" << endl;
	system("pause");
	system("CLS");
	title();
	cout << "                                                                          SEARCH STAFF INFORMATION" << endl;
	cout << line << endl;
	cout << setw(8) << "NAME\t\t\tSTAFF IC\tGENDER\t\tAGE\tDATE OF BIRTH\tWEIGHT(kg)\tHEIGHT(cm)\tBMI\t\tBMR\t\tRMR\t\tWEIGHT CATEGORY" << endl;
	cout << "\t\t\t\t\t\t\t\t\t(dd/mm/yy)" << endl;
	cout << line << "\n\n";
	for (int i = 0; i < total; i++) {		//for-loop to display all searched staff information
		num = index[i];
		cout << staff[num].getName();
		cout << setw(31 - staff[num].getName().size());
		if (staff[i].getStaffIC() / 1000000000 == 0) {
			cout << "\t000" << staff[num].getStaffIC();
		}
		else if (staff[num].getStaffIC() / 10000000000 == 0) {
			cout << "\t00" << staff[num].getStaffIC();
		}
		else if (staff[num].getStaffIC() / 100000000000 == 0) {
			cout << "\t0" << staff[num].getStaffIC();
		}
		else if (staff[num].getStaffIC() / 1000000000000 == 0) {
			cout << "\t" << staff[num].getStaffIC();
		}
		cout << "\t" << staff[num].getGender();
		cout << "\t\t" << staff[num].getAge();
		cout << "\t" << staff[num].getDD();
		cout << "/" << staff[num].getMM();
		cout << "/" << staff[num].getYYYY();
		cout << "\t" << staff[num].getWeight();
		cout << "\t\t" << staff[num].getHeight();
		cout << "\t\t" << staff[num].getBMI();
		cout << "\t\t" << staff[num].getBMR();
		cout << "\t\t" << staff[num].getRMR();
		cout << "\t\t" << staff[num].getWeightCategory() << endl << endl;
	}
	cout << line << endl;
	cout << "                   :::SEARCHED USM STAFF:::" << endl;
	if (choice != 11) {
		statInfo(staff, numData, index, total);		//Display BMI distribution
	}
	else if (choice == 11) {
		statInfo2(staff, numData, index, option, total);		//Display BMI distribution
	}
}

void statInfo(dataStorage staff[], int& numData, int index[], int total) {
	string line = "======================================================================================================================================================================================";
	int totalU = 0, totalN = 0, totalV = 0, totalO = 0;

	numBMI(staff, numData, totalU, totalN, totalV, totalO, index, total);
	cout << "                      BMI DISTRIBUTION" << endl;
	cout << "||==========================================================||" << endl;
	cout << "||      BMI      ||    Weight Category    ||      Total     ||" << endl;
	cout << "||===============||=======================||================||" << endl;
	cout << "||      <20      ||      Underweight      ||        " << totalU << "       ||" << endl;
	cout << "||20 <= BMI < 30 ||     Normal Weight     ||        " << totalN << "       ||" << endl;
	cout << "||25 <= BMI < 30 ||      Overweight       ||        " << totalV << "       ||" << endl;
	cout << "||      >=30     ||        Obese          ||        " << totalO << "       ||" << endl;
	cout << "||==========================================================||" << endl << endl;
	for (int i = 0; i < 3; i++) {
		if (i == 0 || i == 2) {
			cout << "||=================||";
		}
		else if (i == 1) {
			cout << "||   Underweight   ||";
		}
		for (int j = 0; j < totalU; j++) {
			SetColor(14,0);
			cout << "::";
			SetColor(11,0);
		}
		if (i == 1){
			cout << "  " << (static_cast<double>(totalU)/static_cast<double>(numData))*100 << "%";
		}
		cout << endl;
	}
	cout << endl;
	for (int i = 0; i < 3; i++) {
		if (i == 0 || i == 2) {
			cout << "||=================||";
		}
		else if (i == 1) {
			cout << "||  Normal weight  ||";
		}
		for (int j = 0; j < totalN; j++) {
			SetColor(14,0);
			cout << "::";
			SetColor(11,0);
		}
		if (i == 1){
			cout << "  " << (static_cast<double>(totalN)/static_cast<double>(numData))*100 << "%";
		}
		cout << endl;
	}
	cout << endl;
	for (int i = 0; i < 3; i++) {
		if (i == 0 || i == 2) {
			cout << "||=================||";
		}
		else if (i == 1) {
			cout << "||    Overweight   ||";
		}
		for (int j = 0; j < totalV; j++) {
			SetColor(14,0);
			cout << "::";
			SetColor(11,0);
		}
		if (i == 1){
			cout << "  " << (static_cast<double>(totalV)/static_cast<double>(numData))*100 << "%";
		}
		cout << endl;
	}
	cout << endl;
	for (int i = 0; i < 3; i++) {
		if (i == 0 || i == 2) {
			cout << "||=================||";
		}
		else if (i == 1) {
			cout << "||      Obese      ||";
		}
		for (int j = 0; j < totalO; j++) {
			SetColor(14,0);
			cout << "::";
			SetColor(11,0);
		}
		if (i == 1){
			cout << "  " << (static_cast<double>(totalO)/static_cast<double>(numData))*100 << "%";
		}
		cout << endl;
	}
	cout << endl;
	system("pause");
	system("CLS");
	title();
	cout << "Back to main programme..." << endl;
	system("pause");
	system("CLS");
}

void statInfo2(dataStorage staff[], int& numData, int index[], int option, int total) {
	string line = "======================================================================================================================================================================================";
	int totalU = 0, totalN = 0, totalV = 0, totalO = 0;

	numBMI(staff, numData, totalU, totalN, totalV, totalO, index, total);
	if (option == 1) {
		cout << "                      BMI DISTRIBUTION" << endl;
		cout << "||==========================================================||" << endl;
		cout << "||      BMI      ||    Weight Category    ||      Total     ||" << endl;
		cout << "||===============||=======================||================||" << endl;
		cout << "||      <20      ||      Underweight      ||        " << totalU << "       ||" << endl;
		cout << "||==========================================================||" << endl << endl;
	}
	else if (option == 2) {
		cout << "                      BMI DISTRIBUTION" << endl;
		cout << "||==========================================================||" << endl;
		cout << "||      BMI      ||    Weight Category    ||      Total     ||" << endl;
		cout << "||===============||=======================||================||" << endl;
		cout << "||20 <= BMI < 30 ||     Normal Weight     ||        " << totalN << "       ||" << endl;
		cout << "||==========================================================||" << endl << endl;
	}
	else if (option == 3) {
		cout << "                      BMI DISTRIBUTION" << endl;
		cout << "||==========================================================||" << endl;
		cout << "||      BMI      ||    Weight Category    ||      Total     ||" << endl;
		cout << "||===============||=======================||================||" << endl;
		cout << "||25 <= BMI < 30 ||      Overweight       ||        " << totalV << "       ||" << endl;
		cout << "||==========================================================||" << endl << endl;
	}
	else if (option == 4) {
		cout << "                      BMI DISTRIBUTION" << endl;
		cout << "||==========================================================||" << endl;
		cout << "||      BMI      ||    Weight Category    ||      Total     ||" << endl;
		cout << "||===============||=======================||================||" << endl;
		cout << "||      >=30     ||        Obese          ||        " << totalO << "       ||" << endl;
		cout << "||==========================================================||" << endl << endl;
	}
	else if (option == 5) {
		cout << "                      BMI DISTRIBUTION" << endl;
		cout << "||==========================================================||" << endl;
		cout << "||      BMI      ||    Weight Category    ||      Total     ||" << endl;
		cout << "||===============||=======================||================||" << endl;
		cout << "||      <20      ||      Underweight      ||        " << totalU << "       ||" << endl;
		cout << "||20 <= BMI < 30 ||     Normal Weight     ||        " << totalN << "       ||" << endl;
		cout << "||==========================================================||" << endl << endl;
	}
	else if (option == 6) {
		cout << "                      BMI DISTRIBUTION" << endl;
		cout << "||==========================================================||" << endl;
		cout << "||      BMI      ||    Weight Category    ||      Total     ||" << endl;
		cout << "||===============||=======================||================||" << endl;
		cout << "||25 <= BMI < 30 ||      Overweight       ||        " << totalV << "       ||" << endl;
		cout << "||      >=30     ||        Obese          ||        " << totalO << "       ||" << endl;
		cout << "||==========================================================||" << endl << endl;
	}
	if (option == 1 || option == 5) {
		for (int i = 0; i < 3; i++) {
			if (i == 0 || i == 2) {
				cout << "||=================||";
			}
			else if (i == 1) {
				cout << "||   Underweight   ||";
			}
			for (int j = 0; j < totalU; j++) {
				SetColor(14,0);
				cout << "::";
				SetColor(11,0);
			}
			if (i == 1){
				cout << "  " << (static_cast<double>(totalU)/static_cast<double>(numData))*100 << "%";
			}
			cout << endl;
		}
		cout << endl;
	}
	if (option == 2 || option == 5) {
		for (int i = 0; i < 3; i++) {
			if (i == 0 || i == 2) {
				cout << "||=================||";
			}
			else if (i == 1) {
				cout << "||  Normal weight  ||";
			}
			for (int j = 0; j < totalN; j++) {
				SetColor(14,0);
				cout << "::";
				SetColor(11,0);
			}
			if (i == 1){
				cout << "  " << (static_cast<double>(totalN)/static_cast<double>(numData))*100 << "%";
			}
			cout << endl;
		}
		cout << endl;
	}
	if (option == 3 || option == 6) {
		for (int i = 0; i < 3; i++) {
			if (i == 0 || i == 2) {
				cout << "||=================||";
			}
			else if (i == 1) {
				cout << "||    Overweight   ||";
			}
			for (int j = 0; j < totalV; j++) {
				SetColor(14,0);
				cout << "::";
				SetColor(11,0);
			}
			if (i == 1){
				cout << "  " << (static_cast<double>(totalV)/static_cast<double>(numData))*100 << "%";
			}
			cout << endl;
		}
		cout << endl;
	}
	if (option == 4 || option == 6) {
		for (int i = 0; i < 3; i++) {
			if (i == 0 || i == 2) {
				cout << "||=================||";
			}
			else if (i == 1) {
				cout << "||      Obese      ||";
			}
			for (int j = 0; j < totalO; j++) {
				SetColor(14,0);
				cout << "::";
				SetColor(11,0);
			}
			if (i == 1){
				cout << "  " << (static_cast<double>(totalO)/static_cast<double>(numData))*100 << "%";
			}
			cout << endl;
		}
		cout << endl;
	}
	cout << endl;
	system("pause");
	system("CLS");
	title();
	cout << "Back to main programme..." << endl;
	system("pause");
	system("CLS");
}

void numBMI(dataStorage staff[], int& numData, int& totalU, int& totalN, int& totalV, int& totalO, int index[], int total) {
	int num = 0;
	totalU = 0, totalN = 0, totalV = 0, totalO = 0;
	for (int i = 0; i < total; i++) {		//for-loop to get the total number of staff for each weight categories
		num = index[i];
		if (staff[num].getWeightCategory() == "Underweight") {
			totalU++;
		}
		else if (staff[num].getWeightCategory() == "Normal Weight") {
			totalN++;
		}
		else if (staff[num].getWeightCategory() == "Overweight") {
			totalV++;
		}
		else if (staff[num].getWeightCategory() == "Obese") {
			totalO++;
		}
	}
}

void overallInfo(dataStorage staff[], int& numData){		//Display overall staff BMI distribution
	int totalU = 0, totalN = 0, totalV = 0, totalO = 0;
	string line = "======================================================================================================================================================================================";
	for (int i = 0; i < numData; i++) {		//for-loop to get the total number of staff for each weight categories
		if (staff[i].getWeightCategory() == "Underweight") {
			totalU++;
		}
		else if (staff[i].getWeightCategory() == "Normal Weight") {
			totalN++;
		}
		else if (staff[i].getWeightCategory() == "Overweight") {
			totalV++;
		}
		else if (staff[i].getWeightCategory() == "Obese") {
			totalO++;
		}
	}
	title();
	cout << "                   :::OVERALL USM STAFF:::" << endl;
	cout << "                      BMI DISTRIBUTION" << endl;
	cout << "||==========================================================||" << endl;
	cout << "||      BMI      ||    Weight Category    ||      Total     ||" << endl;
	cout << "||===============||=======================||================||" << endl;
	cout << "||      <20      ||      Underweight      ||        " << totalU << "       ||" << endl;
	cout << "||20 <= BMI < 30 ||     Normal Weight     ||        " << totalN << "       ||" << endl;
	cout << "||25 <= BMI < 30 ||      Overweight       ||        " << totalV << "       ||" << endl;
	cout << "||      >=30     ||        Obese          ||        " << totalO << "       ||" << endl;
	cout << "||==========================================================||" << endl << endl;
	for (int i = 0; i < 3; i++) {
		if (i == 0 || i == 2) {
			cout << "||=================||";
		}
		else if (i == 1) {
			cout << "||   Underweight   ||";
		}
		for (int j = 0; j < totalU; j++) {
			SetColor(14,0);
			cout << "::";
			SetColor(11,0);
		}
		if (i == 1){
			cout << "  " << (static_cast<double>(totalU)/static_cast<double>(numData))*100 << "%";
		}
		cout << endl;
	}
	cout << endl;
	for (int i = 0; i < 3; i++) {
		if (i == 0 || i == 2) {
			cout << "||=================||";
		}
		else if (i == 1) {
			cout << "||  Normal weight  ||";
		}
		for (int j = 0; j < totalN; j++) {
			SetColor(14,0);
			cout << "::";
			SetColor(11,0);
		}
		if (i == 1){
			cout << "  " << (static_cast<double>(totalN)/static_cast<double>(numData))*100 << "%";
		}
		cout << endl;
	}
	cout << endl;
	for (int i = 0; i < 3; i++) {
		if (i == 0 || i == 2) {
			cout << "||=================||";
		}
		else if (i == 1) {
			cout << "||    Overweight   ||";
		}
		for (int j = 0; j < totalV; j++) {
			SetColor(14,0);
			cout << "::";
			SetColor(11,0);
		}
		if (i == 1){
			cout << "  " << (static_cast<double>(totalV)/static_cast<double>(numData))*100 << "%";
		}
		cout << endl;
	}
	cout << endl;
	for (int i = 0; i < 3; i++) {
		if (i == 0 || i == 2) {
			cout << "||=================||";
		}
		else if (i == 1) {
			cout << "||      Obese      ||";
		}
		for (int j = 0; j < totalO; j++) {
			SetColor(14,0);
			cout << "::";
			SetColor(11,0);
		}
		if (i == 1){
			cout << "  " << (static_cast<double>(totalO)/static_cast<double>(numData))*100 << "%";
		}
		cout << endl;
	}
	cout << endl;
	system("pause");
	system("CLS");
	title();
	cout << "Back to main programme..." << endl;
	system("pause");
	system("CLS");
}

void targetInfo(dataStorage staff[], int& numData) {		//Calculate total calories needed to consume to maintain weight
	int choice = 0, choice2 = 0, age = 0;
	long long int IC = 0;
	string name, inputIC;
	char gender;
	double weight = 0, height = 0, RMR = 0, calories = 0;
	bool found = false;
	string line = "======================================================================================================================================================================================";

	title();
	cout << "                                                                       CALORIES TARGET INFORMATION" << endl;
	cout << line << endl;
	SetColor(15,0);
	cout << "The Harris-Benedict Formula(RMR) is based on total body weight, height, age, and sex and is able to provide accurate result for" << endl;
	cout << "you to know how much calories needed to maintain your weight." << endl;
	cout << "Harris-Benedict Formula(RMR):" << endl;
	cout << line << endl;
	cout << "||MALE:                                                                                 ||FEMALE:                                                                                   ||" << endl;
	cout << "||                                                                                      ||                                                                                          ||" << endl;
	cout << "||RMR = 88.362 + (13.397 * Weight) + (4.799 * Height)                                   ||RMR = 447.593 + (9.247 * Weight) + (3.098 * Height)                                       ||" << endl;
	cout << "||       - (5.677 * Age)                                                                ||       - (4.330 * Age)                                                                    ||" << endl;
	cout << line << endl;
	SetColor(11,0);
	cout << "Do you want to search your information from our database or input your own information:\n1  Search from database\n2  Input information\nChoice: ";
	cin >> choice;
	while (cin.fail() || choice > 2 || choice <= 0) {		//Input validation
		SetColor(4,0);
		cout << "Invalid input! Please enter a valid choice: ";
		cin.clear();
		cin.ignore(INT_MAX, '\n');
		cin >> choice;
		SetColor(11,0);
	}
	if (choice == 1) {
		cout << "\nSearch by:\n1  Name\n2  Staff IC\nChoice: ";
		cin >> choice2;
		while (cin.fail() || choice2 > 2 || choice2 <= 0) {		//Input validation
			SetColor(4,0);
			cout << "Invalid input! Please enter a valid choice: ";
			cin.clear();
			cin.ignore(INT_MAX, '\n');
			cin >> choice2;
			SetColor(11,0);
		}
		system("CLS");
		title();
		cout << "                                                                          CALORIES TARGET INFORMATION" << endl;
		cout << line << endl;
		switch (choice2) {
		case 1: {
			cout << "\nSearch Name (max 31 characters including blank space): ";
			cin.clear();
			cin.ignore(INT_MAX, '\n');
			getline(cin, name);
			while (found == false) {
				for (int j = 0; name[j] != '\0'; j++) {
					if (name.length() >= 32 || isdigit(name[j]) != 0 || ispunct(name[j]) != 0) {		//Input validation
						SetColor(4,0);
						cout << "Invalid name format input! Please enter a valid name: ";
						cin.clear();
						getline(cin, name);
						j = -1;
						SetColor(11,0);
					}
				}
				for (int i = 0; i < numData; i++) {
					if (staff[i].getName() == name) {		//Find the specific staff using name entered
						found = true;
						if (staff[i].getGender() == "Male") {
							gender = 'M';
						}
						else {
							gender = 'F';
						}
						name = staff[i].getName();
						IC = staff[i].getStaffIC();
						age = staff[i].getAge();
						weight = staff[i].getWeight();
						height = staff[i].getHeight();
						RMR = staff[i].getRMR();
						break;
					}
				}
				if (found == false) {		//Name entered not found, ask user to input again
					SetColor(4,0);
					cout << "Name not found, please re-enter a valid name: ";
					cin.clear();
					getline(cin, name);
					SetColor(11,0);
				}
			}
			break;
		}
		case 2: {
			cout << "\nSearch Staff IC(without '-'): ";
			cin.ignore(INT_MAX, '\n');
			getline(cin, inputIC);
			while (found == false) {
				for (int j = 0; inputIC[j] != '\0'; j++) {		//Input validation
					if (inputIC.length() != 12 || isalpha(inputIC[j]) != 0 || ispunct(inputIC[j]) != 0) {
						SetColor(4,0);
						cout << "Invalid IC! Please enter a valid Staff IC: ";
						cin.clear();
						getline(cin, inputIC);
						j = -1;
						SetColor(11,0);
					}
				}
				for (int i = 0; i < numData; i++) {
					if (staff[i].getStaffIC() == realNum(inputIC)) {		//Find specific staff using staff IC
						found = true;
						if (staff[i].getGender() == "Male") {
							gender = 'M';
						}
						else {
							gender = 'F';
						}
						name = staff[i].getName();
						IC = staff[i].getStaffIC();
						age = staff[i].getAge();
						weight = staff[i].getWeight();
						height = staff[i].getHeight();
						RMR = staff[i].getRMR();
						break;
					}
				}
				if (found == false) {		//Staff IC entered not found, ask user to input again
					SetColor(4,0);
					cout << "IC not found, please re-enter a valid IC: ";
					cin.clear();
					getline(cin, inputIC);
					SetColor(11,0);
				}
			}
			break;
		}
		}
	}
	else if (choice == 2) {		//Ask user to enter all information to calculate calories target
		system("CLS");
		title();
		cout << line << endl;
		cout << "Enter the following details: " << endl << endl;
		cout << "Name (max 31 characters including blank space): ";
		cin.ignore(INT_MAX, '\n');
		getline(cin, name);
		for (int j = 0; name[j] != '\0'; j++) {
			if (name.length() >= 32 || isdigit(name[j]) != 0 || ispunct(name[j]) != 0) {		//Input validation
				SetColor(4,0);
				cout << "Invalid name format input! Please enter a valid name: ";
				cin.clear();
				getline(cin, name);
				j = -1;
				SetColor(11,0);
			}
		}
		cout << "\nGender(M/F): ";
		cin >> gender;
		while (cin.fail() || (gender != 'M' && gender != 'm' && gender != 'F' && gender != 'f')) {		//Input validation
			SetColor(4,0);
			cout << "Invalid input! Please enter a valid gender: ";
			cin.clear();
			cin.ignore(INT_MAX, '\n');
			cin >> gender;
			SetColor(11,0);
		}
		cout << "\nAge: ";
		cin >> age;
		while (cin.fail() || age <=0 || age >= 80) {		//Input validation
			SetColor(4,0);
			cout << "Invalid input! Please enter a valid age: ";
			cin.clear();
			cin.ignore(INT_MAX, '\n');
			cin >> age;
			SetColor(11,0);
		}
		cout << "\nWeight(kg): ";
		cin >> weight;
		while (cin.fail() || weight < 25 || weight >= 140) {		//Input validation
			SetColor(4,0);
			cout << "Invalid input! Please enter a valid weight: ";
			cin.clear();
			cin.ignore(INT_MAX, '\n');
			cin >> weight;
			SetColor(11,0);
		}
		cout << "\nHeight(cm): ";
		cin >> height;
		while (cin.fail() || height < 140 || height > 210) {		//Input validation
			SetColor(4,0);
			cout << "Invalid input! Please enter a valid height: ";
			cin.clear();
			cin.ignore(INT_MAX, '\n');
			cin >> height;
			SetColor(11,0);
		}
		if (gender == 'M' || gender == 'm') {
			RMR = 88.362 + (13.397 * weight) + (4.799 * height) - (5.677 * static_cast<double>(age));		//Calculate RMR information
		}
		else if (gender == 'F' || gender == 'f') {
			RMR = 447.593 + (9.247 * weight) + (3.098 * height) - (4.330 * static_cast<double>(age));
		}
	}
	system("CLS");
	title();
	cout << "                                                                       CALORIES TARGET INFORMATION" << endl;
	cout << line << endl;
	cout << "Name: " << name;
	if (choice == 1) {
		cout << "\t\tStaff IC: ";
		if (IC / 1000000000 == 0) {
			cout << "000" << IC << endl;
		}
		else if (IC / 10000000000 == 0) {
			cout << "00" << IC << endl;
		}
		else if (IC / 100000000000 == 0) {
			cout << "0" << IC << endl;
		}
		else if (IC / 1000000000000 == 0) {
			cout << IC << endl;
		}
	}
	cout << "Gender: " << gender << "\t\tAge: " << age << "\t\tWeight: " << weight << "\t\tHeight: " << height << endl << endl;
	cout << "Choose your average avtivity level in a week:" << endl;		//Menu showing all choices of activity level
	cout << "1  Sedentary (little or no exercise, desk job)" << endl;
	cout << "2  Lightly active (light exercise/ sports 1-3 days per week)" << endl;
	cout << "3  Moderately active (moderate exercise or sports 6-7 days per week)" << endl;
	cout << "4  Very active (hard exercise every day or exercising twice a day)" << endl;
	cout << "5  Extra active (hard exercise 2 or more times per day or training for marathon, triathlon, etc)" << endl;
	cout << "Choice: ";
	cin >> choice2;
	while (cin.fail() || choice2 > 5 || choice2 <= 0) {		//Input validation
		SetColor(4,0);
		cout << "Invalid input! Please enter a valid choice: ";
		cin.clear();
		cin.ignore(INT_MAX, '\n');
		cin >> choice2;
		SetColor(11,0);
	}
	system("CLS");
	title();
	cout << "                                                                       CALORIES TARGET INFORMATION" << endl;
	cout << line << endl;
	string sen1 = "Hi! ", sen2 = ". Nice to meet you. The total calories needed to maintain your weight is ", dot = ". ", sen3 = "In order to lose weight, you need to consume fewer calories than ",
		sen4 = " everyday, increase your activity level or do both.", activityLvl = " ", sen5 = "Thank you for using Let's Get Fit!";
	switch (choice2){
	case 1: {activityLvl = "Sedentary";
		calories = RMR * 1.2;
		break;
	}
	case 2: {activityLvl = "Lightly active";
		calories = RMR * 1.375;
		break;
	}
	case 3: {activityLvl = "Moderately active";
		calories = RMR * 1.55;
		break;
	}
	case 4: {activityLvl = "Very active";
		calories = RMR * 1.725;
	}
	case 5: {activityLvl = "Extra active";
		calories = RMR * 1.9;
		break;
	}
	}

	cout << "Name: " << name;		//Display calories target information
	if (choice == 1) {
		cout << "\t\tStaff IC: " << IC << endl;
	}
	cout << "Gender: " << gender << "\t\tAge: " << age << "\t\tWeight: " << weight << "\t\tHeight: " << height << "\t\tActivity level: " << activityLvl << endl << endl;
	cout << sen1 << name << sen2 << calories << dot << endl;
	cout << sen3 << calories << sen5 << endl;
	system("pause");
	system("CLS");
	title();
	cout << "Back to main programme..." << endl;
	system("pause");
	system("CLS");
}

void deleteInfo(dataStorage staff[], int& numData){
	bool found = false;
	int choice = 0;
	string line = "======================================================================================================================================================================================";
	string name, inputIC;
	title();
	cout << "                                                                       DELETE STAFF INFORMATION" << endl;
	cout << line << endl;
	cout << "\nSearch staff by:\n1  Name\n2  Staff IC\nChoice: ";
	cin >> choice;
	while (cin.fail() || choice > 2 || choice <= 0) {		//Input validation
		SetColor(4,0);
		cout << "Invalid input! Please enter a valid choice: ";
		cin.clear();
		cin.ignore(INT_MAX, '\n');
		cin >> choice;
		SetColor(11,0);
	}
	system("CLS");
	title();
	cout << "                                                                       DELETE STAFF INFORMATION" << endl;
	cout << line << endl;
	switch (choice) {
	case 1: {
		cout << "\nSearch Name (max 31 characters including blank space): ";
		cin.clear();
		cin.ignore(INT_MAX, '\n');
		getline(cin, name);
		for (int j = 0; name[j] != '\0'; j++) {
			if (name.length() >= 32 || isdigit(name[j]) != 0 || ispunct(name[j]) != 0) {		//Input validation
				SetColor(4,0);
				cout << "Invalid name format input! Please enter a valid name: ";
				cin.clear();
				getline(cin, name);
				j = -1;
				SetColor(11,0);
			}
		}
		for (int i = 0; i < numData; i++) {
			if (staff[i].getName() == name) {		//Find the specific staff using name
				found = true;
				system("CLS");
				title();
				cout << "                                                                       DELETE STAFF INFORMATION" << endl;
				cout << line << endl;
				cout << setw(8) << "NAME\t\t\t\tSTAFF IC\tGENDER\t\tAGE\tDATE OF BIRTH\tWEIGHT(kg)\tHEIGHT(cm)\tBMI\t\tBMR\t\tRMR\t\tWEIGHT CATEGORY" << endl;
				cout << "\t\t\t\t\t\t\t\t\t(dd/mm/yy)" << endl;
				cout << line << "\n\n";
				cout << staff[i].getName();
				cout << setw(31 - staff[i].getName().size());
				if (staff[i].getStaffIC() / 1000000000 == 0) {
					cout << "\t000" << staff[i].getStaffIC();
				}
				else if (staff[i].getStaffIC() / 10000000000 == 0) {
					cout << "\t00" << staff[i].getStaffIC();
				}
				else if (staff[i].getStaffIC() / 100000000000 == 0) {
					cout << "\t0" << staff[i].getStaffIC();
				}
				else if (staff[i].getStaffIC() / 1000000000000 == 0) {
					cout << "\t" << staff[i].getStaffIC();
				}
				cout << "\t" << staff[i].getGender();
				cout << "\t\t" << staff[i].getAge();
				cout << "\t" << staff[i].getDD();
				cout << "/" << staff[i].getMM();
				cout << "/" << staff[i].getYYYY();
				cout << "\t" << staff[i].getWeight();
				cout << "\t\t" << staff[i].getHeight();
				cout << "\t\t" << staff[i].getBMI();
				cout << "\t\t" << staff[i].getBMR();
				cout << "\t\t" << staff[i].getRMR();
				cout << "\t\t" << staff[i].getWeightCategory() << endl << endl;
				cout << line << endl;
				SetColor(4,0);
				cout << "Are you sure you want to delete the following staff information?\n1  Yes\n2  No\nChoice: ";
				SetColor(11,0);
				cin >> choice;
				while (cin.fail() || choice > 2 || choice <= 0) {		//Input validation
					SetColor(4,0);
					cout << "Invalid input! Please enter a valid choice: ";
					cin.clear();
					cin.ignore(INT_MAX, '\n');
					cin >> choice;
					SetColor(11,0);
				}
				if (choice == 1){
					for (i; i < numData - 1; i++){		//for-loop to delete all that staff information
						staff[i].setPersonalData(staff[i+1].getName(), staff[i+1].getGender(), staff[i+1].getStaffIC());
						staff[i].setFitnessData(staff[i+1].getWeight(), staff[i].getHeight());
						staff[i].calData();
					}
					numData--;
					cout << "Staff information deleted, back to main programme..." << endl;
				}
				else{
					cout << "Staff information not deleted, back to main programme..." << endl;
				}
				system("pause");
				system("CLS");
				break;
			}
		}
		if (found == false) {		//Name entered not found, back to main programme
			SetColor(4,0);
			cout << "Name not found, back to main programme..." << endl;
			SetColor(11,0);
			system("pause");
			system("CLS");
		}
		break;
	}
	case 2: {
		cout << "\nSearch Staff IC(without '-'): ";
		cin.ignore(INT_MAX, '\n');
		getline(cin, inputIC);
		for (int j = 0; inputIC[j] != '\0'; j++) {		//Input validation
			if (inputIC.length() != 12 || isalpha(inputIC[j]) != 0 || ispunct(inputIC[j]) != 0) {
				SetColor(4,0);
				cout << "Invalid IC! Please enter a valid Staff IC: ";
				cin.clear();
				getline(cin, inputIC);
				j = -1;
				SetColor(11,0);
			}
		}
		for (int i = 0; i < numData; i++) {
			if (staff[i].getStaffIC() == realNum(inputIC)) {		//Find the specific staff using staff IC
				found = true;
				system("CLS");
				title();
				cout << "                                                                       DELETE STAFF INFORMATION" << endl;
				cout << line << endl;
				cout << setw(8) << "NAME\t\t\t\tSTAFF IC\tGENDER\t\tAGE\tDATE OF BIRTH\tWEIGHT(kg)\tHEIGHT(cm)\tBMI\t\tBMR\t\tRMR\t\tWEIGHT CATEGORY" << endl;
				cout << "\t\t\t\t\t\t\t\t\t(dd/mm/yy)" << endl;
				cout << line << "\n\n";
				cout << staff[i].getName();
				cout << setw(31 - staff[i].getName().size());
				if (staff[i].getStaffIC() / 1000000000 == 0) {
					cout << "\t000" << staff[i].getStaffIC();
				}
				else if (staff[i].getStaffIC() / 10000000000 == 0) {
					cout << "\t00" << staff[i].getStaffIC();
				}
				else if (staff[i].getStaffIC() / 100000000000 == 0) {
					cout << "\t0" << staff[i].getStaffIC();
				}
				else if (staff[i].getStaffIC() / 1000000000000 == 0) {
					cout << "\t" << staff[i].getStaffIC();
				}
				cout << "\t" << staff[i].getGender();
				cout << "\t\t" << staff[i].getAge();
				cout << "\t" << staff[i].getDD();
				cout << "/" << staff[i].getMM();
				cout << "/" << staff[i].getYYYY();
				cout << "\t" << staff[i].getWeight();
				cout << "\t\t" << staff[i].getHeight();
				cout << "\t\t" << staff[i].getBMI();
				cout << "\t\t" << staff[i].getBMR();
				cout << "\t\t" << staff[i].getRMR();
				cout << "\t\t" << staff[i].getWeightCategory() << endl << endl;
				cout << line << endl;
				SetColor(4,0);
				cout << "Are you sure you want to delete the following staff information?\n1  Yes\n2  No\nChoice: ";
				cin >> choice;
				SetColor(11,0);
				while (cin.fail() || choice > 2 || choice <= 0) {		//Input validation
					SetColor(4,0);
					cout << "Invalid input! Please enter a valid choice: ";
					cin.clear();
					cin.ignore(INT_MAX, '\n');
					cin >> choice;
					SetColor(11,0);
				}
				if (choice == 1){
					for (i; i < numData - 1; i++){		//for-loop to delete all that staff information
						staff[i].setPersonalData(staff[i+1].getName(), staff[i+1].getGender(), staff[i+1].getStaffIC());
						staff[i].setFitnessData(staff[i+1].getWeight(), staff[i].getHeight());
						staff[i].calData();
					}
					numData--;
					cout << "Staff information deleted, back to main programme..." << endl;
				}
				else{
					cout << "Staff information not deleted, back to main programme..." << endl;
				}
				system("pause");
				system("CLS");
				break;
			}
		}
		if (found == false) {		//Staff IC entered not found, back to main programme
			SetColor(4,0);
			cout << "IC not found, , back to main programme..." << endl;
			SetColor(11,0);
			system("pause");
			system("CLS");
		}
		break;
	}
	}
}

void closeFile(dataStorage staff[], int& numData) {		//Output all data to a text file
	ofstream resInfo;
	string fileName, fileExt = ".txt";
	string line = "======================================================================================================================================================================================";

	cout << "Creating a text file containing updated USM staff information...";
	cout << "Enter the text file name: ";
	cin.ignore(INT_MAX, '\n');
	getline(cin, fileName);		//Enter file name to create a text file containing all the staff information with BMI, BMR, RMR and weight categories
	for (int j = 0; fileName[j] != '\0'; j++) {
		if (ispunct(fileName[j]) != 0) {		//Input validation
			SetColor(4,0);
			cout << "Invalid filename format input! Please enter a valid filename: ";
			cin.clear();
			getline(cin, fileName);
			j = -1;
			SetColor(11,0);
		}
	}
	fileName += fileExt;
	resInfo.open(fileName.c_str(), ios::out);
	resInfo << "                                                                         USM STAFF INFORMATION" << endl;
	resInfo << line << "\n\n";
	resInfo << setw(8) << "NAME\t\t\t\tSTAFF IC\tGENDER\t\tAGE\tDATE OF BIRTH\tWEIGHT(kg)\tHEIGHT(cm)\tBMI\t\tBMR\t\tRMR\t\tWEIGHT CATEGORY" << endl;
	resInfo << "\t\t\t\t\t\t\t\t\t(dd/mm/yy)" << endl;
	resInfo << line << "\n";
	resInfo << "TOTAL NUMBER OF USM STAFF: " << numData << endl;
	resInfo << line << "\n\n";
	for (int i = 0; i < numData; i++){
		resInfo << fixed << showpoint << setprecision(2);
		resInfo << staff[i].getName();
		resInfo << setw(31 - staff[i].getName().size());
		if (staff[i].getStaffIC() / 1000000000 == 0) {
			resInfo << "\t000" << staff[i].getStaffIC();
		}
		else if (staff[i].getStaffIC() / 10000000000 == 0) {
			resInfo << "\t00" << staff[i].getStaffIC();
		}
		else if (staff[i].getStaffIC() / 100000000000 == 0) {
			resInfo << "\t0" << staff[i].getStaffIC();
		}
		else if (staff[i].getStaffIC() / 1000000000000 == 0) {
			resInfo << "\t" << staff[i].getStaffIC();
		}
		resInfo << "\t" << staff[i].getGender();
		resInfo << "\t\t" << staff[i].getAge();
		resInfo << "\t" << staff[i].getDD();
		resInfo << "/" << staff[i].getMM();
		resInfo << "/" << staff[i].getYYYY();
		resInfo << "\t" << staff[i].getWeight();
		resInfo << "\t\t" << staff[i].getHeight();
		resInfo << "\t\t" << staff[i].getBMI();
		resInfo << "\t\t" << staff[i].getBMR();
		resInfo << "\t\t" << staff[i].getRMR();
		resInfo << "\t\t" << staff[i].getWeightCategory() << endl << endl;
	}
	resInfo << line;
	resInfo.close();
	system("CLS");
	title();
	cout << "Loading all USM staff information into " << fileName << endl;
	system("pause");
	system("CLS");
	title();
	cout << "THANK YOU..." << endl;
}
