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

    string getDescripcion() {
        return descripcion;
    }

    int getPrioridad() {
        return prioridad;
    }

    string getArea() {
        return area;
    }

    void setDescripcion(string descripcion) {
        this->descripcion = descripcion;
    }

    void setPrioridad(int prioridad) {
        this->prioridad = prioridad;
    }

    void setArea(string area) {
        this->area = area;
    }

    friend ostream& operator<<(ostream& os, const Servicio& s) {
        os << "Servicio: " << s.descripcion
            << " | Prioridad: " << s.prioridad
            << " | Area: " << s.area;
        return os;
    } //prueba
};