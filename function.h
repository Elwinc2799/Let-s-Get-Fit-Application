#ifndef FUNCTION_H
#define FUNCTION_H
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <cmath>
#include <windows.h>
#include "dataStorage.h"
using namespace std;

//Function prototypes
void SetColor(int,int);
void title();
void openFile(dataStorage[], int&, int&);
void sortName(dataStorage[], int&);
void mainMenu(int&);
long long int realNum(string);
bool validIC (string);
bool validName (string);
void displayInfo(dataStorage[], int);
void addModHeader(dataStorage[], int&);
void addInfo(dataStorage[], int&);
void modInfoMenu(dataStorage[], int&);
void modInfo(dataStorage[], int&, int);
void searchFormula(dataStorage[], int&, int, bool&, int[], string, long long int, string, int, int, double, double, double, double, int&);
void searchByWC(dataStorage[], int&, int[], int&, int&);
void searchInfo(dataStorage[], int&, int[]);
void statInfo(dataStorage[], int&, int[], int);
void statInfo2(dataStorage[], int&, int[], int, int);
void numBMI(dataStorage[], int&, int&, int&, int&, int&, int[], int);
void overallInfo(dataStorage[], int&);
void targetInfo(dataStorage[], int&);
void deleteInfo(dataStorage[], int&);
void closeFile(dataStorage[], int&);
#endif
