#ifndef HASHING_H_
#define HASHING_H_

#include <iostream>

using namespace std;

#include <cstring>
using std::string;

namespace UndavHashing{
	/*
	 * Precondicion: -
	 * Postcondicion: Devuelve el valor (hash code) de @hashMe
	 */
    int HashINT(int hashMe);
    
	int Hash(string hashMe);
}

#endif
