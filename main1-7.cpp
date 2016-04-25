
//
// Program Name: 	textAnalyzer
// File(s): 		main.cpp, main.h, commandLine.cpp, commandLine.h
// 					utils.cpp, utils.h, [text.dat], [diagnostic.dat]
//
// Authors: 		Jereme Tarr, Jordan Adkins, Zack Hawks
// Class: 			Computer Science 1020 - P70, MW 6:15 - 9:15 PM
// Date: 			04/24/2016
// Version: 		1.7
//
// In This Version: 		Building Program
// In This Subversion: 		Clean up and comment for submission
// In the Last Subversion:  Adding word usage reports
//
//
// =============================================================================

/*
PROGRAM DESCRIPTION:

Program will read in any length of text from a .dat file [ text.dat ].  Both
words and individual characters will be parsed and counted to allow statistical
analysis.  Program will give the user options to view reports on the gathered
statistics using command lines.

NOTE:
Before executing program, please make sure that you have a file to read from
(e.g. text.dat) and a file to write diagnostic logs to (e.g. diagnostic.dat) in
the same directory as the program.
*/

// =============================================================================

#include <algorithm>		// readIn()
#include <cstdlib> 			// exit
#include <fstream> 			// ifStream and ofStream
#include <iostream>
#include <map>				// stl map (associative array indexed by keys)
#include <string>			// getline()
#include <sstream>			// isstringstream
#include <stdio.h> 			// printf, scanf, puts, NULL, difftime
#include <time.h>			// difftime
#include <unistd.h>			// usleep
#include <vector>

// When not commented out, allows debugging content to be written out to a
// diagnostic.dat file
#define _DEBUGGER_
#define _IOSTREAM_


#include "main1-7.h"
#include "utils.h"
#include "commandLine1-5.h"

using namespace std;

int main() {
	// Local Variables
	time_t start_t;		// start time of program
	time_t end_t;		// recorded end time
	double diff_t;		// difference between start_t & end_t
	string cTime;		// current runtime formatted as text

	string 	fileName;			// used to store the name of the .dat file containing text
	string 	debuggerFileName;	// name of the debugger file (i.e., diagnostic.dat)

	int 	numSentences = 0;		// Keeps count of number of sentences in .dat read file

	// Capture start time of the program
	time(&start_t);

	// If debugger is defined in header, open output file stream called debugStream
	#ifdef _DEBUGGER_
		clearScreen();
		cout << "\033[22;32m=====  FILE TO WRITE DIAGNOSTIC LOGS TO  =====\033[0m" << endl << endl;
		debuggerFileName = getFileName();
		debugStream(debuggerFileName);
		makeLog("Beginning Log File...");
		outStream << "Beginning time of the program is " << start_t << endl;
	#endif

	// Initialize STL map data structures
	map<string, int> wordMap;
	map<char, int> charMap;

	welcomeScreen();

	// Read in and validate input filename from user
	clearScreen();
	cout << "\033[22;32m======  FILE TO READ AND ANALYZE  ======\033[0m" << endl << endl;
	fileName = getFileName(); // getFileName located in utils.cpp
	openStream(fileName);

	// read in all text from text.dat file
	readIn(charMap, wordMap, numSentences);

	// Create instance of commandLine object, pass both maps, and debugger stream
	commandLine cmd(wordMap, charMap, numSentences, outStream);
	// Get user command
	cmd.getCommand();

	// Close ifstream and ofstream
	inStream.close();
	#ifdef _DEBUGGER_
		getTime(start_t, end_t, diff_t);				// Update diff_t
		cTime = currentTime(start_t, end_t, diff_t);	// Get current runtime formatted as string
		makeLog("Ending Program Normally");
		outStream << "Total Program Runtime: " << cTime << endl << endl;
		outStream.close();
	#endif
} // Closing brace for main()


// =============================  FUNCTIONS  =====================================
// Grouped by Context then listed Alphabetically

// INDEX OF FUNCTIONS

// void 	charToMap(map<char, int>& charMap, string& test);
// void 	debugStream(string fileName);	// Opens the debugger file stream
// void 	makeLog(string logStream);		// Writes a string of text to the log file
// void 	openStream(string fileName);	// Opens input stream from text file
// void 	readIn(map<char, int>& charMap, map<string, int>& wordMap, int& numSentences);	// Pulls words out of sentence strings
//string 	strContext(string str, int num);
// string 	strToLower(string test);
// void 	welcomeScreen();
// void 	wordToMap(string test, map<string, int>& wordMap); // Read words into word map

