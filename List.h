#ifndef LIST_H_
#define LIST_H_

namespace UndavList{
	struct List;
	List* Create();
	void PushBack(List* list, void* item);
	void PushFront(List* list, void* item);
	bool IsEmpty(const List* list);
	namespace UndavListIterator{
		struct ListIterator;
		ListIterator* Begin(List* list);
		bool IsEnd(const ListIterator* iterator);
		void* GetItem(ListIterator* iterator);
		void Next(ListIterator* iterator);
		void Destroy(ListIterator* iterator);
	}
	void Remove(List* list, UndavListIterator::ListIterator* position);
	void Destroy(List* list);
}

#endif
