#ifndef PERSONALINFO_H
#define PERSONALINFO_H
#include <iostream>
using namespace std;

class personalInfo {		//Class to store name and gender data
protected:
	string name, gender;

public:
	personalInfo() {
		name = " ";
		gender = " ";
	}
	~personalInfo() {
		name = " ";
		gender = " ";
	}
	void setPersonalInfo(string n, string g) {
		name = n;
		gender = g;
	}
	string getName() {
		return name;
	}
	string getGender() {
		return gender;
	}
};
#endif