// REPORTING FUNCTIONS
// void searchChar(map<char, int>& charMap, char string3);
// void searchWord(map<string, int>& wordMap, string str);
// void showCharUsageReport(map<char, int>& charMap);
// void showCountConsonants(map<char, int>& charMap);
// void showCountSentences(int numSentences);
// void showCountVowels(map<char, int>& charMap);
// void showLeastUsedChars(map<char, int>& charMap, vector<Chars>& charVec);
// void showLeastUsedWords(vector<Word>& wordVec);
// void showLongestWords(vector<Word>& wordCCVec);
// void showMostUsedChars(map<char, int>& charMap, vector<Chars>& charVec);
// void showMostUsedWords(vector<Word>& wordVec);
// void showShortestWords(vector<Word>& wordCCVec);

// REPORT SUPPORTING ROUTINES
// int 		charCount(string word);	// counts the number of characters in a word
// vector<Chars> 	createCharVector(map<char, int>& charMap);
// vector<Word> 	createWordCharCountVector(map<string, int>& wordMap);
// vector<Word> 	createWordUsageVector(map<string, int>& wordMap);
// void 	printCharVector(vector<Chars> charVec); // Prints the ordered vector of characters with
// void 	printWordVector1(vector<Word> wordVec);	// Prints ordered vector of words w/ char counts
// void 	printWordVector2(vector<Word> wordVec); // Prints ordered vector of words w/ usage counts
// int 		getScale(int num); // Sets the scaling to be used for star output
// string 	getSpacing(string str); // Returns contextual spacing based on size of report word
// string 	getStars(int num, int scaling); // Converts num to scaled stars for report output

// FUNCTION: charToMap()
//
// DESCRIPTION:
// This function will take the string 'test' and add each individual character
// to the character map, 'map<char, int> charMap'(in main), and set its value to
// 1 if it is not in the map already. if character is already in the map, it will
// add 1 to the value of the character in the map.
// PARENT FUNCTION: Called in readIn()
// AUTHOR: Zack Hawks
void charToMap(map<char, int>& charMap, string& test) {

	for (int i = 0; i < test.length(); i++){
			//add to map
			//if credintials already exist in the map
			if (charMap[test.at(i)] >= 1) {
				//add one to the character count of the specific character
				charMap[test.at(i)]++;
			}
			//if credintials do not exist in the map
			else {
				//character only exists once
				charMap[test.at(i)] = 1;
			}
	}
}

// FUNCTION: debugStream()
//
// DESCRIPTION:
// Gets handed a string which contains the filename log files will be written to.  Opens the file.
// If file fails to open, exits the program.  Else, outputs that file was successfully opened
// #include <cstdlib> for exit()
// AUTHOR: Jereme Tarr
void debugStream(string fileName) {

	outStream.open(fileName.c_str());
	if (outStream.fail()) {
		cout << "\033[22;31mFailed to open " << fileName << "\033[0m" << endl;
		cout << "\033[22;31mAborting program...\033[0m" << endl;
		exit(1);
	}
	else {
		cout << "\033[22;32mSuccessfully opened "<< fileName << "!\033[0m" << endl << endl;
	}
}

// FUNCTION: makeLog()
//
// DESCRIPTION:
// Function gets handed a string, which it writes to our log file (diagnostic.dat) followed
// by a new line.
// AUTHOR: Jereme Tarr
void makeLog(string logStream) {
	outStream << logStream << endl;
}


// FUNCTION: openStream()
//
// DESCRIPTION:
// Gets handed a string which contains the filename to open.  Opens the file.  If file fails to
// open, exits the program.  Else, outputs that file was successfully opened
// #include <cstdlib> for exit()
// Jereme Tarr
void openStream(string fileName) {

	inStream.open(fileName.c_str());
	if (inStream.fail()) {
		cout << "\033[22;31mFailed to open " << fileName << "\033[0m" << endl;
		cout << "\033[22;31mAborting program...\033[0m" << endl;
		exit(1);
	}
	else {
		cout << "\033[22;32mSuccessfully opened "<< fileName << "!\033[0m" << endl << endl;
	}
}

// quoteRemoval removes any quotation marks within the dat file.
// Zack Hawks
void quoteRemoval(string& test) {
    //this function will determine if each word began or ended
    //  with quotation marks, if it did, then quotation marks
    //  will be removed.
    
    //if first character in 'test' is the beginning of a quote
    //   remove it from the string.
    if (test.at(0) == '"')
        test = test.substr(1, test.length());
    //if last character in 'test' is the end of a quote
    //  remove it from the string.
    if (test.at(test.length()-1) == '"')
        test = test.substr(0, test.length()-1);
}

