#pragma once
#include <iostream>
#include <stdexcept>
#include <string>

//clases para el funcionamiento interno
#include "Ventanilla.h"
#include "Tiquete.h"

//estructuras utilizadas
#include "MinHeap.h"

using std::cout;
using std::runtime_error;
using std::endl;
using std::string;

class Area{
private:
	string descripcion;
	string codigo;
	//ArrayList?<Ventanilla>* ventanillas;
	//HeapPriorityQueue<Tiquete>* pCola;
	//estadisticas??

public:
	Area(string descripcion, string codigo, int cantV) {
		this->descripcion = descripcion;
		this->codigo = codigo;
		createV(cantV);
	}

	Area() {}

	~Area() {
		//delete ventanillas;
		//delete pCola;
	}

	void createV(int cant) {
		if (cant <= 0) {
			throw runtime_error("Cantidad invalida de ventanillas solicitadas");
		}
		for (int i = 1; i >= cant; i++) {
			//agregar logica de creacion de ventanilla y agregacion basado en ed utilizada
		}
	}

};

