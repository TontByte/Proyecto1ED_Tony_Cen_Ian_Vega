/*
Esta es la clase Tiquete (escrita principalmente por Tony y revisada/mejorada por Ian)
Se encarga las instancias de los tiquetes creados
Tiene atributos como el codigo, la prioridad final y datos relacionados a tiempos de atencion
*/

#pragma once
#include <iostream>
#include <stdexcept>
#include <ctime>
#include <string>
#include <ostream>

using std::cout;
using std::endl;
using std::string;
using std::ostream;
using std::runtime_error;

class Tiquete{
private:
	string codigo;
	int pt; //prioridad total
	time_t arrival;
	time_t attended;
	time_t waitingTime;

	//consecutivo global para codigos
	static int consecutivoGlobal;

public:
	Tiquete(char areaC, int prioridadU, int prioridadS) {
		codigo = areaC + std::to_string(consecutivoGlobal);
		consecutivoGlobal++;
		arrival = time(0);
		attended = 0;
		waitingTime = 0;
		pt = (prioridadU * 10) + prioridadS;
	}

	Tiquete() {}

	void attend() {
		attended = time(0);
		waitingTime = attended - arrival;
	}

	int getPriority() {
		return pt;
	}

	string getCodigo() {
		return codigo;
	}

	int getWaitingTime() {
		if (attended == 0) {
			throw runtime_error("Tiquete no ha sido atendido");
		}
		return waitingTime;
	}

	friend ostream& operator<<(ostream& os, const Tiquete& t) {
		os << "(Codigo: " << t.codigo << "Prioridad: " << t.pt << ")";
		return os;
	}
};

