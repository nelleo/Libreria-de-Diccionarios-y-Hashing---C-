#include "List.h"

//
#include <iostream>
using namespace std;
//

using namespace UndavList;
using namespace UndavListIterator;

struct Nodo{
    void* item;
    Nodo* siguiente;
};

struct UndavList::List{
    Nodo* principio;
    Nodo* final;
    int cantidadElementos;
};

List* UndavList::Create(){
    List* nuevaLista = new List;
    nuevaLista->principio = NULL;
    nuevaLista->final = NULL;
    return nuevaLista;
}

Nodo* CrearNodo(void* item){
    Nodo* nuevoNodo = new Nodo;
    nuevoNodo->item = item;
    nuevoNodo->siguiente = NULL;
    return nuevoNodo;
}

void UndavList::PushBack(List* list, void* item){
    Nodo* nuevoNodo = CrearNodo(item);
    if(list->final != NULL){
        list->final->siguiente = nuevoNodo;
        list->final = nuevoNodo;
    }else{
        list->final = nuevoNodo;
        list->principio = nuevoNodo;
    }
    list->cantidadElementos++;
}

void UndavList::PushFront(List* list, void* item){
    Nodo* nuevoNodo = CrearNodo(item);
    if(list->principio != NULL){
        nuevoNodo->siguiente = list->principio;
        list->principio = nuevoNodo;
    }else{
        list->principio = nuevoNodo;
        list->final = nuevoNodo;      
    }
    list->cantidadElementos++;
}

bool UndavList::IsEmpty(const List* list){
    return list->cantidadElementos == 0;
}

struct UndavList::UndavListIterator::ListIterator{
    Nodo* nodoIterador;
};

ListIterator* UndavList::UndavListIterator::Begin(List* list){
      ListIterator* nuevoIterador = new ListIterator;
      nuevoIterador->nodoIterador = list->principio;
      return nuevoIterador;
}

bool UndavList::UndavListIterator::IsEnd(const ListIterator* iterator){
     return iterator->nodoIterador == NULL;
}

void* UndavList::UndavListIterator::GetItem(ListIterator* iterator){
      return iterator->nodoIterador->item;
}

void UndavList::UndavListIterator::Next(ListIterator* iterator){
     iterator->nodoIterador = iterator->nodoIterador->siguiente;
}

void UndavList::UndavListIterator::Destroy(ListIterator* iterator){
      delete iterator;
}

void QuitarPrincipio(List* list){
     Nodo* auxiliar = list->principio;
     list->principio = list->principio->siguiente;
     delete auxiliar;
}

void QuitarFinal(List* list){
    if(!IsEmpty(list)){
		if(list->cantidadElementos==1){
			QuitarPrincipio(list);
		}else{
			Nodo* nodoAEliminar = list->final;
			ListIterator* iterador = Begin(list);
			while(iterador->nodoIterador->siguiente!=nodoAEliminar){
                Next(iterador);
			}
            list->final = iterador->nodoIterador;
			list->final->siguiente = NULL;
			Destroy(iterador);
			delete nodoAEliminar;
		}
	}
}

void QuitarIntermedio(List* list, UndavListIterator::ListIterator* position){
    Nodo* nodoAEliminar = position->nodoIterador;
    ListIterator* iterador = Begin(list);
    Nodo* anterior = NULL;
    while(iterador->nodoIterador!=nodoAEliminar){
        anterior = iterador->nodoIterador;
        Next(iterador);
    }
    Destroy(iterador);
    anterior->siguiente = nodoAEliminar->siguiente;
    delete nodoAEliminar;
}

void UndavList::Remove(List* list, UndavListIterator::ListIterator* position){
    if(!IsEnd(position)){
        if(position->nodoIterador == list->principio){
            QuitarPrincipio(list);
        }else if(position->nodoIterador == list->final){
            QuitarFinal(list);
        }else{
            QuitarIntermedio(list,position);
        }
        list->cantidadElementos--;
    }
}

void UndavList::Destroy(List* list){
    ListIterator* iterador = Begin(list);
    Nodo* nodoAuxiliar = NULL; 
    while(!IsEnd(iterador)){
        nodoAuxiliar = iterador->nodoIterador;
        Next(iterador);
        delete nodoAuxiliar;
    }
    Destroy(iterador);
    delete list;
}
