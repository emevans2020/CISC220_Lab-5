/*
 * main.cpp
 *
 *  Created on: May 3, 2019
 *  Author: Emily Evans
 */

#include <iostream>
#include <time.h>
#include "makeSeuss.hpp"
#include "hashMap.hpp"
#include "hashNode.hpp"
using namespace std;

int main() {
	srand(time(NULL));
	makeSeuss("DrSeuss.txt", "test.txt", true, true);
	makeSeuss("DrSeuss.txt", "test2.txt", true, false);
	makeSeuss("DrSeuss.txt", "test3.txt", false, true);
	makeSeuss("DrSeuss.txt", "test4.txt", false, false);
	return 0;
}