// numSentences called by reference to allow it to be updated without being returned.
// Zack Hawks
void readIn(map<char, int>& charMap, map<string, int>& wordMap, int& numSentences)  {
	string test;

	#ifdef _DEBUGGER_
		makeLog("readIn() Called...");
	#endif

	while(!inStream.eof()) {
		//store word at the front..
		inStream >> test;
		//check for eof()
		if (inStream.eof())
			break;

		charToMap(charMap, test);

		// convert test string to all lowercase
		test = stringToLower(test);

		//check if word contains punctuation in order to keep count on numSentences...
		quoteRemoval(test);
		int look1 = test.find(".");
		int look2 = test.find("!");
		int look3 = test.find("?");
		int look4 = test.find(",");

		//if last character is !, ., or ?...
		if (look1 > 0) {
			test = test.substr(0, (test.size()-1));
			numSentences++;
		}
		else if (look2 > 0) {
			test = test.substr(0, (test.size()-1));
			numSentences++;
		}
		else if(look3 > 0) {
			test = test.substr(0, (test.size()-1));
			numSentences++;
		}
		else if(look4 > 0) {
			test = test.substr(0, (test.size()-1));
			//dont add to numSentences
		}

		#ifdef _DEBUGGER_
			outStream << "text = " << test << endl;
		#endif

		wordToMap(test, wordMap);

		#ifdef _DEBUGGER_
			outStream << "Word entered into wordMap: " << wordMap[test] << endl;
		#endif
	}

	#ifdef _DEBUGGER_
		outStream << "numSentences = " << numSentences << endl;
		makeLog("Ending readIn()");
	#endif
}

// FUNCITON: strContext
//
// DESCRIPTION:
// Function is passed a string in its singular context (e.g. time vs. times).
// If num != 1, an "s" is added to the end of the string and it is returned.
// (e.g. time -> times).
// Author: Jereme Tarr
string strContext(string str, int num) {
	if (num == 1) {
		return(str);
	}
	else {
		str += "s";
		return(str);
	}
}

// AUTHOR: Zack Hawks
string strToLower(string test) {
	//convert to lowercase (using #algorithm)
	transform(test.begin(), test.end(), test.begin(), ::tolower);

	return(test);
}

// FUNCTION: welcomeScreen()
//
// Author: Jereme Tarr
// DESCRIPTION:
// Function is called in main to welcome the user, and give a brief program description
// while the function stalls for 10 seconds under the disguise of "loading..."
// PARENT FUNCTION: Called in main()
void welcomeScreen() {
	int count = 0;
	int numPercent;

	#ifdef _DEBUGGER_
		makeLog("Beginning execution of welcomeScreen()");
	#endif

	while (count < 11) {
		clearScreen();
		cout << "\033[22;32m==========  Welcome to textAnalyzer!  ==========\033[0m";
		cout << endl << endl;
		cout << "This program will analyze any text that you have\n";
		cout << "stored in a .dat file." << endl << endl;

		numPercent = count * 10;
		cout << "loading... " << numPercent << "%";
		cout << endl;
		count++;
		progPause(1);
	}
}


// AUTHOR: Jordan Adkins
void wordToMap(string test, map<string, int>& wordMap) {
	#ifdef _DEBUGGER_
		makeLog("wordToMap() called...");
	#endif

	string lower;

    lower = stringToLower(test);

    if (wordMap[lower] == 0) {
    	wordMap[lower] = 1;
    }
    else {
        wordMap[lower]++;
    }
    #ifdef _DEBUGGER_
    	makeLog("ending wordToMap()...");
    #endif
}

// ========================  REPORTING FUNCTIONS  ================================
// Grouped by Context then listed Alphabetically



// Zack Hawks
void searchChar(map<char, int>& charMap, char string3){
	// convert string3 to uppercase
	// char upper = toupper(string3);
	// add uppercase and lowercase version together in order to find both in map
	// int combinedChar = charMap[upper] + charMap[string3];
	//determine if character exists in map
	int num = charMap[string3];

	// Get contextual string variable (time vs. times) based on num
	string strVar = strContext("time", num);

	if (num >= 1) {
		// Green Message, character found
		cout << endl << "\033[22;32mCharacter \'" << string3 << "\' was found "
		<< num << " " << strVar << ".\033[0m";
		cout << endl << endl;
	}
	//if character does not exists in map, red message
	else {
		cout << endl << "\033[22;31mThe character " << string3 << " was not found...\033[0m";
		cout << endl << endl;
	}
}

