// Roster.cpp
// Created by Evan Almonte on 10/18/2015.
//
#include "Roster.hpp"
#include "Student.hpp"
#include "Utilities.hpp"
#include <cstdlib>
#include <iostream>

using std::cout;
using std::cin;
using std::istream;
using std::ostream;
using std::string;

Student** createRandomList(int size);

//Constructors
Roster::Roster( ) : courseName(""), courseCode(""), numEnrolled(0), instructor(""),
                    numOfCredits(0), capacity(15), studentList(new Student*[capacity]) {
	for (int i = 0; i < capacity; ++i) {
		studentList[i] = nullptr;
	}
}

string Roster::getCourseCode( ) const {
	return courseCode;
}

Roster::Roster(std::string course, std::string courseNumber, std::string professor, int credits, int maxCapacity) :
	courseName(course), courseCode(courseNumber), numEnrolled(0),
	instructor(professor), numOfCredits(credits), capacity(maxCapacity) {
	if (numOfCredits <= 0 || numOfCredits > 4) {
		cout << "Invalid number of credits given: " << numOfCredits << "\n";
		exit(1);
	}
	studentList = new Student*[capacity];
	for (int i = 0; i < capacity; ++i) {
		studentList[i] = nullptr;
	}
}

Roster::Roster(const Roster& rhs) :
	courseName(rhs.courseName), courseCode(rhs.courseCode), instructor(rhs.instructor),
	numOfCredits(rhs.numOfCredits), capacity(rhs.capacity), studentList(new Student*[capacity]) {
	for (numEnrolled = 0; numEnrolled < rhs.numEnrolled; ++numEnrolled) {
		studentList[numEnrolled] = new Student(*rhs.studentList[numEnrolled]);
	}
}

Roster::~Roster( ) {
	for (int i = 0; i < numEnrolled; ++i) {
		delete studentList[i];
	}
	delete[] studentList;
}

void Roster::addStudent(Student* aStudent) {
	if (numEnrolled == capacity) {
		grow();
	}
	studentList[numEnrolled++] = aStudent;
}

void Roster::addStudent(Student* newStudents[], int numOfStudents) {
	for (int i = 0; i < numOfStudents; ++i , ++numEnrolled) {
		if (numEnrolled == capacity) {
			grow();
		}
		studentList[numEnrolled] = newStudents[i];
	}
}


//Accessors
string Roster::getCourseName( ) const {
	return courseName;
}

string Roster::getInstructorName( ) const {
	return instructor;
}

int Roster::getNumOfCredits( ) const {
	return numOfCredits;
}

//Mutators
void Roster::addStudent( ) {
	Student* aStudent = new Student;
	cin >> *aStudent;
	if (numEnrolled == capacity) {
		grow();
	}
	studentList[numEnrolled++] = aStudent;
}

void Roster::deleteStudent(string lastName) {
	int location = findStudent(lastName);
	if (location != STUDENT_NOT_FOUND && location != DONT_EDIT) {
		delete studentList[location];
		for (int i = location; i < numEnrolled; ++i) {
			studentList[i] = studentList[i + 1];
		}

		studentList[--numEnrolled] = nullptr;
	}
}

void Roster::driver( ) {
	int sizeOfList = 8;
	Student** studentList = createRandomList(sizeOfList);

	addStudent(studentList, sizeOfList);
	cout << *this;
	deleteStudent("ABreU");

	int sizeOfList2 = 2;
	Student** studentList2 = createRandomList(sizeOfList2);
	addStudent(studentList2, sizeOfList2);
	cout << *this;

}

//Miscellaneous Functions
int Roster::findStudent(string lastName) const {
	int* foundStudents = new int[numEnrolled];
	int numFound = findStudentHelper(foundStudents, lastName);
	//If no students are found, return to the caller.
	if (numFound == 0) {
		cout << "No students with a last name of " << lastName << " were found.\n";
		return STUDENT_NOT_FOUND;
	}
	int studentIndex = DONT_EDIT;
	int userChoice;
	cout << "Please choose a student(0 to quit): ";
	userChoice = getYesOrNo ( );
	while (userChoice < 0 || userChoice > numFound) {
		cout << "Please enter a valid number: ";
		cin >> userChoice;
	}
	if (userChoice != 0) {
		studentIndex = foundStudents[userChoice - 1];
	}
	delete[] foundStudents;
	return studentIndex;
}

int Roster::findStudentHelper(int* foundStudents, string lastName) const {
	int numFound = 0;
	for (int i = 0; i < numEnrolled; ++i) {
		if (upperConvert(studentList[i]->getLastName()) == upperConvert(lastName)) {
			cout << numFound + 1 << ". " + studentList[i]->getFullName() + ", " + studentList[i]->getId() + "\n";
			foundStudents[numFound] = i;
			numFound++;
		}
	}
	return numFound;
}

