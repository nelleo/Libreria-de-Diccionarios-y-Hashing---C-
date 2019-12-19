#include "Dominio.h"
#include <string>

using UndavDominio::Dominio;
using std::string;

struct UndavDominio::Dominio{
	string ip;
	string dns;
	string pais;
	string descripcion;
};

Dominio* UndavDominio::Crear(string dns, string ip, string pais, string descripcion){
	Dominio* dominio = new Dominio;
	dominio->descripcion = descripcion;
	dominio->dns = dns;
	dominio->ip = ip;
	dominio->pais = pais;
	return dominio;
}

Dominio* UndavDominio::Crear(string dns, string ip, string pais){
	return Crear(dns, ip, pais, "");
}

bool UndavDominio::SonIguales(const Dominio* dominioA, const Dominio* dominioB){
	return dominioA->ip == dominioB->ip;
}

string UndavDominio::ObtenerIp(const Dominio* dominio){
	return dominio->ip;
}

string UndavDominio::ObtenerDns(const Dominio* dominio){
	return dominio->dns;
}

string UndavDominio::ObtenerDescripcion(const Dominio* dominio){
	return dominio->descripcion;
}

string UndavDominio::ObtenerPais(const Dominio* dominio){
	return dominio->pais;
}

void UndavDominio::CambiarDescripcion(Dominio* dominio, string descripcion){
	dominio->descripcion = descripcion;
}

Dominio* UndavDominio::CrearCopia(const Dominio* dominio){
	return Crear(dominio->dns, dominio->ip, dominio->pais, dominio->descripcion);
}

void UndavDominio::Destruir(const Dominio* dominio){
	delete dominio;
}
