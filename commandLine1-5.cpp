// AUTHOR: 	Jereme Tarr
// Version:	1.5

#include <cstdlib> 			// exit
#include <fstream> 			// ifStream and ofStreamS
#include <map>				// stl map (associative array indexed by keys)
#include <string>			// string
#include <iostream>
#include <sstream>			// isstringstream

// When not commented out, allows debugging content to be written out to a 
// diagnostic.dat file
#define _DEBUGGER_	


#include "commandLine1-5.h"
#include "main1-7.h"
#include "utils.h"


// USER COMMAND FUNCTIONS
// commandLine::commandLine(map<string, Word*> wordList, map<char, int> charMap);
// void 	doCommand(string cmdString, string cmdArray[]);	// Calls supporting funcs based on cmd
// void 	getCommand();					// Reads in user command line
// void 	invalidCmd();					// User entered invalid command, reprompts
// void 	helpScreen(int context);		// Displays possible user commands
// void 	parseCommand(string cmdString, string cmdArray[]);
// void 	searchFuncs(string cmdArray[]);	// Calls appropriate search-based function

//========================= USER COMMANDS FUNCTIONS =========================

// CONSTRUCTOR
commandLine::commandLine(std::map<string, int>& wordList, std::map<char, int>& charMap, int num) {
	numSentences = num;
	wordsList = wordList;
	charsMap = charMap;
	
	// Create ordered vector of characters based on number of times used
	charVec = createCharVector(charsMap);	
	// Create ordered vector of words based on length of word
	wordCCVec = createWordCharCountVector(wordsList);
	// Create ordered vector of words based on number of times used
	wordUsageVec = createWordUsageVector(wordsList);
}

// Overloaded constructor allowing for debugging output file stream to be passed to object
commandLine::commandLine(std::map<string, int>& wordList, std::map<char, int>& charMap, int num, ofstream& outPStream) {
	numSentences = num;
	wordsList = wordList;
	charsMap = charMap;

	// Create ordered vector of characters based on number of times used
	charVec = createCharVector(charsMap);	
	// Create ordered vector of words based on length of word
	wordCCVec = createWordCharCountVector(wordsList);
	// Create ordered vector of words based on number of times used
	wordUsageVec = createWordUsageVector(wordsList);
}


// FUNCTION: doCommand()
//
// DESCRIPTION:
// Function is passed an array containing up to 3 command words.  Function then
// calls the appropriate functions based on the commands entered by the user.
void commandLine::doCommand(string cmdString, string cmdArray[]) {
	int 	caseID;
	string 	string1 = cmdArray[0];
	string 	string2 = cmdArray[1];
	string 	string3 = cmdArray[2]; 

	#ifdef _DEBUGGER_
		makeLog("doCommand() called...");
	#endif

	// Convert command strings to numbers for use in a switch
	if (cmdString == "help") {
		helpScreen(1);
		getCommand();
	}
	else if (cmdString == "exit") {
		#ifdef _DEBUGGER_
			makeLog("case: cmdString == exit");
		#endif
		exit(1);
	}

	if (string1 == "search") {
		searchFuncs(cmdArray);
	}
	else if (string1 == "show") {
		showFuncs(cmdString, cmdArray);
	}
	
	else {
		#ifdef _DEBUGGER_
			makeLog("case: triggered else{}  cmdArray[0] = invalid command");
		#endif
		invalidCmd();	// Display invalid command text, reprompt for user input
	}

	#ifdef _DEBUGGER_
		makeLog("Ending doCommand()");
	#endif
}

// FUNCTION: getCommand()
//
// DESCRIPTION:
// Prompts user to enter a command line, which is read in and then stored as a string.
// LIBRARIES: #include <climits> // INT_MAX
void commandLine::getCommand() {

	#ifdef _DEBUGGER_
		makeLog("getCommand() called");
	#endif


	cout << "Please enter your command.  For a list of all commands\n";
	cout << "please type help" << endl << endl;

	cout << "Command Line > ";
	// cin.clear();
	// cin.ignore(INT_MAX, '\n');
	getline(cin, cmdString);

	#ifdef _DEBUGGER_
		outStream << "cmdString: " << cmdString << endl;
	#endif

	clearScreen();

	parseCommand(cmdString, cmdArray);
	doCommand(cmdString, cmdArray);
}

// FUNCTION: helpScreen()
//
// DESCRIPTION:
// Function is fed an integer, which corresponds to where the user is within the program.
// This allows the function to provide contextually relevant lists of available commands.
// Therefore, the purpose of this function is to show the user all commands available to 
// him/her at that point in the program.
void commandLine::helpScreen(int context) {

	#ifdef _DEBUGGER_
		makeLog("helpScreen() called...");
		outStream << "context = " << context << endl;
	#endif

	clearScreen();

	cout << "\033[22;32m==========================   HELP  FILE   ==========================\033[0m" << endl;
	cout << "AVAILABLE COMMANDS:" << endl << endl;

	if (context == 1) {
		// Indented to display properly in PS11
		cout << "exit 				- exits the program\n";
		cout << "search char X 			- tells how many time character was found\n";
		cout << "search word the 		- tells how many times the word \"the\" was found\n";
		cout << "show charUsage report 		- shows each character used with usage count\n";
		cout << "show count consonants 		- gives total number of consonants found\n";
		cout << "show count vowels 		- gives total number of vowels found\n";
		cout << "show count sentences 		- gives total number of sentences found\n";
		cout << "show longest words 		- shows 10 longest words w/ usage counts\n";
		cout << "show mostUsed chars 		- shows the 10 most used characters w/ usage counts\n";
		cout << "show shortest words 		- shows 10 shortest words w/ usage counts\n";
		cout << "show leastUsed words 		- shows the 10 least used words w/ usage counts\n";
		cout << "show mostUsed words 		- shows the 10 most used words w/ usage counts\n";
	}
	// cout << endl << "press any key twice to continue..." << endl;
	// getch();
	clearScreen(2);
	#ifdef _DEBUGGER_
		makeLog("Ending helpScreen()");
	#endif
}

