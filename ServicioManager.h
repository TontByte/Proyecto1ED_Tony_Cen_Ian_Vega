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