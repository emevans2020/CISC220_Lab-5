/*
 * 	hashNode.cpp
 *
 *  Created on: May 3, 2019
 *  Author: Emily Evans
 */

#include <iostream>
#include <stdlib.h>
#include "hashNode.hpp"
using namespace std;

hashNode:: hashNode() { // constructor to initialize everything
	keyword = "";
	values = NULL;
	valuesSize = 0;
	currSize = 0;
}

hashNode:: hashNode(string s){
	keyword = s;
	values = new string[valuesSize]; //dynamically allocated array of valuesSize
	valuesSize = 150; // can be 100 or whatever size I want
	currSize = 0;
}

hashNode:: hashNode(string s, string v) {// in addition, puts a value in the values array and initializes currSize to 1
	keyword = s;
	valuesSize = 150;
	values = new string[valuesSize];
	values[0] = v;
	currSize = 1;
}

/* addValue: adds a new value to the end of the values array, increases currSize, checks to make
 * sure there’s more space, and, if not, calls dblArray()
 */
void hashNode:: addValue(string v){
	if (currSize == valuesSize){
		dblArray();
	}
	values[currSize] = v;
	currSize++;

}

void hashNode:: dblArray(){ //creates a new array, double the length, and copies over the values.
	//sets the values array to be the newly allocated array.
	string *arr = new string [valuesSize*2];
	for (int i = 0; i < (valuesSize*2); i++){
		arr[i] = values[i];
	}
	valuesSize *= 2;
	values = arr;
}

string hashNode:: getRandValue(){
	if(currSize == 0){	//If there’s no values in the value array, then it returns an empty string.
		return "";
	}
	else {
		int random = rand()%currSize;	// returns a random string from the values array.
		return values[random];
	}
}
