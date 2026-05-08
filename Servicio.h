/*
Esta es la clase Servicio (escrita principalmente por Ian y revisada/mejorada por Tony)
Se encarga de representar los diferentes servicios que ofrece el sistema
Contiene atributos como la descripcion del servicio, su prioridad y el area a la que pertenece
Esta informacion se utiliza junto con el usuario para calcular la prioridad final del tiquete
*/
#pragma once
#include <string>
#include <iostream>
using namespace std;

class Servicio {
private:
    string descripcion;
    int prioridad;
    string area;

public:

    Servicio(string descripcion, int prioridad, string area) {
        this->descripcion = descripcion;
        this->prioridad = prioridad;
        this->area = area;
    }

    Servicio() {
        area = descripcion = "";
        prioridad = 0;
    }

    string getDescripcion() {
        return descripcion;
    }

    int getPrioridad() {
        return prioridad;
    }

    string getArea() {
        return area;
    }

    friend ostream& operator<<(ostream& os, const Servicio& s) {
        os << "Servicio: " << s.descripcion
            << " | Prioridad: " << s.prioridad
            << " | Area: " << s.area;
        return os;
    }
};