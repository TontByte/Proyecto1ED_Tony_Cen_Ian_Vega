#pragma once
#include <iostream>
#include <stdexcept>
#include <string>

using std::cout;
using std::runtime_error;
using std::endl;
using std::string;

class Ventanilla{
private:
	string nombre;

	//atributos de estadisticas
	int cantTiquetesV;
	//ya creo??

public:
	Ventanilla(string nombre) {
		this->nombre = nombre;
		cantTiquetesV = 0;
	}
	Ventanilla() {}

	~Ventanilla() {
		//???
	}
};

