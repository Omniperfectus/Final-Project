Jordan

// AUTHOR: 	Jereme Tarr
// Version 	1.5

#pragma once

#include <map>				// stl map (associative array indexed by keys)
#include <string>

#include "main1-7.h"

using namespace std;


class commandLine {

	public:
		string cmdString;
		string cmdArray[3];
		int numSentences;
		vector<Chars> 		charVec;
		vector<Word> 		wordCCVec;			// Word Character Count Vector
		vector<Word> 		wordUsageVec;		// Number of times word used Vector
		map<string, int> 	wordsList;
		map<char, int> 		charsMap;

		ofstream outStream;

	
		// CONSTRUCTOR
		commandLine(std::map<string, int>& wordList, std::map<char, int>& charMap, int num);
		commandLine(std::map<string, int>& wordList, std::map<char, int>& charMap, int num, ofstream& outPStream);

		// USER COMMAND FUNCTIONS
		void 	doCommand(string cmdString, string cmdArray[]);	// Calls supporting funcs based on cmd
		void 	getCommand();								// Reads in user command line
		void 	invalidCmd();								// User entered Invalid cmd, reprompts
		void 	helpScreen(int context);					// Displays possible user commands
		void 	parseCommand(string cmdString, string cmdArray[]);
		void 	searchFuncs(string cmdArray[]);
		void 	showCountFuncs(string cmdArray[]);			// function call switch starting w/ "show count"
		// function call switch starting w/ "show"
		void 	showFuncs(string cmdString, string cmdArray[]);	
		void 	showLeastUsedFuncs(string cmdArray[]);		// function call switch starting w/ "show leastUsed"
		void 	showMostUsedFuncs(string cmdArray[]);		// function call switch starting w/ "show mostUsed"	
};

