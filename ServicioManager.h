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
			cout << "Indice invalido.\n";
		}
	}

	void reordenarServicio(int origen, int destino) {
		if (origen < 0 || origen >= servicios.getSize() || destino < 0 || destino >= servicios.getSize()) {
			cout << "Indice invalido.\n";
			return;
		}
		//obtener el servicio a mover
		servicios.goToPos(origen);
		Servicio temp = servicios.getElement();
		servicios.remove();
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
	Servicio getServicio(int index) {
		servicios.goToPos(index);
		return servicios.getElement();
	}
	int size() {
		return servicios.getSize();
	}
};