#include "pch.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <numeric>
#include <unordered_set>
using namespace std;

int main()
{
	vector<int> freqs;
	unordered_set<int> seenFreqs;
	bool notFound = true;
	string line;
	int total = 0;
	ifstream inputFile("input.txt");			//try to open the input file
	if (inputFile.is_open()) {
		while (getline(inputFile, line)) {		//if sucessful get each line in order until there are no more lines
			freqs.push_back(stoi(line));		//add said line into a vector to store in memory as an int
		}
		inputFile.close();
	}
	cout << accumulate(freqs.begin(), freqs.end(), 0) << endl;			//print out the sum of all the frequencies
	while (notFound) {												    //loop though the frequencies until an answer if found
		for (int c : freqs) {											
			if (seenFreqs.insert(total +=c).second){}					//check if a duplicate total freqncy is found by adding a newly calculated total to a HashTable
			else { cout << total << endl; notFound = false;  break; }	//when a frequency fails to be added print out that value and exit out the loops
		}
	}
}