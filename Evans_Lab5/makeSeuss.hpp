/*
 * 	makeSeuss.hpp
 *  Created on: May 3, 2019
 *  Author: Emily Evans
 *  This header file contains code provided by Professor Yarrington
 */

#ifndef MAKESEUSS_HPP_
#define MAKESEUSS_HPP_
#include "hashMap.hpp"
#include "hashNode.hpp"
#include <stdlib.h>
#include <time.h>
#include <iostream>
using namespace std;

class makeSeuss {
	hashMap *ht;
	string fn; // file name for input (“DrSeuss.txt”)
	string newfile; // name of output file

public:
	makeSeuss(string file,string newf,bool h1, bool c1);
	void readFile();
	void writeFile();
};

#endif /* MAKESEUSS_HPP_ */
