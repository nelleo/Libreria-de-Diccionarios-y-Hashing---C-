#ifndef ITEM_H_
#define ITEM_H_

#include <string>
using std::string;

namespace UndavItem{
	struct Item;

	/*
	 * Precondicion: -
	 * Postcondicion: Devuelve una instancia valida de Item
	 */
	Item* Create(void* item);

	/*
	 * Precondicion: -
	 * Postcondicion: Devuelve el valor de item
	 */
	void* Get(const Item* item);

	/*
	 * Precondicion: @item es una instancia valida
	 * Postcondicion: Libera todos los recursos asociados de @item
	 */
	void Destroy(Item* item);
}

#endif
