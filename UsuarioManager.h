#pragma once
#include <iostream>
#include "Usuario.h"
#include "ArrayList.h"

using namespace std;

class UsuarioManager {
private:
    ArrayList<Usuario> usuarios;

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
            cout << "Indice invalido.\n";
        }
    }

    void mostrarUsuarios() {
        cout << "\nUsuarios \n";
        for (int i = 0; i < usuarios.getSize(); i++) {
            usuarios.goToPos(i);
            cout << i << ". " << usuarios.getElement() << endl;
        }
    }

    Usuario getUsuario(int index) {
        usuarios.goToPos(index);
        return usuarios.getElement();
    }

    int size() {
        return usuarios.getSize();
    }
};