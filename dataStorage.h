#ifndef DATASTORAGE_H
#define DATASTORAGE_H
#include "personalInfo.h"
#include "fitnessInfo.h"
#include <cmath>

class dataStorage :public personalInfo {		//Derived class from personalInfo class by inheritance, store age, DOB and weightcategory
private:
	long long int staffIC;
	int age, dd, mm, yyyy;
	fitnessInfo fI;		//Composition with fitnessInfo class
	double BMI, BMR, RMR;
	string weightCategory;

public:
	dataStorage() {
		staffIC = age = dd = mm = yyyy = 0;
		BMI = BMR = RMR = 0;
		weightCategory = " ";
	}
	~dataStorage() {
		staffIC = age = dd = mm = yyyy = 0;
		BMI = BMR = RMR = 0;
		weightCategory = " ";
	}
	void setPersonalData(string N, string G, long long int IC) {		//Set name, gender, staff IC, age and DOB
		staffIC = IC;
		setPersonalInfo(N, G);
		int digits = 0, DOB = 0;
		digits = IC / 10000000000;
		if (digits >= 20 && digits <= 99) {
			age = 2020 - (1900 + digits);
			yyyy = digits + 1900;
		}
		else if (digits >= 0 && digits <= 19) {
			age = 2020 - (2000 + digits);
			yyyy = digits + 2000;
		}
		mm = ((IC / 1000000) - (digits * 10000)) / 100;
		dd = ((IC / 1000000) - (digits * 10000)) % 100;
	}
	void setFitnessData(double W, double H) {
		fI.setFitnessInfo(W, H);
	}
	long long int getStaffIC() {
		return staffIC;
	}
	int getAge() {
		return age;
	}
	int getDD() {
		return dd;
	}
	int getMM() {
		return mm;
	}
	int getYYYY() {
		return yyyy;
	}
	double getWeight() {
		return fI.getWeight();
	}
	double getHeight() {
		return fI.getHeight();
	}
	double getBMI() {
		return BMI;
	}
	double getBMR() {
		return BMR;
	}
	double getRMR() {
		return RMR;
	}
	string getWeightCategory() {
		return weightCategory;
	}
	void calData() {		//Calculate and set BMI, BMR, RMR and weight category
		BMI = fI.getWeight() / pow(fI.getHeight(), 2) * 10000;
		if (gender == "Male" || gender == "MALE" || gender == "male") {
			BMR = 10 * fI.getWeight() + 6.25 * fI.getHeight() - static_cast<double>(getAge()) * 5 + 5;
			RMR = 88.362 + (13.397 * fI.getWeight()) + (4.799 * fI.getHeight()) - (5.677 * static_cast<double>(getAge()));
		}
		else if (gender == "Female" || gender == "FEMALE" || gender == "female") {
			BMR = 10 * fI.getWeight() + 6.25 * fI.getHeight() - static_cast<double>(getAge()) * 5 - 161;
			RMR = 447.593 + (9.247 * fI.getWeight()) + (3.098 * fI.getHeight()) - (4.330 * static_cast<double>(getAge()));
		}
		if (BMI >= 0 && BMI < 20) {
			weightCategory = "Underweight";
		}
		else if (BMI >= 20 && BMI < 25) {
			weightCategory = "Normal Weight";
		}
		else if (BMI >= 25 && BMI < 30) {
			weightCategory = "Overweight";
		}
		else if (BMI >= 30) {
			weightCategory = "Obese";
		}
	}
	friend void searchInfo(dataStorage[], int&);
	friend void statInfo(dataStorage[], int&, int[]);
	friend void targetInfo(dataStorage[], int&);
};
#endif
