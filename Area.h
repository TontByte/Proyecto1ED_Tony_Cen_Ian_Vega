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
	int tiempoPromedio;
	int cantTiquetes;
	//estadisticas??

public:
	Area(string descripcion, string codigo, int cantV) {
		this->descripcion = descripcion;
		this->codigo = codigo;
		ventanillas = new ArrayList<Ventanilla>(cantV);
		pCola = new HeapPriorityQueue<Tiquete>;
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
			//agregar logica de creacion de ventanilla y agregacion basado en ed utilizada
		}
	}

	void modifyV(int cant) {
		if (cant <= 0) {
			throw runtime_error("Cantidad invalida de ventanillas solicitadas");
		}
		delete ventanillas;
		ventanillas = new ArrayList<Ventanilla>(cant);
	}

};

