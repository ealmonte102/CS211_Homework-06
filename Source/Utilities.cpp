// Utilities.cpp
// Created by Evan Almonte on 10/18/2015.
//
#include "Utilities.hpp"
#include <cctype>
#include <iostream>
#include <string>

using std::cin;
using std::cout;
using std::string;

bool getYesOrNo ( ) {
	char answer;
	cin >> answer;
	while (answer != 'Y' && answer != 'y' && answer != 'N' && answer != 'n') {
		cin >> answer;
	}
	switch (answer) {
		case 'y':
		case 'Y':
			return true;
		case 'n':
		case 'N':
		default:
			return false;
	}
}

int getValidInt( ) {
	int numToReturn;
	while(! (cin >> numToReturn)) {
		cin.clear ( );
		cin.ignore (100, '\n');
	}
	return numToReturn;
}

string upperConvert (string data) {
	for (unsigned int i = 0; i < data.length ( ); ++i) {
		data[i] = static_cast<char>(toupper (data[i]));
	}
	return data;
}