void Roster::search(string lastName) const {
	int location = findStudent(lastName);
	if (location != STUDENT_NOT_FOUND && location != DONT_EDIT) {
		cout << "\n" << *studentList[location];
	}
}

void Roster::sortDown( ) const {
	selectionSortDown(studentList, numEnrolled);
}

void Roster::sortUp( ) const {
	selectionSortUp(studentList, numEnrolled);
}

void Roster::grow( ) {
	int newCapacity = 2 * capacity + 1;
	Student** tempList = new Student*[newCapacity];
	capacity = newCapacity;
	//Fill the array with the current student list.
	for (int i = 0; i < numEnrolled; ++i) {
		tempList[i] = studentList[i];
	}
	//Fill the rest of the array with null pointers.
	for (int i = numEnrolled; i < capacity; ++i) {
		tempList[i] = nullptr;
	}
	delete[] studentList;
	studentList = tempList;
}

//Overloaded Operators
ostream& operator<<(ostream& output, const Roster& currentRoster) {
	output << "==============================\n";
	output << "Course: " << currentRoster.courseName << "\n";
	output << "Course Code: " << currentRoster.courseCode << "\n";
	output << "Instructor: " << currentRoster.instructor << "\n";
	output << "Credits: " << currentRoster.numOfCredits << "\n";
	output << "Students Enrolled: " << currentRoster.numEnrolled << "/" << currentRoster.capacity << "\n";
	output << "______________________________\n";
	for (int i = 0; i < currentRoster.numEnrolled; ++i) {
		output << currentRoster.studentList[i]->getLastName() + ", " + currentRoster.studentList[i]->getFirstName();
		output << ": " << currentRoster.studentList[i]->getId() << "\n";
	}
	output << "------------------------------ \n";

	return output;
}

std::istream& operator>>(std::istream& input, Roster& currentRoster) {
	cout << "Change the course name(Y/N)? ";
	if (getYesOrNo()) {
		cout << "Please enter the course name: ";
		cin >> currentRoster.courseName;
	}
	cout << "Change the course code(Y/N)? ";
	if (getYesOrNo()) {
		cout << "Please enter the course code: ";
		cin >> currentRoster.courseCode;
	}
	cout << "Change the course instructor?(Y/N)? ";
	if (getYesOrNo()) {
		cout << "Please enter the course's instructor: ";
		cin >> currentRoster.instructor;
	}
	cout << "Change the credits awarded upon completion(Y/N)? ";
	if (getYesOrNo()) {
		cout << "Please enter the credits awarded upon completion: ";
		do {
			cout << "Im here\n";
			cin >> currentRoster.numOfCredits;
		} while (currentRoster.numOfCredits < 0 || currentRoster.numOfCredits > 4);
	}
	return input;
}

const Student& Roster::operator[](int index) const {
	if (index < 0 || index >= numEnrolled) {
		cout << "Array index out of bounds: " << index << "\n";
		exit(1);
	}
	return *studentList[index];
}

Roster& Roster::operator=(const Roster& rhs) {
	if (this != &rhs) {
		for (int i = 0; i < numEnrolled; ++i) {
			delete studentList[i];
		}
		delete[] studentList;

		courseName = rhs.courseName;
		courseCode = rhs.courseCode;
		instructor = rhs.instructor;
		numOfCredits = rhs.numOfCredits;
		capacity = rhs.capacity;
		studentList = new Student*[capacity];
		for (numEnrolled = 0; numEnrolled < rhs.numEnrolled; ++numEnrolled) {
			studentList[numEnrolled] = new Student(*rhs.studentList[numEnrolled]);
		}
	}
	return *this;
}

//Generates a random list of students as large as the specified parameter.
Student** createRandomList(int size) {
	Student** studentList = new Student*[size];
	int numOfLastNames = 6;
	string lastNames[] = {"Almonte" , "Petrou", "Capaldo", "Abreu", "McSorley", "Toribio"};

	int numOfFirstNames = 6;
	string firstNames[] = {"Evan", "Andrew", "Joshua", "Max", "Andy", "Alex"};

	int numOfGpas = 6;
	double gpas[] = {3.5, 2.98, 4.0, 2.6, 3.75, 3.9};

	int numOfBirthdays = 5;
	Date birthdays[] = {Date(6, 16, 1995), Date(3, 23, 1992), Date(8, 23, 1998), Date(5, 15, 1990), Date(3, 5, 1995)};

	for (int i = 0; i < size; ++i) {
		string randLast = lastNames[rand() % numOfLastNames];
		string randFirst = firstNames[rand() % numOfFirstNames];
		double randGpa = gpas[rand() % numOfGpas];
		int randCreds = rand() % 117;
		Date randDob = birthdays[rand() % numOfBirthdays];


		studentList[i] = new Student(randLast, randFirst, randGpa, randCreds, randDob, Date());
	}
	return studentList;
}
