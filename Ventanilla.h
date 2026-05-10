/*
Esta es la clase Ventanilla (escrita principalmente por Tony y revisada/mejorada por Ian)
Se encarga de todos los objetos Ventanilla
Tiene atributos como el nombre y el codigo del ultimo tiquete atendido
Tambien guarda las estadisticas relacionados a la ventanilla
Tiene los metodos principales que se ejecutan a la atencion de tiquetes en cada ventanilla
*/

#pragma once
#include <iostream>
#include <ostream>
#include <stdexcept>
#include <string>

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
	Ventanilla() {
		nombre = atendido = "";
		cantTiquetesV = 0;
	}

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

	void reset() {
		cantTiquetesV = 0;
		atendido = "";
	}

	friend ostream& operator<<(ostream& os, const Ventanilla& v) {
		os << "Ventanilla: " << v.nombre
			<< " | Ultimo Atendido: " << v.atendido;
		return os;
	}
};

