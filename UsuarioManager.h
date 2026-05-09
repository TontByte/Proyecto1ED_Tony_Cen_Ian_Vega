/*
Esta es la clase UsuarioManager (escrita principalmente por Ian y revisada/mejorada por Tony)
Es un control de todos los tipos de usuario del sistema
Permite ejecutar funciones como agregar, eliminar y mostrar usuarios, manteniendolos ordenados por prioridad
*/
#pragma once
#include <iostream>
#include "Usuario.h"
#include "ArrayList.h"

using namespace std;

class UsuarioManager {
private:
    ArrayList<Usuario> usuarios;

    //utiliza bubblesort
    void ordenar() {
        for (int i = 0; i < usuarios.getSize(); i++) {
            for (int j = i + 1; j < usuarios.getSize(); j++) {
                usuarios.goToPos(i);
                Usuario ui = usuarios.getElement();
                usuarios.goToPos(j);
                Usuario uj = usuarios.getElement();
                if (uj.getPrioridad() < ui.getPrioridad()) {
                    usuarios.goToPos(i);
                    usuarios.setElement(uj);
                    usuarios.goToPos(j);
                    usuarios.setElement(ui);
                }
            }
        }
    }

public:
    void agregarUsuario(string nombre, int prioridad) {
        usuarios.append(Usuario(nombre, prioridad));
        ordenar();
        cout << "Usuario agregado.\n";
    }

    void eliminarUsuario(int index) {
        if (index >= 0 && index < usuarios.getSize()) {
            usuarios.goToPos(index);
            usuarios.remove();
            cout << "Usuario eliminado.\n";
        }
        else {
            throw runtime_error("Indice seleccionado invalido.");
        }
    }

    void mostrarUsuarios() {
        cout << "\nUsuarios \n";
        for (int i = 0; i < usuarios.getSize(); i++) {
            usuarios.goToPos(i);
            cout << i << ". " << usuarios.getElement() << endl;
        }
    }

    void printStatistics() {
        for (usuarios.goToStart(); !usuarios.atEnd(); usuarios.next()) {
            usuarios.getElement().printStatistics();
        }
    }

    Usuario& getUsuario(int index) {
        usuarios.goToPos(index);
        return usuarios.getElement();
    }

    int size() {
        return usuarios.getSize();
    }
};