// Jereme Tarr, Taken from searchChar() written by Zack Hawks
void searchWord(map<string, int>& wordMap, string str) {

	// Get word usage count form map, store as int num
	int num = wordMap[str];

	// Get contextual string variable (time vs. times) based on num
	string strVar = strContext("time", num);

	if (num >= 1) {
		// Green Message, character found
		cout << endl << "\033[22;32mWord \"" << str << "\" was found "
		<< num << " " << strVar << ".\033[0m";
		cout << endl << endl;
	}
	//if character does not exists in map, red message
	else {
		cout << endl << "\033[22;31mThe word \"" << str << "\" was not found...\033[0m";
		cout << endl << endl;
	}
}

// FUNCTION: showCharUsageReport()
//
// DESCRIPTION:
// Function lists each character in charMap, as well as how many times each
// character was used.
// Jereme Tarr
void showCharUsageReport(map<char, int>& charMap) {
	int count = 0;

	// show content:
	cout << "\033[22;32m==========  CHARACTER USAGE REPORT  ==========\033[0m" << endl;
	cout << "            Character | Times Used" << endl << endl;
	for (std::map<char,int>::iterator it=charMap.begin(); it!=charMap.end(); ++it) {
    	cout << it->first << "|" << it->second << "	";
    	count ++;
    	if (count % 6 == 0) {
    		cout << endl << endl;
    	}
	}
	cout << endl;
}


// Zack Hawks
void showCountConsonants(map<char, int>& charMap) {
	//return the sum of the consonants and their corresponding
	//  capital letter
	int ccount =
	charMap['b'] + charMap['B'] + charMap['c'] + charMap['C'] +
	charMap['d'] + charMap['D'] + charMap['f'] + charMap['F'] +
	charMap['g'] + charMap['G'] + charMap['h'] + charMap['H'] +
	charMap['j'] + charMap['J'] + charMap['k'] + charMap['K'] +
	charMap['l'] + charMap['L'] + charMap['m'] + charMap['M'] +
	charMap['n'] + charMap['N'] + charMap['p'] + charMap['P'] +
	charMap['q'] + charMap['Q'] + charMap['r'] + charMap['R'] +
	charMap['s'] + charMap['S'] + charMap['t'] + charMap['T'] +
	charMap['v'] + charMap['V'] + charMap['w'] + charMap['W'] +
	charMap['x'] + charMap['X'] + charMap['y'] + charMap['Y'] +
	charMap['z'] + charMap['Z'];

	cout << "\033[22;32mThere were " << ccount << " consonants found in the file.\033[0m";
	cout << endl << endl;
}

// Zack Hawks
void showCountSentences(int numSentences) {
	//will reference numSentences from main
	cout << endl;
	cout  << "\033[22;32mNumber of sentences found: " << numSentences << "\033[0m";
	cout << endl << endl;
}

// AUTHOR: Zack Hawks
void showCountVowels(map<char, int>& charMap) {
	//return the sum of the vowels and their corresponding
	//  capital letter
	int vcount =
	charMap['a'] + charMap['A'] + charMap['e'] + charMap['E'] +
	charMap['i'] + charMap['I'] + charMap['o'] + charMap['O'] +
	charMap['u'] + charMap['U'];
	// return(vcount);

	cout << "\033[22;32mThere were " << vcount << " vowels found in the file.\033[0m";
	cout << endl << endl;
}


// AUTHOR: Jereme Tarr
void showLeastUsedChars(map<char, int>& charMap, vector<Chars>& charVec) {
	string stars;
	int scaling;
	string var;
	string spacing;

	cout << "\033[22;32m==========  10 LEAST USED CHARACTERS  ==========\033[0m" << endl;
	cout << endl;

	int j = 0;
	for (std::vector<Chars>::iterator vecIt = charVec.end()-1; vecIt!=charVec.begin(); --vecIt) {
		// convert iterated character number to int count
		int count = vecIt->num;

		// Only on first character iterated
		if (j == 0) {
			// Set scaling to be used for star output
			scaling = getScale(count);

			if (scaling == 1) {
				var = "occurance";
			}
			else {
				var = "occurances";
			}
			cout << "[ each asterisk represents " << scaling << " word ";
			cout << var << " ]" << endl << endl;
		}

		// print out scaled w/ asterisks
		stars = getStars(count, scaling);
		if ((10-j) == 10) {
			cout << "#" << 10-j << "| " << vecIt->name << ": " << stars;
			cout << endl;
		}
		else {
			cout << "#" << 10-j << " | " << vecIt->name << ": " << stars;
			cout << endl;
		}
		j++;
		if (j == 10) {
			cout << endl;
			return;
		}
	}
}

