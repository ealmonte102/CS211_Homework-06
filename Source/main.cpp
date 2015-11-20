//  Created by X Code Testing on 11/6/15.
//  Copyright (c) 2015 Evan Almonte. All rights reserved.
//  main.cpp

#include "Date.h"
#include "Roster.hpp"
#include "Student.hpp"
#include <cstdlib>
#include <ctime>
#include <iostream>

Student** createRandomList (int size);

using std::cout;	
using std::cin;
using std::string;

int main ( ) {
	srand (static_cast<unsigned int>(time (nullptr)));
	Roster* testRoster = new Roster ("CS212", "00212", "Gutlove", 4, 0);

	//Make a random list of 8 students, add them to the roster.
	int sizeOfList = 4;
	Student** studentList = createRandomList (sizeOfList);
	testRoster->addStudent (studentList, sizeOfList);
	
	testRoster->driver ( );
	cout << *testRoster;
	
	delete testRoster;
	
	cout << "Students were not deleted." << "\n";
	for (int i = 0; i < sizeOfList; ++i) {
		cout << *studentList[i] << "\n";
	}
	return 0;
}


//Generates a random list of students as large as the specified parameter.
Student** createRandomList (int size) {
	Student** studentList = new Student*[size];
	int numOfLastNames = 6;
	string lastNames[] = { "Almonte" , "Petrou", "Capaldo", "Abreu", "McSorley", "Toribio" };

	int numOfFirstNames = 6;
	string firstNames[] = { "Evan", "Andrew", "Joshua", "Max", "Andy", "Alex" };

	int numOfGpas = 6;
	double gpas[] = { 3.5, 2.98, 4.0, 2.6, 3.75, 3.9 };

	int numOfBirthdays = 5;
	Date birthdays[] = { Date (6, 16, 1995), Date (3, 23, 1992), Date (8, 23, 1998), Date (5, 15, 1990), Date (3, 5, 1995) };

	for (int i = 0; i < size; ++i) {
		string randLast = lastNames[rand ( ) % numOfLastNames];
		string randFirst = firstNames[rand ( ) % numOfFirstNames];
		double randGpa = gpas[rand ( ) % numOfGpas];
		int randCreds = rand ( ) % 117;
		Date randDob = birthdays[rand ( ) % numOfBirthdays];


		studentList[i] = new Student (randLast, randFirst, randGpa, randCreds, randDob, Date ( ));
	}
	return studentList;
}
