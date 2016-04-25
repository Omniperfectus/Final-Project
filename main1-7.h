
// Version: 1.7

#pragma once
// #include <algorithm>		// find
// #include <iostream>		// cin, cout
// #include <sstream>		// isstringstream
#include <string>		// string
#include <vector>			

using namespace std;

struct Word {
	string 	wordName;		// the word itself
	int 	numChars;		// number of characters in word
	int 	count;			// number of times word is used
};

// Structure to hold character and usage count
struct Chars {
	char 	name;		// character name (character name is the char itself)
	int 	num;	// number of times char is used
};

// CONSTANTS
#ifdef _IOSTREAM_
	ifstream inStream;
	ofstream outStream;
#endif

// FUNCTION PROTOTYPES
void 	charToMap(map<char, int>& charMap, string& test);
void 	debugStream(string fileName);	// Opens the debugger file stream
void 	makeLog(string logStream);		// Writes a string of text to the log file
void 	openStream(string fileName);	// Opens input stream from text file
void 	readIn(map<char, int>& charMap, map<string, int>& wordMap, int& numSentences);	// Pulls words out of sentence strings
void	quoteRemoval(string& test);
string 	strContext(string str, int num);
string 	strToLower(string test);
void 	welcomeScreen();
void 	wordToMap(string test, map<string, int>& wordMap); // Read words into word map

// REPORTING FUNCTIONS
void searchChar(map<char, int>& charMap, char string3);
void searchWord(map<string, int>& wordMap, string str);
void showCharUsageReport(map<char, int>& charMap);
void showCountConsonants(map<char, int>& charMap);
void showCountSentences(int numSentences);
void showCountVowels(map<char, int>& charMap);
void showLeastUsedChars(map<char, int>& charMap, vector<Chars>& charVec);
void showLeastUsedWords(vector<Word>& wordVec);
void showLongestWords(vector<Word>& wordCCVec);
void showMostUsedChars(map<char, int>& charMap, vector<Chars>& charVec);
void showMostUsedWords(vector<Word>& wordVec);
void showShortestWords(vector<Word>& wordCCVec);

// REPORT SUPPORTING ROUTINES
int 	charCount(string word);	// counts the number of characters in a word
vector<Chars> 	createCharVector(map<char, int>& charMap);
vector<Word> 	createWordCharCountVector(map<string, int>& wordMap);
vector<Word> 	createWordUsageVector(map<string, int>& wordMap);
void 	printCharVector(vector<Chars> charVec); // Prints the ordered vector of characters with 
void 	printWordVector1(vector<Word> wordVec);	// Prints ordered vector of words w/ char counts
void 	printWordVector2(vector<Word> wordVec); // Prints ordered vector of words w/ usage counts
int 	getScale(int num); // Sets the scaling to be used for star output
string 	getSpacing(string str); // Returns contextual spacing based on size of report word
string 	getStars(int num, int scaling); // Converts num to scaled stars for report output

