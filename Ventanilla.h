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
	string atendido;

	//atributos de estadisticas
	int cantTiquetesV;

public:
	Ventanilla(string nombre) {
		this->nombre = nombre;
		atendido = "";
		cantTiquetesV = 0;
	}
	Ventanilla() {}

	string getNombre() {
		return nombre;
	}

	void atenderTiquete(string codigo) {
		atendido = codigo;
		cantTiquetesV++;
	}

	void print() {
		cout << nombre << ": " << atendido << endl;
	}

	void printStatistics() {
		cout << "Tiquetes atendido en " << nombre << ": " << cantTiquetesV << endl;
	};
};

