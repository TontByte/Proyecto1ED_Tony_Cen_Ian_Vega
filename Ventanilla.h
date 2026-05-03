#pragma once
#include <iostream>
#include <stdexcept>
#include <string>

#include "Tiquete.h"

using std::cout;
using std::runtime_error;
using std::endl;
using std::string;

class Ventanilla{
private:
	string nombre;
	Tiquete tAttended;

	//atributos de estadisticas
	int cantTiquetesV;

public:
	Ventanilla(string nombre) {
		this->nombre = nombre;
		cantTiquetesV = 0;
	}
	Ventanilla() {}

	~Ventanilla() {
		//???
	}

	string getNombre() {
		return nombre;
	}

	void addTiquete(Tiquete t) {
		tAttended = t;
		cantTiquetesV++;
	}

	void print() {}

	void printStatistics() {};
};

