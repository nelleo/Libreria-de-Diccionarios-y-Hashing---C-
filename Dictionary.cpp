#include "Dictionary.h"
using namespace UndavDictionary;
using namespace UndavDictionaryIterator;

const int CapacidadInicial = 5;
const int CantElementsInicial = 0;
const int Inicio = 0;

enum direccion{ derecha , izquierda };

struct UndavDictionary::Dictionary{
    Item** items;
    Key** claves;
    int cantidadElementos;
    int capacidad;
};

Dictionary* UndavDictionary::Create(){
    Dictionary* nuevoDiccionario = new Dictionary;
    nuevoDiccionario->cantidadElementos = CantElementsInicial;
    nuevoDiccionario->capacidad = CapacidadInicial;  
     nuevoDiccionario->items = new Item*[nuevoDiccionario->capacidad];
    nuevoDiccionario->claves = new Key*[nuevoDiccionario->capacidad];
    return nuevoDiccionario;
}

void CorrerUnaPosicionHacia(Dictionary *dictionary,int posicionVacia,direccion direc){
	if(direc==derecha){
		int indiceDesdeDondeCorrer=dictionary->cantidadElementos-1;
		for(int i=indiceDesdeDondeCorrer; i>=posicionVacia;--i){
	 		dictionary->claves[i+1]=dictionary->claves[i];
	 		dictionary->items[i+1]=dictionary->items[i];
		}
		dictionary->claves[posicionVacia]=NULL;
		dictionary->items[posicionVacia]=NULL;	
	}else{
		int indiceDesdeDondeCorrer=posicionVacia;
		for(int i=indiceDesdeDondeCorrer; i<=dictionary->cantidadElementos-1;++i){
	 	dictionary->claves[i]=dictionary->claves[i+1];
	 	dictionary->items[i]=dictionary->items[i+1];
		}
		dictionary->claves[dictionary->cantidadElementos-1]=NULL;
		dictionary->items[dictionary->cantidadElementos-1]=NULL;	
	}
}

int  ObtenerRankingKey(Key** claves, Key* claveBuscada, int indiceUltimaClave){
	int indiceComienzo=indiceUltimaClave-indiceUltimaClave;
	int indiceFin=indiceUltimaClave;
	while(indiceComienzo<=indiceFin){
		int indiceMitad = indiceComienzo +  ((indiceFin - indiceComienzo) /2);
		if(UndavKey::AreEquals(claves[indiceMitad],claveBuscada)){
			return indiceMitad;
		}else{
		    if(UndavKey::IsLess(claveBuscada,claves[indiceMitad])){
                indiceFin = indiceMitad-1;
            }else{
                indiceComienzo = indiceMitad+1;
		    }
        }
    }
	return indiceComienzo;
}


void Redimensionar(Dictionary* dictionary, int capacidadNueva){
	Key** nuevasClaves = new Key*[capacidadNueva];
	Item** nuevosValores = new Item*[capacidadNueva];
	for(int i=0; i<dictionary->cantidadElementos && i <capacidadNueva;++i){
		nuevasClaves[i] = dictionary->claves[i];
		nuevosValores[i] = dictionary->items[i];
	}
	delete [] dictionary->claves;
	delete [] dictionary->items;
	dictionary->claves = nuevasClaves;
	dictionary->items = nuevosValores;
	dictionary->capacidad = capacidadNueva;
}


void Insertar(Dictionary *dictionary, Key* key, Item* item,int indiceDondeInsertar){
    dictionary->claves[indiceDondeInsertar] = key;
    dictionary->items[indiceDondeInsertar] = item;
    dictionary->cantidadElementos++;
}


void UndavDictionary::Put(Dictionary* dictionary, Key* key, Item* item){
    int indiceRankingKey = ObtenerRankingKey(dictionary->claves,key,dictionary->cantidadElementos-1);
    if(UndavKey::AreEquals(dictionary->claves[indiceRankingKey],key)){
        dictionary->items[indiceRankingKey] = item;
    }else{
        if(dictionary->capacidad == dictionary->cantidadElementos){
            Redimensionar(dictionary, dictionary->capacidad * 2);
		}
		if(dictionary->claves[indiceRankingKey]==NULL){
			Insertar(dictionary,key,item,indiceRankingKey);
		}else{
			CorrerUnaPosicionHacia(dictionary,indiceRankingKey,derecha);
			Insertar(dictionary,key,item,indiceRankingKey);
		}
    }
}

Item* UndavDictionary::Get(const Dictionary* dictionary, Key* key){
    	Item* itemObtenido = NULL;
    int indiceRankingKey = ObtenerRankingKey(dictionary->claves,key,dictionary->cantidadElementos-1);
    if(UndavKey::AreEquals(dictionary->claves[indiceRankingKey],key)){
        itemObtenido = dictionary->items[indiceRankingKey];
    }
    return itemObtenido;
}    

void UndavDictionary::Remove(Dictionary* dictionary, Key* key){
    int positionKey =  ObtenerRankingKey(dictionary->claves,key,dictionary->cantidadElementos -1);
    if(UndavKey::AreEquals(dictionary->claves[positionKey],key)){
        CorrerUnaPosicionHacia(dictionary,positionKey,izquierda);
    	dictionary->cantidadElementos--;                  
    }
}

bool UndavDictionary::Contains(const Dictionary* dictionary, Key* key){
    int indiceRankingKey = ObtenerRankingKey(dictionary->claves,key,dictionary->cantidadElementos -1);
    return UndavKey::AreEquals(dictionary->claves[indiceRankingKey],key);
}

bool UndavDictionary::IsEmpty(const Dictionary* dictionary){
     return dictionary->cantidadElementos == CantElementsInicial;
}

int UndavDictionary::Count(const Dictionary* dictionary){
    return dictionary->cantidadElementos;
}

struct UndavDictionary::UndavDictionaryIterator::DictionaryIterator{
       Dictionary* diccionarioIterador;
       int indiceCursor;
       int indiceFinal;
};

DictionaryIterator* UndavDictionary::UndavDictionaryIterator::Begin(Dictionary* dictionary){
      DictionaryIterator* nuevoIterador = new DictionaryIterator;
      nuevoIterador->diccionarioIterador = dictionary;
      nuevoIterador->indiceCursor = Inicio;
      nuevoIterador->indiceFinal = dictionary->cantidadElementos ;
      return nuevoIterador;
}

bool UndavDictionary::UndavDictionaryIterator::IsEnd(const DictionaryIterator* iterator){
     return iterator->indiceCursor == iterator->indiceFinal;
}

Key* UndavDictionary::UndavDictionaryIterator::GetKey(DictionaryIterator* iterator){
     return iterator->diccionarioIterador->claves[iterator->indiceCursor];
}

Item* UndavDictionary::UndavDictionaryIterator::GetValue(DictionaryIterator* iterator){
      return iterator->diccionarioIterador->items[iterator->indiceCursor];
}

void UndavDictionary::UndavDictionaryIterator::Next(DictionaryIterator* iterator){
     iterator->indiceCursor++;
}

void UndavDictionary::UndavDictionaryIterator::Destroy(DictionaryIterator* iterator){
     delete iterator;
}

void UndavDictionary::Destroy(Dictionary* dictionary){
     delete[] dictionary->items;
     delete[] dictionary->claves;
     delete dictionary;
}