void commandLine::invalidCmd() {
	cout << endl;
	cout << "\033[22;31mI'm sorry, you have entered an invalid command\033[0m" << endl;
	cout << "\033[22;31mPlease be aware that commands ARE case sensitive\033[0m" << endl << endl;
	cout << "\033[22;31mPlease try again...\033[0m" << endl << endl;
	getCommand();
}

// FUNCTION: parseCommand()
//
// DESCRIPTION:
// Function is passed a string containing the user-input command line.  This function
// parses the command line into individual words and performs error checking on the user's
// inputs.
void commandLine::parseCommand(string cmdString, string cmdArray[]) {
	// Local Variables
	int i = 0;

	// Clear cmdArray
	for (int j=0; j<3; j++) {
		cmdArray[j] = "";
	}

	#ifdef _DEBUGGER_
		makeLog("parseCommand() called...");
	#endif

	istringstream ss(cmdString);
	string token;			// Variable containing one space delimited section of string

	while (getline(ss, token, ' ')) {		// parse out string by spaces, store to "token"
		cmdArray[i] = token;				// store token to commandArray[]
		// DIAGNOSTIC
		#ifdef _DEBUGGER_
			outStream << "cmdArray[" << i << "] = " << token << endl;
		#endif
		i++;								// Advance i to place next token in next array loc
	}

	#ifdef _DEBUGGER_
		makeLog("Ending parseCommand()...");
	#endif
}

// FUNCTION: searchFuncs()
//
// DESCRIPTION:
// Calls appropriate search-based function according to second word in cmdArray[].
// PARENT FUNCTION: Called in doCommand()
void commandLine::searchFuncs(string cmdArray[]) {
	string string2 = cmdArray[1];
	string string3 = cmdArray[2];

	if (string2 == "char") {
		#ifdef _DEBUGGER_
			makeLog("case: string 2 == char");
		#endif

		searchChar(charsMap, string3[0]);
		// cout << endl << "Call searchChar(cmdArray[])" << endl << endl;
		getCommand();
	}
	else if (string2 == "word") {
		#ifdef _DEBUGGER_
			makeLog("case: string 2 == word");
		#endif

		searchWord(wordsList, string3);
		// cout << endl << "Call searchWord(cmdArray[])" << endl << endl;
		getCommand();
	}
	// Invalid Command
	else {
		#ifdef _DEBUGGER_
			makeLog("case: triggered else{}  cmdArray[1] = invalid command");
		#endif
		invalidCmd();
	}
}

void commandLine::showCountFuncs(string cmdArray[]) {
	string string3 = cmdArray[2];

	if (string3 == "consonants") {
		showCountConsonants(charsMap);
		getCommand();
	}
	else if (string3 == "vowels") {
		showCountVowels(charsMap);
		getCommand();
	}
	else if (string3 == "sentences") {
		showCountSentences(numSentences);
		getCommand();
	}
	else {
		invalidCmd();
	}
}

void commandLine::showFuncs(string cmdString, string cmdArray[]) {
	string string2 = cmdArray[1];

	if (cmdString == "show longest words") {
		showLongestWords(wordCCVec);
		getCommand();
	}
	else if (cmdString == "show shortest words") {
		showShortestWords(wordCCVec);
		getCommand();
	}
	else if (cmdString == "show charUsage report") {
		showCharUsageReport(charsMap);
		getCommand();
	}

	if (string2 == "leastUsed") {
		showLeastUsedFuncs(cmdArray);
		getCommand();
	}
	else if (string2 == "mostUsed") {
		showMostUsedFuncs(cmdArray);
	}
	else if (string2 == "count") {
		showCountFuncs(cmdArray);
	}
	else {
		invalidCmd();
	}
}

void commandLine::showLeastUsedFuncs(string cmdArray[]) {
	string string3 = cmdArray[2];


	if (string3 == "words") {
		showLeastUsedWords(wordUsageVec);
		getCommand();
	}
	else if (string3 == "chars") {
		showLeastUsedChars(charsMap, charVec);
	}
	else {
		invalidCmd();
	}
}
void commandLine::showMostUsedFuncs(string cmdArray[]) {
	string string3 = cmdArray[2];


	if (string3 == "chars") {
		showMostUsedChars(charsMap, charVec);
		getCommand();
	}
	else if (string3 == "words") {
		showMostUsedWords(wordUsageVec);
		getCommand();
	}
	else {
		invalidCmd();
	}
}