// AUTHOR: Jereme Tarr
void showLeastUsedWords(vector<Word>& wordVec) {
	string stars;
	int scaling;
	string var;
	string spacing;

	cout << "\033[22;32m============  10 LEAST USED WORDS  ============\033[0m" << endl;
	cout << endl;

	int j = 0;
	for (std::vector<Word>::iterator wordIt = wordVec.end()-1; wordIt!=wordVec.begin(); --wordIt) {

		// convert iterated character name to string & iterated number to int count
		int count = wordIt->count;

		// Only on first character iterated
		if (j == 0) {
			// Set scaling to be used for star output
			scaling = getScale(count);

			if (scaling == 1) {
				var = "occurance";
			}
			else {
				var = "occurances";
			}
			cout << "[ each asterisk represents " << scaling << " word ";
			cout << var << " ]" << endl << endl;
		}

		// print out scaled w/ asterisks
		stars = getStars(count, scaling);
		spacing = getSpacing(wordIt->wordName);
		if ((10-j) == 10) {
			cout << "#" << 10-j << "| " << wordIt->wordName << spacing << stars;
			cout << endl;
		}
		else {
			cout << "#" << 10-j << " | " << wordIt->wordName << spacing << stars;
			cout << endl;
		}
		j++;
		if (j == 10) {
			cout << endl;
			return;
		}
	}
}

// AUTHOR: Jereme Tarr
void showLongestWords(vector<Word>& wordCCVec) {
	cout << "\033[22;32m============  10 LONGEST WORDS  ============\033[0m" << endl;
	cout << endl;

	int j = 0;
	for (std::vector<Word>::iterator wordIt = wordCCVec.begin(); wordIt!=wordCCVec.end(); ++wordIt) {
		string stars;
		int scaling;
		string var;
		string spacing;

		// convert iterated character name to string & iterated number to int count
		int count = wordIt->numChars;

		// Only on first character iterated
		if (j == 0) {
			// Set scaling to be used for star output
			scaling = getScale(count);

			if (scaling == 1) {
				var = "occurance";
			}
			else {
				var = "occurances";
			}
			cout << "[ each asterisk represents " << scaling << " character ";
			cout << var << " ]" << endl << endl;
		}
		// print out scaled w/ asterisks
		stars = getStars(count, scaling);
		spacing = getSpacing(wordIt->wordName);
		if ((j+1) < 10) {
			cout << "#" << j+1 << " | " << wordIt->wordName << ": " << spacing << stars << "\n";
		}
		else {
			cout << "#" << j+1 << "| " << wordIt->wordName << ": " << spacing << stars << "\n";
		}
		// cout << "charVec[" << j << "] count: " << vecIt->num << "\n";
		j++;
		if (j == 10) {
			cout << endl;
			return;
		}
	}
}

// AUTHOR: Jereme Tarr
void showMostUsedChars(map<char, int>& charMap, vector<Chars>& charVec) {
	cout << "\033[22;32m============  10 MOST USED CHARACTERS  ============\033[0m" << endl;
	cout << endl;

	int j = 0;
	for (std::vector<Chars>::iterator vecIt = charVec.begin(); vecIt!=charVec.end(); ++vecIt) {
		string stars;
		int scaling;
		string var;

		// convert iterated character name to string & iterated number to int count
		int count = vecIt->num;
		// Only on first character iterated
		if (j == 0) {
			// Set scaling to be used for star output
			scaling = getScale(count);

			if (scaling == 1) {
				var = "occurance";
			}
			else {
				var = "occurances";
			}

			cout << "[ each asterisk represents " << scaling << " character ";
			cout << var << " ]" << endl << endl;
		}
		// print out scaled w/ asterisks
		stars = getStars(count, scaling);
		if ((j+1) < 10) {
			cout << "#" << j+1 << " | " << vecIt->name << ": " << stars << "\n";
		}
		else {
			cout << "#" << j+1 << "| " << vecIt->name << ": " << stars << "\n";
		}
		// cout << "charVec[" << j << "] count: " << vecIt->num << "\n";
		j++;
		if (j == 10) {
			cout << endl;
			return;
		}
	}
}

