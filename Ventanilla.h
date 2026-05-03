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
	int cantTiquetesV;
	//estadisticas y ya??

public:
	Ventanilla(string nombre) {
		this->nombre = nombre;
	}
	Ventanilla() {}

	~Ventanilla() {
		//???
	}
};

