#pragma once
#include <iostream>
#include <string>
using namespace std;

class Usuario {
private:
    string nombre;
    int prioridad;

public:

    Usuario(string nombre, int prioridad) {
        this->nombre = nombre;
        this->prioridad = prioridad;
    }

    string getNombre() {
        return nombre;
    }

    int getPrioridad() {
        return prioridad;
    }

    void setNombre(string nombre) {
        this->nombre = nombre;
    }

    void setPrioridad(int prioridad) {
        this->prioridad = prioridad;
    }

    friend ostream& operator<<(ostream& os, const Usuario& u) {
        os << "Usuario: " << u.nombre
            << " | Prioridad: " << u.prioridad;
        return os;
    }
};