// AUTHOR: Jereme Tarr
void showMostUsedWords(vector<Word>& wordVec) {
	string stars;
	int scaling;
	string var;
	string spacing;

	cout << "\033[22;32m============  10 MOST USED WORDS  ============\033[0m" << endl;
	cout << endl;

	int j = 0;
	for (std::vector<Word>::iterator wordIt = wordVec.begin(); wordIt!=wordVec.end(); ++wordIt) {
		// convert iterated character name to string & iterated number to int count
		int count = wordIt->count;

		// Only on first character iterated
		if (j == 0) {
			// Set scaling to be used for star output
			scaling = getScale(count);
			if (scaling == 1) {
				var = "occurance";
			}
			else {
				var = "occurances";
			}
			cout << "[ each asterisk represents " << scaling << " word ";
			cout << var << " ]" << endl << endl;
		}
		// print out scaled w/ asterisks
		stars = getStars(count, scaling);
		spacing = getSpacing(wordIt->wordName);
		if ((j+1) < 10) {
			cout << "#" << j+1 << " | " << wordIt->wordName << ": " << spacing << stars << "\n";
		}
		else {
			cout << "#" << j+1 << "| " << wordIt->wordName << ": " << spacing << stars << "\n";
		}
		// cout << "charVec[" << j << "] count: " << vecIt->num << "\n";
		j++;
		if (j == 10) {
			cout << endl;
			return;
		}
	}
}

// AUTHOR: Jereme Tarr
void showShortestWords(vector<Word>& wordCCVec) {
	string stars;
	int scaling;
	string var;
	string spacing;

	cout << "\033[22;32m==========  10 SHORTEST WORDS  ==========\033[0m" << endl;
	cout << endl;

	int j = 0;
	for (std::vector<Word>::iterator wordIt = wordCCVec.end()-1; wordIt!=wordCCVec.begin(); --wordIt) {
		// convert iterated word character count to num
		int count = wordIt->numChars;
		// Only on first character iterated
		if (j == 0) {
			// Set scaling to be used for star output
			scaling = getScale(count);
			if (scaling == 1) {
				var = " character";
			}
			else {
				var = " characters";
			}
			cout << "[ each asterisk represents " << scaling << var << " ]" << endl << endl;
		}
		// print out scaled w/ asterisks
		stars = getStars(count, scaling);
		spacing = getSpacing(wordIt->wordName);
		if ((10-j) == 10) {
			cout << "#" << 10-j << "| " << wordIt->wordName << ": " << spacing << stars;
			cout << endl;
		}
		else {
			cout << "#" << 10-j << " | " << wordIt->wordName <<": " <<  spacing << stars;
			cout << endl;
		}
		j++;
		if (j == 10) {
			cout << endl;
			return;
		}
	}
}

// =======================  REPORT SUPPORTING ROUTINES  ==============================

// AUTHOR: Jereme Tarr
int charCount(string word) {
	int count = 0;
	for (int i=0; i<word.size(); i++) {
		count++;
	}
	return(count);
}


// FUNCTION: createCharVector()
//
// DESCRIPTION:
// Function takes the character map and puts it into an array sorted by the number
// of times each character is used.  Most-used characters are at the beginning of
// the vector.  Least used characters are at the end.  This function allows the
// showMostUsedChars() and showLeastUsedChars() functions to simply traverse the
// vector from either end in order to report.  Function is called only once, upon
// commandLine constructor in order to reduce computing overhead.
// PARENT FUNCTION: commandLine::commandLine()
// AUTHOR: Jereme Tarr
vector<Chars> createCharVector(map<char, int>& charMap) {
	#ifdef _DEBUGGER_
		makeLog("showMostUsedChars() called...");
	#endif

	// vector of Chars structures
	vector<Chars> charVec;
	#ifdef _DEBUGGER_
		outStream << "vector<Chars> charVec created..." << endl;
	#endif

	// Iterate through charMap looking at usage counts
	for (std::map<char, int>::iterator charIt=charMap.begin(); charIt!=charMap.end(); charIt++) {

  		// Vector is empty
		if (charVec.size() == 0) {
			// cout << "vector found to be empty, making new struct" << endl;

			Chars charStruct;
			charStruct.name = charIt->first;
			charStruct.num = charIt->second;
			charVec.push_back(charStruct);
		}
		else {
	  		// Vector is not empty, find slot and insert
	  		// cout << "vector found NOT EMPTY, intializing charVec for-loop" << endl;
	  		for (std::vector<Chars>::iterator vecIt = charVec.begin(); vecIt != charVec.end(); ++vecIt) {

	    		// charMap # is > charVec #.  Insert before
	    		if (charIt->second > vecIt->num) {
	    			// Create new Char Structure
	    			Chars newStruct;
	    			newStruct.name = charIt->first;
	    			newStruct.num = charIt->second;
	    			charVec.insert(vecIt, newStruct);
	    			break;
	    		}
	    		else {
	    			// have come to charVec.end(), push_back
	    			if (vecIt == charVec.end()-1) {
	    				Chars newStruct;
	    				newStruct.name = charIt->first;
	    				newStruct.num = charIt->second;
	    				charVec.push_back(newStruct);
	    				break;
	    			}
	    		} // closing brace for else-statement
	  		} // closing brace vector for-loop
		} // closing brace charMap for-loop
	} // Ending brace for else-statement
	return(charVec);
}

