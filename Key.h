#ifndef KEY_H_
#define KEY_H_
#include <string>
using std::string;

namespace UndavKey{
	struct Key;
    
	typedef int (*CompareKeysFunction)(void*,void*);
	typedef int (*HashKeyFunction)(void*);
    
	/*
	 * Precondicion: -
	 * Postcondicion: Devuelve una instancia valida de Key para claves inmutables string
	 */
	Key* Create(string key);

	/*
	 * Precondicion: -
	 * Postcondicion: Devuelve una instancia valida de Key para claves inmutables int
	 */
	Key* Create(int key);

	/*
	 * Precondicion: @compareFunction devuelve 0 si los dos paramteros keys son iguales, devuelve -1 si el primer parametro es menor y devuelve 1 si el primer parametro es mayor.
	 * @hashKey es la funcion de hashing de @key
	 * Postcondicion: Devuelve una instancia valida de Key
	 */
	Key* Create(void* key, CompareKeysFunction compareFunction, HashKeyFunction hashKey);

	/*
	 * Precondicion: -
	 * Postcondicion: Devuelve el valor de key
	 */
	const void* Get(const Key* key);

	/*
	 * Precondicion: -
	 * Postcondicion: Devuelve el valor (hash code) de @key
	 */
	int GetHash(const Key* key);

	/*
	 * Precondicion: keyA y keyB son instancias validas
	 * Postcondioin: Devuleve true si KeyA y KeyB son iguales. Caso contrario devuelve false
	 */
	bool AreEquals(const Key* keyA, const Key* keyB);

	/*
	 * Precondicion: @keyA y @keyB son instancias validas
	 * Postcondioin: Devuelve true si KeyA es menor a KeyB . Caso contrario devuelve false
	 */
	bool IsLess(const Key* keyA, const Key* keyB);

	/*
	 * Precondicion: @key es una instancia valida
	 * Postcondicion: Libera todos los recursos asociados de @key
	 */
	void Destroy(Key* key);
}

#endif
