#ifndef DOMINIO_H_
#define DOMINIO_H_

#include <string>

using std::string;

namespace UndavDominio{
	struct Dominio;
	Dominio* CrearCopia(const Dominio* dominio);
	Dominio* Crear(string dns, string ip, string pais);
	Dominio* Crear(string dns, string ip, string pais, string descripcion);
	bool SonIguales(const Dominio* dominioA, const Dominio* dominioB);
	string ObtenerIp(const Dominio* dominio);
	string ObtenerDns(const Dominio* dominio);
	string ObtenerPais(const Dominio* dominio);
	string ObtenerDescripcion(const Dominio* dominio);
	void CambiarDescripcion(Dominio* dominio, string descripcion);
	void Destruir(const Dominio* dominio);
}

#endif
