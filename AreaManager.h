/*
Esta es la clase AreaManager (escrita principalmente por Tony y revisada/mejorada por Ian)
Es un control de todos las areas
Permite ejecutar funciones sobre las areas deseadas
*/

#pragma once
#include <iostream>
#include <stdexcept>
#include <string>
#include "Area.h"
#include "ArrayList.h"
#include "Tiquete.h"

using std::cout;
using std::runtime_error;
using std::endl;
using std::string;

class AreaManager {
private:
	ArrayList<Area*> areas;

public:
	AreaManager() {}

	~AreaManager() {
		for (areas.goToStart(); !areas.atEnd(); areas.next()) {
			delete areas.getElement();
		}
		areas.clear();
	}

	AreaManager(const AreaManager&) = delete;
	AreaManager& operator=(const AreaManager&) = delete;

	void createArea(string descripcion, string codigo, int cantV) {
		Area* a = new Area(descripcion, codigo, cantV);
		areas.append(a);
	}

	//agregar muestreo de servicios relacionados al area
	//agregar confirmacion en programa principal
	void modifyAreaVentanillas(int cant, int choiceIndex) {
		if (choiceIndex < 0 || choiceIndex >= areas.getSize()) {
			throw runtime_error("Indice seleccionado invalido.");
		}
		areas.goToPos(choiceIndex);
		areas.getElement()->modifyV(cant);
	}

	void addTiqueteArea(int choiceIndex, Tiquete t) {
		if (choiceIndex < 0 || choiceIndex >= areas.getSize()) {
			throw runtime_error("Indice seleccionado invalido.");
		}
		areas.goToPos(choiceIndex);
		areas.getElement()->addTiquete(t);
	}

	void deleteArea(int choiceIndex) { //se utilizara indice para decidir 
		if (choiceIndex < 0 || choiceIndex >= areas.getSize()) {
			throw runtime_error("Indice seleccionado invalido.");
		}
		areas.goToPos(choiceIndex);
		Area* a = areas.remove();
		delete a;
	}
};

//test
