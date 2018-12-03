#include "pch.h"
#include <iostream>
#include <fstream>
#include <string>
#include <deque>
#include <algorithm>
using namespace std;

bool countDuplicates(string s, int num) {		//takes a string and the desired number of duplicate characters tries to find if a character repeats the desired
	sort(s.begin(), s.end());					//Sorts the string alphabetically
	char current = '1';
	int count = 0;
	for (int c = 0; c < s.length(); c++) {		//reads current chacter and next counts the number of times that character has appeared
		if (current != s.at(c)) {
			if (count == num) return true;		//if any character repeats the desired amount of times end the search
			current = s.at(c);					//otherwise reset the buffer
			count = 1;							//reset the counter
		} else { count++; }
	}
	return false;
}

string findSimilar(string s, deque<string> t) {//takes a string(s) and a vector of strings to compare it to to find a string its similar(1 char difference) to
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
	deque<string> ids, workedIds;
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
		workedIds.pop_front();					//removing the current string from the comparison vector as its isn't neccesary to compare to itself
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