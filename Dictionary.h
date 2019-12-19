#ifndef DICTIONARY_H_
#define DICTIONARY_H_

#include "Key.h"
#include "Item.h"

using UndavItem::Item;
using UndavKey::Key;

namespace UndavDictionary{
	struct Dictionary;
	Dictionary* Create();
	void Put(Dictionary* dictionary, Key* key, Item* item);
	Item* Get(const Dictionary* dictionary, Key* key);
	void Remove(Dictionary* dictionary, Key* key);
	bool Contains(const Dictionary* dictionary, Key* key);
	bool IsEmpty(const Dictionary* dictionary);
	int Count(const Dictionary* dictionary);
	namespace UndavDictionaryIterator{
		struct DictionaryIterator;
		DictionaryIterator* Begin(Dictionary* dictionary);
		bool IsEnd(const DictionaryIterator* iterator);
		Key* GetKey(DictionaryIterator* iterator);
		Item* GetValue(DictionaryIterator* iterator);
		void Next(DictionaryIterator* iterator);
		void Destroy(DictionaryIterator* iterator);
	}
	void Destroy(Dictionary* dictionary);
}

#endif
