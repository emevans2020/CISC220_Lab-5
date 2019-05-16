/*
 * hashMap.cpp
 *
 *  Created on: May 3, 2019
 *      Author: Emily Evans
 */

#include <iostream>
#include <stdlib.h>
#include "hashMap.hpp"
#include "hashNode.hpp"
using namespace std;

/* When creating the map, make sure you initialize the values to NULL so you know whether that
 * index has a key in it or not already. The Boolean values initialize the h1 and the c1 boolean
 * values, making it easier to control which hash and which collision methods you use.
 */
hashMap::hashMap(bool hash1, bool coll1){
	mapSize = 101;
	map = new hashNode*[mapSize];
	for (int i = 0; i<mapSize; i++){
		map[i] = NULL;
	}
	numKeys = 0;
	h1 = hash1;
	c1 = coll1;
	collisionct1 = 0;
	collisionct2 = 0;
}
// adds a node to the map at the correct index based on the key string, and then inserts the value into the value field of the hashNode
// Must check to see whether there's a node at that location. If there's nothing there (it's NULL), add the hashNode with the keyword and value.
// If the node has the same keyword, just add the value to the list of values.
//If the node has a different keyword, keep calculating a new hash index until either the keyword matches the node at that index's keyword, or until the
// map at that index is NULL, in which case you'll add the node there.
//This method also checks for load, and if the load is over 70%, it calls the reHash method to create a new longer map array and rehash the values
//if h1 is true, the first hash function is used, and if it’s false, the second is used.
//if c1 is true, the first collision method is used, and if it’s false, the second is used
void hashMap::addKeyValue(string k, string v){
	int index = 0;
	if ((numKeys+1)/mapSize > .7){
		reHash();
	}

	if (h1 == true){
		index = calcHash(k); // used first hash function
		if (map[index] == NULL){ // if the index at that map is empty make new node!
			map[index] = new hashNode(k,v);
			numKeys++;
		}
		else if (map[index]->keyword == k){			// if same keyword already exists add the value to the keyword
			map[index]->addValue(v);
		}
		else if (c1 == true){			// if collision happens call collHash1
			collisionct1++;
			index = collHash1 (index, k);
			if (map[index] == NULL){
				map[index] = new hashNode(k,v);
				numKeys++;
			}
			else if (map[index]->keyword == k){
				map[index]->addValue(v);
			}
		}
		else if (c1 != true){			// if collision happens call collHash2
			collisionct1++;
			index = collHash2 (index, k);
			if (map[index] == NULL){
				map[index] = new hashNode(k,v);
				numKeys++;
			}
			else if (map[index]->keyword == k){
				map[index]->addValue(v);
			}
		}
	}
	else if (h1 == false){ // you are basically doing the same thing if h1 is false
		index = calcHash2(k);
		if (map[index] == NULL){ // if the index at that map is empty make new node!
			map[index] = new hashNode(k,v);
			numKeys++;
		}
		else if (map[index]->keyword == k){			// if same keyword already exists add the value to the keyword
			map[index]->addValue(v);
		}
		else if (c1 == true){			// if collision happens call collHash1
			collisionct1++;
			index = collHash1 (index, k);
			if (map[index] == NULL){
				map[index] = new hashNode(k,v);
				numKeys++;
			}
			else if (map[index]->keyword == k){
				map[index]->addValue(v);
			}
		}
		else if (c1 != true){			// if collision happens call collHash2
			collisionct1++;
			index = collHash2 (index, k);
			if (map[index] == NULL){
				map[index] = new hashNode(k,v);
				numKeys++;
			}
			else if (map[index]->keyword == k){
				map[index]->addValue(v);
			}
		}
	}
}

// uses calcHash and reHash to calculate and return the index of where the keyword
// k should be inserted into the map array
int hashMap::getIndex(string k){
	int index;
	if ((numKeys+1)/mapSize > .7){
		reHash();
	}
	if(h1==true){
		index = calcHash(k);
	}
	else{
		index = calcHash2(k);
	}
	return index;
}
/*
 * calcHash: This hashing function will take each character from the key and multiply it by a number
 * starting at 0 and then increasing by 1 each time. The total will keep track of the word x number
 * and at the end divide by the mapSize to get the index
 * Ex: Hello
 *  H*0 + e*1 + l*2 + l*3 + o*4
 *
 */
