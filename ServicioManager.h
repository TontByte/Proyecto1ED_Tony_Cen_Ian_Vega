/*
Esta es la clase ServicioManager (escrita principalmente por Ian y revisada/mejorada por Tony)
Es un control de todos los servicios del sistema
Permite ejecutar funciones como agregar, eliminar, mostrar y reordenar los servicios segun sea necesario
*/
#pragma once
#include <iostream>
#include "Servicio.h"
#include "ArrayList.h"

using namespace std;

class ServicioManager {
private:
	ArrayList<Servicio> servicios;

public:
	void agregarServicio(string descripcion, int prioridad, string area) {
		servicios.append(Servicio(descripcion, prioridad, area));
		cout << "Servicio agregado.\n";
	}

	void eliminarServicio(int index) {
		if (index >= 0 && index < servicios.getSize()) {
			servicios.goToPos(index);
			servicios.remove();
			cout << "servicio eliminado.\n";
		}
		else {
			throw runtime_error("Indice seleccionado invalido.");
		}
	}

	void reordenarServicio(int origen, int destino) {
		if (origen < 0 || origen >= servicios.getSize() || destino < 0 || destino >= servicios.getSize()) {
			throw runtime_error("Indice seleccionado invalido.");
		}
		//obtener el servicio a mover
		servicios.goToPos(origen);
		Servicio temp = servicios.getElement();
		servicios.remove();
		if (origen < destino) {
			destino--;
		}
		//insertar el servicio en la nueva posicion
		servicios.goToPos(destino);
		servicios.insert(temp);

		cout << "Servicio reordenado.\n";
	}
	void mostrarServicios() {
		cout << "Servicios:\n";
		for (int i = 0; i < servicios.getSize(); i++) {
			servicios.goToPos(i);
			cout << i << ": " << servicios.getElement() << endl;
		}
	}

	void mostrarServiciosArea(string area) {
		for (servicios.goToStart(); !servicios.atEnd(); servicios.next()) {
			if (servicios.getElement().getArea() == area) {
				cout << servicios.getElement() << endl;
			}
		}
	}

	Servicio& getServicio(int index) {
		servicios.goToPos(index);
		return servicios.getElement();
	}
	int size() {
		return servicios.getSize();
	}

	//metodos extra que se utilizan para AreaMangaer
	void eliminarServArea(string area) {
		servicios.goToStart();
		while (!servicios.atEnd()) {
			if (servicios.getElement().getArea() == area) {
				servicios.remove();
			}
			else {
				servicios.next();
			}
		}
	}

	void reset() {
		for (servicios.goToStart(); !servicios.atEnd(); servicios.next()) {
			servicios.getElement().reset();
		}
	}

	void printServArea(string area) {
		cout << "Servicios relacionados a " << area << ":" << endl;
		for (servicios.goToStart(); !servicios.atEnd(); servicios.next()) {
			if (servicios.getElement().getArea() == area) {
				cout << servicios.getElement() << endl;
			}
		}
	}

	void printStatistics() {
		for (servicios.goToStart(); !servicios.atEnd(); servicios.next()) {
			servicios.getElement().printStatistics();
		}
	}
};