// PARENT FUNCTION: commandLine::commandLine()
// AUTHOR: Jereme Tarr
vector<Word> createWordCharCountVector(map<string, int>& wordMap) {
	int count;

	// vector of Word structures
	vector<Word> wordVec;

	// Iterate through wordMap looking at character counts
	for (std::map<string, int>::iterator wordIt=wordMap.begin(); wordIt!= wordMap.end(); wordIt++) {
		#ifdef _DEBUGGER_
			outStream << endl << "Word to be placed: " << wordIt->first << endl;
	  		// outStream << "wordIt->second: " << wordIt->second << endl;
	  	#endif

  		// Vector is empty
		if (wordVec.size() == 0) {
			#ifdef _DEBUGGER_
				outStream << "vector found to be empty, making new struct" << endl;
			#endif

			Word wordStruct;
			wordStruct.wordName = wordIt->first;
			count = charCount(wordStruct.wordName);
			wordStruct.numChars = count;
			wordVec.push_back(wordStruct);
		}

		else {
	  		// Vector is not empty, find slot and insert
	  		#ifdef _DEBUGGER_
	  			outStream << "vector found NOT EMPTY, intializing wordVec for-loop" << endl;
	  		#endif
	  		for (std::vector<Word>::iterator vecIt = wordVec.begin(); vecIt != wordVec.end(); ++vecIt) {

	    		// charMap # is > wordVec #.  Insert before
	    		if (wordIt->first.size() > vecIt->numChars) {
	    			// Create new Char Structure
	    			Word newStruct;
	    			newStruct.wordName = wordIt->first;
	    			count = charCount(newStruct.wordName);
	    			newStruct.numChars = count;
	    			wordVec.insert(vecIt, newStruct);
	    			break;
	    		}
	    		else {
	    			// have come to wordVec.end(), push_back
	    			if (vecIt == wordVec.end()-1) {
	    				Word newStruct;
	    				newStruct.wordName = wordIt->first;
	    				count = charCount(newStruct.wordName);
	    				newStruct.numChars = count;
	    				wordVec.push_back(newStruct);
	    				break;
	    			}
	    		} // closing brace for else-statement
	  		} // closing brace vector for-loop
		} // closing brace wordMap for-loop
	} // Ending brace for else-statement
	#ifdef _DEBUGGER_
		printWordVector1(wordVec);
	#endif
	return(wordVec);
}

// PARENT FUNCTION: commandLine::commandLine()
// AUTHOR: Jereme Tarr
vector<Word> createWordUsageVector(map<string, int>& wordMap) {
	int count;

	// vector of Word structures
	vector<Word> wordVec;

	// Iterate through wordMap looking at character counts
	for (std::map<string, int>::iterator wordIt=wordMap.begin(); wordIt!= wordMap.end(); wordIt++) {
		#ifdef _DEBUGGER_
			outStream << endl << "Word to place: " << wordIt->first << endl;
	  		outStream << "wordIt->second: " << wordIt->second << endl;
	  	#endif

  		// Vector is empty
		if (wordVec.size() == 0) {
			#ifdef _DEBUGGER_
				outStream << "vector found to be empty, making new struct" << endl;
			#endif
			Word wordStruct;
			wordStruct.wordName = wordIt->first;
			wordStruct.count = wordIt->second;
			wordVec.push_back(wordStruct);
		}

		else {
	  		// Vector is not empty, find slot and insert
	  		#ifdef _DEBUGGER_
	  			outStream << "vector found NOT EMPTY, intializing wordVec for-loop" << endl;
	  		#endif
	  		for (std::vector<Word>::iterator vecIt = wordVec.begin(); vecIt != wordVec.end(); ++vecIt) {
	    		// charMap # is > wordVec #.  Insert before
	    		if (wordIt->second > vecIt->count) {
	    			// Create new Char Structure
	    			Word newStruct;
	    			newStruct.wordName = wordIt->first;
	    			newStruct.count = wordIt->second;
	    			wordVec.insert(vecIt, newStruct);
	    			break;
	    		}
	    		else {
	    			// have come to wordVec.end(), push_back
	    			if (vecIt == wordVec.end()-1) {
	    				Word newStruct;
	    				newStruct.wordName = wordIt->first;
	    				newStruct.count = wordIt->second;
	    				wordVec.push_back(newStruct);
	    				break;
	    			}
	    		} // closing brace for else-statement
	  		} // closing brace vector for-loop
		} // closing brace wordMap for-loop
	} // Ending brace for else-statement
	#ifdef _DEBUGGER_
		printWordVector2(wordVec);
	#endif
	return(wordVec);
}

