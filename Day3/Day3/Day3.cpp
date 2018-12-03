#include "pch.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <deque>
#include <string>
#include <sstream>
#include <algorithm>
using namespace std;

struct dataHolder { int x[5]; };

string clean(string str) {
	size_t index = 0;
	replace(str.begin(), str.end(), '#', ' ');
	replace(str.begin(), str.end(), '@', ' ');
	replace(str.begin(), str.end(), ',', ' ');
	replace(str.begin(), str.end(), ':', ' ');
	replace(str.begin(), str.end(), 'x', ' ');
	return str;
}


dataHolder getInts(string str) {
	stringstream stream;
	dataHolder returnVal;
	returnVal.x[0] = 0;
	string current;
	int data, read = -1;
	str = clean(str);
	stream << str;
	while (!stream.eof()) {
		stream >> current;
		if (stringstream(current) >> data) {
			if (read == -1) { returnVal.x[4] = data; read++; }
			else { returnVal.x[read] = data; read++; }
		}
	}
	return returnVal;
}

int main()
{
	vector<dataHolder> data;
	deque<deque<int> > grid;
	const int MINVECTOR = 1000;
	int total = 0;
	ifstream inputFile("input.txt");			//open the input file
	if (inputFile.is_open()) {
		string line;
		while (getline(inputFile, line)) {		//if sucessful get each line in order until there are no more lines
			data.push_back(getInts(line));
		}
		inputFile.close();
	}

	grid.assign(MINVECTOR, deque<int>(MINVECTOR, 0)); //initialise array of 1000 by 1000
	for (dataHolder d : data){
		for (int i = 0; i < 2; i++) {
			//check and fix bounds
			if (i == 0 && (d.x[i] + d.x[i + 2] > grid.size())) {  //if there aren't enough rows add more rows
				for (int y = grid.size(); y < d.x[i] + d.x[i + 2]; y++) { //keep adding rows until enough are added
					grid.push_back(deque<int>(grid[0].size(), 0));
				}
			}else if (i == 1 && (d.x[i] + d.x[i + 2] > grid[0].size())) { //if there aren't enough columns elongate each row
				for (int y = grid[0].size(); y < d.x[i] + d.x[i + 2]; y++) {
					for (deque<int> c : grid) {
						c.push_back(0);
					}
				}
			}
		}
		//add in the data
		for (int x = 0; x < d.x[2]; x++) {
			for (int y = 0; y < d.x[3]; y++) {
				grid[(d.x[0] + x)][(d.x[1] + y)]++;
			}
		}
	}
	//read each overlap
	for (deque<int> c : grid) {
		for (int d : c) {
			if (d > 1) { total++; }
		}
	}
	cout << total << endl;
	// check claim
	for (dataHolder d : data) {
		for (int x = 0; x < d.x[2]; x++) {
			for (int y = 0; y < d.x[3]; y++) {
				if (grid[(d.x[0] + x)][(d.x[1] + y)] == 1) {}
				else { goto weOut; }
			}
		}
		cout << d.x[4];
	weOut:
		;
	}
}

