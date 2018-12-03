#include "pch.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

bool countDuplicates(string s, int num) {		//takes a string and the desired number of duplicate characters tries to find if a character repeats the desired
	for (char c = 'a'; c <= 'z'; c++) {			//number of times. goes trhough the alphabet (there's almost certainly a better way of doing this)	
		int count = 0;
		for (char d : s) {
			if (d == c) count++;				//counts the number of times that character has appeared
		}
		if (count == num) return true;			//if any character repeats the desired amount of times end the search
	}
	return false;
}

string findSimilar(string s, vector<string> t) {//takes a string(s) and a vector of strings to compare it to to find a string its similar(1 char difference) to
	for (string u : t) {						//iterate through each string in the vector comparing it to the currently worked string(s)
		int count = 0;
		for (int index = 0; index < u.length(); ++index) {
			if (u[index] != s[index]) count++;	//count the number of times they differ in character in each position
		}
		if (count == 1) return u;				//if they are deemed similar (1 character difference) return the similar string
	}
	return "";
}

int main() {
	vector<string> ids, workedIds;
	string line;
	int twos = 0, threes = 0;
	ifstream inputFile("input.txt");			//open the input file
	if (inputFile.is_open()) {					
		while (getline(inputFile, line)) {		//if sucessful get each line in order until there are no more lines
			ids.push_back(line);				//add said line into a vector to store in memory
		}
		inputFile.close();
	}
	for (string s : ids) {
		if (countDuplicates(s, 2)) twos++;		//for each string stored in the vector check if it has any duplicate characters used exactly twice
		if (countDuplicates(s, 3)) threes++;	//then check if that string has any duplicate letters used exatly 3 times
	}
	cout << twos * threes << endl;				//print out the checksum

	workedIds.insert(workedIds.end(), ids.begin(), ids.end()); //create a copy of the vector to be used for faster searching

	for (string s : ids) {						//loop through the vector
		workedIds.erase(workedIds.begin());		//removing the current string from the comparison vector as its isn't neccesary to compare to itself
		string t = findSimilar(s, workedIds);	//or previous entries. compare the string to all non compared strings
		if (t != "") {							//if a similar (one char difference) has been found 
			for (int index = 0; index < s.length(); index++) {
				if (s[index] == t[index]) {
					cout << s[index];			// print out only the shared characters
				}								
			}
			cout << endl;
			break;								//we can give up now
		}
	}
}