int hashMap::calcHash(string k){ // hash function
	int total = 0;
	int x = 0;
	for (int i = 0; i < k.length(); i++){
		total += k[i]*x;
		x++;
	}
	return total % mapSize;
}
/* This hash method is very similar to Horner’s method for polynomials changed
 * to be used on strings. I chose to use the prime number 37 to multiply with
 * the hashVal
 */
int hashMap::calcHash2(string k){ // hash function 2
	int hashVal = 0;
	for(int i = 0; i < k.length(); i++ ){
		hashVal = ((37 * hashVal + (int)k[i]) % mapSize);
	}
	return hashVal;
}

/* I used a binary search on an array of prime numbers to find the closest prime to
 * double the map Size, and then set mapSize to that new prime. You can include as one
 * of the fields an array of prime numbers, or you can write a function that calculates
 * the next prime number. Whichever you prefer.
 *
 * My function will continue to increase the number of closestPrime after I multiplied mapSize by 2
 * and will increase the number checking each time if it is prime if it is not prime the condition
 * stays false, but when it hits a number that is prime turns closestPrime to true and makes mapSize that prime
 */
int hashMap::getClosestPrime(){
	int closestPrime = mapSize*2;
	bool isPrime = false;

	while (isPrime != true){
		closestPrime ++;
		// Check from 2 to n-1
		for (int i = 2; i < closestPrime/2; i++){
			if (closestPrime % i == 0){
				isPrime = false;
			}
			else {
				isPrime=true;
			}
		}
	}
	return mapSize = closestPrime;
}

void hashMap::reHash(){		// when size of array is at 70%, double array size and rehash keys
	hashNode** tmp = map;
	int tmpSize = mapSize;

	mapSize = getClosestPrime();
	map = new hashNode*[mapSize];
	for (int i = 0; i<mapSize; i++){
		map[i] = NULL;
	}

	for(int i = 0; i < tmpSize; i++){
		if(tmp[i] != NULL){
			for(int j = 0; j < tmp[i]->currSize; j++){
				addKeyValue(tmp[i]->keyword, tmp[i]->values[j]);
			}
		}
	}
} // end rehash

// getting index with collision method 1 (note – you may modify the parameters if you don’t need some/need more)
// linear probing
int hashMap::collHash1(int i, string k){
	int newIndex = i;
	while(map[newIndex % mapSize] != NULL && map[newIndex % mapSize]->keyword != k){
		newIndex=(newIndex+1)%mapSize;
		collisionct2++;
		if (map[newIndex % mapSize] == NULL){
			return newIndex;
		}
		else if(newIndex > mapSize){
			newIndex -= mapSize;
		}
	}
	return newIndex;
}

// getting index with collision method 2 (note – you may modify the parameters if you don’t need some/need more)
//collision handling by quadratic probing
int hashMap::collHash2(int i, string k){
	int newIndex = i;
	int quad = 1;

	while (map[newIndex % mapSize] != NULL && map[newIndex % mapSize]->keyword != k){
		newIndex=(newIndex += quad * quad)%mapSize;
		collisionct2++;
		quad++;
		if (map[newIndex % mapSize] == NULL){
			return newIndex;
		}
		else if(newIndex > mapSize){
			newIndex -= mapSize;
		}
	}
	return newIndex;
}

//finds the key in the array and returns its index. If it's not in the array, void printMap();
//I wrote this solely to check if everything was working.
// DO NOT USE LOOP FOR FIND KEY!
int hashMap::findKey(string k){
	int index = 0;

	if(h1 == true){
		index = calcHash(k);
	}
	else{
		index = calcHash2(k);
	}
	if(map[index]->keyword != k || map[index] == NULL){
		if(map[index]==NULL || map[index]->keyword != k){
			return -1;
		}
		else if (map[index]->keyword == k){
			return index;
		}
		else if (c1 == true){
			index = collHash1(index,k);
		}
		else {
			index = collHash2(index, k);
		}
	}
	return index;
}

void hashMap::printMap(){				// this is mostly helper for fixing code
	cout << endl;
	for(int i=0; i<mapSize; i++){
		if (map[i]!= NULL){
			cout<< map[i]->keyword << ": ";
			cout<< map[i]->values[0]<< endl;
		}
	}
}
