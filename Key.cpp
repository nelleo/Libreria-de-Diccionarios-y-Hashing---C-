#include "Key.h"
#include "Hashing.h"
using namespace UndavKey;
using namespace UndavHashing;

typedef void(*DestroyInnerKey)(void*);

struct UndavKey::Key{
    void* valor;
    CompareKeysFunction funcionComparar;
    HashKeyFunction funcionHashing;
    DestroyInnerKey funcionDestroyKey;
};

int CompararFuncionSTR(void* keyA, void* keyB){
    string claveA = *((string*)keyA);
    string claveB = *((string*)keyB);
    if(claveA == claveB)return 0;
    else if(claveA < claveB)return -1;
    else return 1;
}

int CompararFuncionINT(void* keyA, void* keyB){
    int claveA = *((int*)keyA);
    int claveB = *((int*)keyB);
    if(claveA == claveB)return 0;
    else if(claveA < claveB)return -1;
    else return 1;
}

int HashearSTR(void* key){
    string clave = *((string*)key);
    return UndavHashing::Hash(clave);
}

int HashearINT(void* key){
    int clave = *((int*)key);
    return UndavHashing::HashINT(clave);
}

void DestroyKeySTR(void* innerKey){
	delete (string*)innerKey;
}

void DestroyKeyINT(void* innerKey){
	delete (int*)innerKey;
}

Key* UndavKey::Create(string key){
    string* clave = new string;
    *clave = key;
    Key* nuevaClave = Create(clave,CompararFuncionSTR,HashearSTR);
    nuevaClave->funcionDestroyKey = &DestroyKeySTR;
    return nuevaClave;
}

Key* UndavKey::Create(int key){
    int* clave = new int;
    *clave = key;
    Key* nuevaClave=Create(clave,CompararFuncionINT,HashearINT);
    nuevaClave->funcionDestroyKey = &DestroyKeyINT;
    return nuevaClave;
}

Key* UndavKey::Create(void* key, CompareKeysFunction compareFunction, HashKeyFunction hashKey){
    Key* nuevaClave = new Key;
    nuevaClave->valor = key;
    nuevaClave->funcionComparar = compareFunction;
    nuevaClave->funcionHashing = hashKey;
    return nuevaClave;
}

const void* UndavKey::Get(const Key* key){
    return key->valor;
}

int UndavKey::GetHash(const Key* key){
    return key->funcionHashing(key->valor);
}

bool UndavKey::AreEquals(const Key* keyA, const Key* keyB){
    if(keyA->funcionComparar == keyB->funcionComparar){
    	return (keyA->funcionComparar(keyA->valor,keyB->valor) == 0);
    }
    return false;
}

bool UndavKey::IsLess(const Key* keyA, const Key* keyB){
    if(keyA->funcionComparar == keyB->funcionComparar){
        return (keyA->funcionComparar(keyA->valor,keyB->valor) == -1);
    }
    return false;
}

void UndavKey::Destroy(Key* key){
	key->funcionDestroyKey(key->valor);
}
