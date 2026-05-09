/*
Esta es la clase Area (escrita principalmente por Tony y revisada/mejorada por Ian)
Se encarga de todos los objetos Area
Tiene atributos como la descripcion, el codigo, las ventanillas disponibles y la cola de prioridad
Tambien guarda las estadisticas del area
Tiene los metodos principales que se ejecutan en relacion al manejo de tiquetes
*/

#pragma once
#include <iostream>
#include <ostream>
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
	int tiempoTotal;
	int cantTiquetes;
	

public:
	Area(string descripcion, string codigo, int cantV) {
		this->descripcion = descripcion;
		this->codigo = codigo;
		ventanillas = new ArrayList<Ventanilla>(cantV);
		pCola = new HeapPriorityQueue<Tiquete>;
		tiempoTotal = 0;
		cantTiquetes = 0;
		createV(cantV);
	}

	Area() {
		ventanillas = nullptr;
		pCola = nullptr;
		codigo = descripcion = "";
		tiempoTotal = cantTiquetes = 0;
	}

	Area(const Area&) = delete;
	Area& operator=(const Area&) = delete;

	~Area() {
		delete ventanillas;
		delete pCola;
	}

	void createV(int cant) {
		if (cant <= 0) {
			throw runtime_error("Cantidad invalida de ventanillas solicitadas");
		}
		for (int i = 1; i <= cant; i++) {
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
		createV(cant);
	}

	int getCantV() {
		return ventanillas->getSize();
	}

	int getCantT() {
		return pCola->getSize();
	}

	string getCodigo() {
		return codigo;
	}

	string getMinTicket() {
		return pCola->min().getCodigo();
	}

	string getVName(int vIndex) {
		if (vIndex < 0 || vIndex > ventanillas->getSize()) {
			throw runtime_error("Indice de ventanilla invalido");
		}
		ventanillas->goToPos(vIndex);
		return ventanillas->getElement().getNombre();
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
				t.attend(); //el tiquete se atiende para conseguir tiempo de espera
				v.atenderTiquete(t.getCodigo()); //se agrega el codigo para mostrarse en ventanilla
				cantTiquetes++;
				tiempoTotal += t.getWaitingTime();
				found = true;
				break;
			} 
		}

		if (!found) {
			throw runtime_error("Ventanilla no encontrada");
		}
	}

	void printVentanillas() {
		cout << "Ventanillas: " << endl;;
		for (int i = 0; i < ventanillas->getSize(); i++) {
			ventanillas->goToPos(i);
			cout << i << ". " << ventanillas->getElement() << endl;
		}

	}

	void print() {
		cout << codigo << "(" << descripcion << ")" << ", Ventanillas: " << ventanillas->getSize() << endl;
		for (ventanillas->goToStart(); !ventanillas->atEnd(); ventanillas->next()) {
			ventanillas->getElement().print();
		}
		cout << "Tiquetes: ";
		pCola->print();
		cout << "---------------------------" << endl;
	}

	void printStatistics() {
		if (cantTiquetes == 0) {
			cout << "No hay tiquetes atendidos en " << codigo << endl;
		}
		else {
			cout << "Tiquetes atendido en " << codigo << ": " << cantTiquetes << endl;
			double tiempoPromedio = (double)tiempoTotal / (double)cantTiquetes;
			cout << "Tiempo promedio de espera: " << tiempoPromedio << endl;
		}
	}

	void printStatisticsVentanilla() {
		for (ventanillas->goToStart(); !ventanillas->atEnd(); ventanillas->next()) {
			ventanillas->getElement().printStatistics();
		}
	}

	friend ostream& operator<<(ostream& os, const Area& a) {
		os << "Area: " << a.codigo
			<< " | Descripcion: " << a.descripcion;
		return os;
	}

};

