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
#include "ServicioManager.h"

using std::cout;
using std::runtime_error;
using std::endl;
using std::string;

class AreaManager {
private:
	ArrayList<Area*> areas;
	ServicioManager& sm;

public:
	AreaManager(ServicioManager& sm) : sm(sm) {}

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

	//agregar muestreo de servicios relacionados al area en menu principal
	//agregar confirmacion en programa principal
	void deleteArea(int choiceIndex) { //se utilizara indice para decidir 
		if (choiceIndex < 0 || choiceIndex >= areas.getSize()) {
			throw runtime_error("Indice seleccionado invalido.");
		}
		areas.goToPos(choiceIndex);
		Area* a = areas.remove();
		string areaCodigo = a->getCodigo();
		delete a;
		sm.eliminarServArea(areaCodigo);
	}
};

//test