// FUNCTION: printCharVector()
//
// DESCRIPTION:
// Characters stored in the character map (charMap) are organized by pulling them
// into a vector of Chars structs, which contain the letter (char name) and the
// number of times that character was found in text (int num).  This vector is
// sorted with highest usage characters first, lowest usage characters last.
// When called, this func prints the sorted vector out.
// PARENT FUNCTION: Used for diagnostics, usually in showMostUsedChars()
// AUTHOR: Jereme Tarr
void printCharVector(vector<Chars> charVec) {
	// output charVector
	cout << "DIAGNOSTIC:\n";
	int j = 0;
	for (std::vector<Chars>::iterator vecIt2 = charVec.begin(); vecIt2 != charVec.end(); ++vecIt2) {
		cout << "charVec[" << j << "] char:  " << vecIt2->name << "\n";
		cout << "charVec[" << j << "] count: " << vecIt2->num << "\n";
		cout << endl;
		j++;
	}
}

// FUNCTION: printWordVector()
//
// DESCRIPTION:
// Characters stored in the character map (charMap) are organized by pulling them
// into a vector of Chars structs, which contain the letter (char name) and the
// number of times that character was found in text (int num).  This vector is
// sorted with highest usage characters first, lowest usage characters last.
// When called, this func prints the sorted vector out.
// PARENT FUNCTION: Used for diagnostics, usually in showMostUsedChars()
// AUTHOR: Jereme Tarr
void printWordVector1(vector<Word> wordVec) {
	// output charVector
	outStream << endl << "DIAGNOSTIC: printWordVector1()\n";
	int j = 0;
	for (std::vector<Word>::iterator wordIt = wordVec.begin(); wordIt != wordVec.end(); ++wordIt) {
		outStream << "wordCCVec[" << j << "] word:  " << wordIt->wordName << "\n";
		outStream << "wordCCVec[" << j << "] numChars: " << wordIt->numChars << "\n";
		j++;
	}
	outStream << endl;
}

// AUTHOR: Jereme Tarr
void printWordVector2(vector<Word> wordVec) {
	// output charVector
	outStream << endl << "DIAGNOSTIC: printWordVector2()\n";
	int j = 0;
	for (std::vector<Word>::iterator wordIt = wordVec.begin(); wordIt != wordVec.end(); ++wordIt) {
		outStream << "wordUsageVec[" << j << "] word:  " << wordIt->wordName << "\n";
		outStream << "wordUsageVec[" << j << "] usageCount: " << wordIt->count << "\n";
		j++;
	}
	outStream << endl;
}

// AUTHOR: Jereme Tarr
int getScale(int num) {
	if (num < 50) {
		return(1);
	}
	else if (num >= 50 && num < 100) {
		return(10);
	}
	else if (num >= 100 && num < 1000) {
		return(100);
	}
	else if (num >= 1000 && num < 10000) {
		return(1000);
	}
	else {
		return(1);
	}
}

// AUTHOR: Jereme Tarr
string getSpacing(string str) {
	string spacing;

	if (str.size() < 10) {
		// 2 Tabs
		spacing = "		";
	}
	else if (str.size() <= 10) {
		// 1 Tabs
		spacing = "	";
	}
	else {
		// 1 Tab
		spacing = "	";
	}

	return(spacing);
}

// AUTHOR: Jereme Tarr
string getStars(int num, int scaling) {
	string stars;

	// Apply scaling
	int number = num / scaling;
	// Load stars into string
	for (int i=0; i<number; i++) {
		stars += "*";
	}
	return(stars);
}

