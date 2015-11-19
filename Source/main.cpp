//  Created by X Code Testing on 11/6/15.
//  Copyright (c) 2015 Evan Almonte. All rights reserved.
//  main.cpp

#include "Roster.hpp"
#include <cstdlib>
#include <ctime>
#include <iostream>

using std::cout;	
using std::cin;
using std::string;

int main ( ) {
	srand (static_cast<unsigned int>(time (nullptr)));
	
	Roster* testRoster = new Roster ("CS212", "00212", "Gutlove", 4, 0);
	testRoster->driver ( );
	
	delete testRoster;
	return 0;
}
