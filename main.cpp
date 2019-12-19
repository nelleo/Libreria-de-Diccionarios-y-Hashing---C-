#include <iostream>
#include "Dominio.h"
#include "List.h"
#include "Key.h"
#include "Item.h"
#include "Dictionary.h"
#include "Hashing.h"

using namespace UndavDictionary;
using UndavDictionary::UndavDictionaryIterator::DictionaryIterator;
using UndavDominio::Dominio;
using UndavList::List;
using UndavList::UndavListIterator::ListIterator;
using std::cout;
using std::endl;

#define Argentina "Argentina"
#define USA "USA"

typedef void (*FuncionMapEntradaDiccionario)(DictionaryIterator *);
void MapDiccionario(Dictionary* diccionario, FuncionMapEntradaDiccionario map);
void MostrarEntradaDiccionario(DictionaryIterator* entradaDiccionario);
void DestruirEntradaDiccionarioDominiosPorPais(DictionaryIterator* entradaDiccionario);
void DestruirEntradaDiccionario(DictionaryIterator* entradaDiccionario);

void ProbarColecciones();
List* CrearDominios();
void DestruirDominios(List* dominios);
Dictionary* CrearTablaDominiosPorPais();
Dictionary* CrearDiccionario(Key* claves[], Item* valores[], int cantidadEntradas);
void CargarDominios(Dictionary* dominiosPorPais, List* dominios);
void AgregarEntrada(Dictionary* tablaDominios, Dominio* dominio);
void MostrarDominiosPorPais(Dictionary* dominiosPorPais);
void MostrarDominios(Dictionary* tablaDominios);

int main() {
	cout<<"Salida esperada. El orden no importa."<<endl<<endl;
	ProbarColecciones();
	system("pause");
	return 0;
}

Dictionary* CrearTablaDominiosPorPais(){
	Key* hashPaises[2]={
		UndavKey::Create(UndavHashing::Hash(Argentina)),
		UndavKey::Create(UndavHashing::Hash(USA))
    };
	Item* diccionarios[2] = {
		UndavItem::Create(UndavDictionary::Create()),
		UndavItem::Create(UndavDictionary::Create())
	};
	return CrearDiccionario(hashPaises, diccionarios, 2);
}

List* CrearDominios(){
	List* dominios = UndavList::Create();
	UndavList::PushBack(dominios, UndavDominio::Crear("www.undav.edu.ar", "18.216.74.20", Argentina));
	UndavList::PushBack(dominios, UndavDominio::Crear("www.git.kernel.org", "147.75.58.133", USA));
	UndavList::PushBack(dominios, UndavDominio::Crear("www.twitter.com", "1.1.1.1", USA));
	UndavList::PushBack(dominios, UndavDominio::Crear("www.google.com", "216.58.222.36", USA));
	UndavList::PushBack(dominios, UndavDominio::Crear("www.twitter.com", "104.244.42.129", USA));
	return dominios;
}

void DestruirDominios(List* dominios){
	ListIterator* iterador = UndavList::UndavListIterator::Begin(dominios);
	while(!UndavList::UndavListIterator::IsEnd(iterador)){
		Dominio* dominio = (Dominio*)UndavList::UndavListIterator::GetItem(iterador);
		UndavDominio::Destruir(dominio);
		UndavList::UndavListIterator::Next(iterador);
	}
	UndavList::UndavListIterator::Destroy(iterador);
	UndavList::Destroy(dominios);
}

void CargarDominios(Dictionary* dominiosPorPais, List* dominios){
	ListIterator* iterador = UndavList::UndavListIterator::Begin(dominios);
	while(!UndavList::UndavListIterator::IsEnd(iterador)){
		Dominio* dominio = (Dominio*)UndavList::UndavListIterator::GetItem(iterador);
		Key* key = UndavKey::Create(UndavHashing::Hash(UndavDominio::ObtenerPais(dominio)));
        Item* item = UndavDictionary::Get(dominiosPorPais, key);
        Dictionary* tablaDominios = (Dictionary*)UndavItem::Get(UndavDictionary::Get(dominiosPorPais, key));
		AgregarEntrada(tablaDominios, dominio);
		UndavKey::Destroy(key);
		UndavList::UndavListIterator::Next(iterador);
	}
	UndavList::UndavListIterator::Destroy(iterador);
}

