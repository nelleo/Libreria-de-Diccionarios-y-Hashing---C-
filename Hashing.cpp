#include "Hashing.h"
#include <sstream>
#include <string>

using namespace UndavHashing;

const int numeroPrimo = 173;

typedef unsigned long int uint64_t;

// 64-bit hash for 64-bit platforms 
//la versión original fue modificada para facilitar la comprecion del algoritmo
uint64_t MurmurHash64A (const void * cadenaAHashear,int len,unsigned int seed){
	const uint64_t m = 0xc6a4a;
	const int r = 47;
	uint64_t h = seed ^ (len * m);
	const uint64_t * data = (const uint64_t *)cadenaAHashear;
	const uint64_t * end = data + (len/8);
	while(data != end)
	{
		uint64_t k = *data++;
		k *= m; 
		k ^= k >> r; 
		k *= m; 
		h ^= k;
		h *= m; 
	}
	const unsigned char * data2 = (const unsigned char*)data;
	switch(len & 7)
	{
		case 7: h ^= uint64_t(data2[6]) << 48;
		break;
		case 6: h ^= uint64_t(data2[5]) << 40;
		break;
		case 5: h ^= uint64_t(data2[4]) << 32;
		break;
		case 4: h ^= uint64_t(data2[3]) << 24;
		break;
		case 3: h ^= uint64_t(data2[2]) << 16;
		break;
		case 2: h ^= uint64_t(data2[1]) << 8;
		break;
		case 1: h ^= uint64_t(data2[0]);
		break;
		default:h *= m;
	};
	h ^= h >> r;
	h *= m;
	h ^= h >> r;
	return h;
} 

int UndavHashing::Hash(string hashMe){
	const char* cadenaAHashear = hashMe.c_str();
	int len = strlen(cadenaAHashear);
	unsigned int seed = int ('M');
	return  MurmurHash64A (cadenaAHashear,len, seed );
}


int UndavHashing::HashINT(int hashMe){
	std::string hashMeStr;
	std::stringstream cadenaDeFlujo;
	cadenaDeFlujo << hashMe;
	hashMeStr =cadenaDeFlujo.str();
	const char* cadenaAHashear = hashMeStr.c_str();
	int len = strlen(cadenaAHashear);
	unsigned int seed = int ('M');
	return  MurmurHash64A (cadenaAHashear,len, seed );
}
