#pragma once
#include <iostream>
#include <stdexcept>
#include <string>

//clases para el funcionamiento interno
#include "Ventanilla.h"
#include "Tiquete.h"

//estructuras utilizadas
#include "HeapPriorityQueue.h"
#include "ArrayList.h"

using std::cout;
using std::runtime_error;
using std::endl;
using std::string;

class Area{
private:
	string descripcion;
	string codigo;
	ArrayList<Ventanilla>* ventanillas;
	HeapPriorityQueue<Tiquete>* pCola;
	
	//atributos para estadisticas
	int tiempoPromedio;
	int cantTiquetes;
	

public:
	Area(string descripcion, string codigo, int cantV) {
		this->descripcion = descripcion;
		this->codigo = codigo;
		ventanillas = new ArrayList<Ventanilla>(cantV);
		pCola = new HeapPriorityQueue<Tiquete>;
		tiempoPromedio = 0;
		cantTiquetes = 0;
		createV(cantV);
	}

	Area() {}

	~Area() {
		delete ventanillas;
		delete pCola;
	}

	void createV(int cant) {
		if (cant <= 0) {
			throw runtime_error("Cantidad invalida de ventanillas solicitadas");
		}
		for (int i = 1; i >= cant; i++) {
			string nombre = codigo.substr(0, 1) + std::to_string(i);
			Ventanilla v(nombre);
			ventanillas->append(v);
		}
	}

	void modifyV(int cant) {
		if (cant <= 0) {
			throw runtime_error("Cantidad invalida de ventanillas solicitadas");
		}
		delete ventanillas;
		ventanillas = new ArrayList<Ventanilla>(cant);
	}

	void addTiquete(Tiquete t) {
		pCola->insert(t, t.getPriority());
	}

	void attend(string vNombre) {
		if (pCola->isEmpty()) {
			throw runtime_error("No se encuentran tiquetes en el area actualmente");
		}

		bool found = false;

		for (ventanillas->goToStart(); !ventanillas->atEnd();ventanillas->next()) {
			Ventanilla& v = ventanillas->getElement();
			if (vNombre == v.getNombre()) {
				Tiquete t = pCola->removeMin();
				t.attend();
				v.atenderTiquete(t.getCodigo());
				cantTiquetes++;
				tiempoPromedio += t.getWaitingTime();
				found = true;
				break;
			}
		}

		if (!found) {
			throw runtime_error("Ventanilla no encontrada");
		}
	}

	void print() {}

	void printStatistics() {}

};