void ProbarColecciones(){
	Dictionary* dominiosPorPais = CrearTablaDominiosPorPais();
    List* dominios = CrearDominios();
	CargarDominios(dominiosPorPais, dominios);
	MostrarDominiosPorPais(dominiosPorPais);
	MapDiccionario(dominiosPorPais, DestruirEntradaDiccionarioDominiosPorPais);
}

void Agregar(Dictionary* dominiosPorPais, Dominio* dominios[], int cantidad){
	for(int i=0; i<cantidad;++i){
		Key* key = UndavKey::Create(UndavHashing::Hash(UndavDominio::ObtenerPais(dominios[i])));
		Dictionary* tablaDominios = (Dictionary*)UndavDictionary::Get(dominiosPorPais, key);
		AgregarEntrada(tablaDominios, dominios[i]);
		UndavKey::Destroy(key);
	}
}

void AgregarEntrada(Dictionary* tablaDominios, Dominio* dominio){
	Key* key = UndavKey::Create(UndavDominio::ObtenerDns(dominio));
	Item* item = UndavItem::Create(dominio);
    bool claveExistente = UndavDictionary::Contains(tablaDominios, key);
	UndavDictionary::Put(tablaDominios, key, item);
	if(claveExistente){
		UndavKey::Destroy(key);
    }
}

void MostrarDominiosPorPais(Dictionary* dominiosPorPais){
	Key* keyArgentina = UndavKey::Create(UndavHashing::Hash(Argentina));
	Key* keyUSA = UndavKey::Create(UndavHashing::Hash(USA));
	cout<<Argentina<<endl;
	MostrarDominios((Dictionary*)UndavItem::Get(UndavDictionary::Get(dominiosPorPais, keyArgentina)));
	cout<<USA<<endl;
	MostrarDominios((Dictionary*)UndavItem::Get(UndavDictionary::Get(dominiosPorPais, keyUSA)));
	UndavKey::Destroy(keyArgentina);
	UndavKey::Destroy(keyUSA);
}

void MostrarDominios(Dictionary* tablaDominios){
	MapDiccionario(tablaDominios, MostrarEntradaDiccionario);
}

void MapDiccionario(Dictionary* diccionario, FuncionMapEntradaDiccionario map){
	DictionaryIterator* iterator = UndavDictionaryIterator::Begin(diccionario);
	while(!UndavDictionaryIterator::IsEnd(iterator)){
		map(iterator);
		UndavDictionaryIterator::Next(iterator);
	}
	UndavDictionaryIterator::Destroy(iterator);
}

void MostrarEntradaDiccionario(DictionaryIterator* entradaDiccionario){
	Item* valor = UndavDictionaryIterator::GetValue(entradaDiccionario);
	Dominio* dominio = (Dominio*)UndavItem::Get(valor);
	cout<<"\t["<<UndavDominio::ObtenerDns(dominio)<<"] -> ";
	cout<<UndavDominio::ObtenerIp(dominio)<<"]"<<endl;
}

void DestruirEntradaDiccionario(DictionaryIterator* entradaDiccionario){
	UndavKey::Destroy(UndavDictionaryIterator::GetKey(entradaDiccionario));
	UndavItem::Destroy(UndavDictionaryIterator::GetValue(entradaDiccionario));
}

void DestruirEntradaDiccionarioDominiosPorPais(DictionaryIterator* entradaDiccionario){
	UndavItem::Item* value = UndavDictionaryIterator::GetValue(entradaDiccionario);
	Dictionary* tablaDominios = (Dictionary*)UndavItem::Get(value);
	MapDiccionario(tablaDominios, DestruirEntradaDiccionario);
	UndavDictionary::Destroy(tablaDominios);
	DestruirEntradaDiccionario(entradaDiccionario);
}

Dictionary* CrearDiccionario(Key* claves[],Item* valores[], int cantidadEntradas){
	Dictionary* diccionario = Create();
	for(int i=0; i<cantidadEntradas; ++i){
		Put(diccionario, claves[i], valores[i]);
	}
	return diccionario;
}
