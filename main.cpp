// main.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <cstdlib>
#include <string>
#include <stdexcept>
#include "Tiquete.h"
#include "AreaManager.h"
#include "ServicioManager.h"
#include "UsuarioManager.h"

using std::cout;
using std::cin;
using std::getline;
using std::runtime_error;
using std::string;
using std::endl;

void waitEnter() {
    cout << "Presione enter para regresar al menu." << endl;
    string input;
    getline(cin, input);
}

string getStringValue(string datoDeseado) {
    cout << datoDeseado << "(ingrese aqui): ";
    string value;
    getline(cin, value);
    return value;
}

int getNumValue(int maxIndex, int minIndex) {
    if (maxIndex < 0 || minIndex > maxIndex || maxIndex < minIndex) {
        throw runtime_error("Implementacion erronea de getMaxValue");
    }

    int res;
    bool gotten = false;

    while (!gotten) {
        cout << "Ingrese el indice del elemento que desea seleccionar:" << endl;
        cin >> res;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Seleccion invalida. Volver a intentar." << endl;
        }
        else if (res < 0 || res > maxIndex || res < minIndex) {
            cin.ignore(1000, '\n');
            cout << "Seleccion invalida. Volver a intentar." << endl;
        }
        else {
            cin.ignore(1000, '\n');
            gotten = true;
            return res;
        }
    }
}

void clearScreen() {
    system("cls");
}

bool minReqs(AreaManager& am, ServicioManager& sm, UsuarioManager& um) {
    if (am.size() == 0 || sm.size() == 0 || um.size() == 0) {
        return false;
    }
    else {
        return true;
    }
}

int drawMainMenu() {
    cout << "--- Sistema de administracion de colas ---" << endl;
    cout << "--- Seleccione una opcion utilizando su indice." << endl;
    cout << "1. Estado de colas" << endl;
    cout << "2. Crear tiquete" << endl;
    cout << "3. Atender tiquete" << endl;
    cout << "4. Administracion" << endl;
    cout << "5. Estadisticas" << endl;
    cout << "6. Salir" << endl;
    return getNumValue(6, 1);
}

void drawColas(AreaManager& am, ServicioManager& sm, UsuarioManager& um) {
    cout << "Cantidad de areas: " << am.size() << endl;
    am.printAreas();
    waitEnter();
}

void createTicket(AreaManager& am, ServicioManager& sm, UsuarioManager& um) {
    //add loop
    if (minReqs) {
        int option = 0;
        cout << "Ingrese la opcion deseada: " << endl;
        cout << "1. Crear tiquete" << endl;
        cout << "2. Regresar al menu" << endl;
        option = getNumValue(2, 1);
        if (option == 1) {
            cout << "Seleccione el tipo de usuario y el servicio requerido:" << endl;
            um.mostrarUsuarios();
            Usuario tipoU = um.getUsuario(getNumValue(um.size(), 0));
            cout << "Usuario seleccionado: " << tipoU.getNombre() << endl;
            sm.mostrarServicios();
            Servicio tipoS = sm.getServicio(getNumValue(sm.size(), 0));
            cout << "Servicio seleccionado: " << tipoS.getDescripcion() << endl;
            Tiquete t(tipoS.getArea()[0], tipoU.getPrioridad(), tipoS.getPrioridad());
            cout << "Tiquete generado: " << t << endl;
            int pos = am.getAreaIndex(tipoS.getArea());
            am.addTiqueteArea(pos, t);
        }
        else if (option == 2) {
            return;
        }
        else {
            throw runtime_error("Opcion invalida seleccionada.");
        }
    }
    else {
        cout << "No se ha cumplido la cantidad minima de Areas, Usuarios y Servicios requeridos para utilizar el programa." << endl;
        waitEnter();
    }
}

void attend(AreaManager& am, ServicioManager& sm, UsuarioManager& um) {}

void admin(AreaManager& am, ServicioManager& sm, UsuarioManager& um) {}

void statistics(AreaManager& am, ServicioManager& sm, UsuarioManager& um) {}


int main(){
    //definir variables para simplificar semantica
    int mainMenu = 0;
    int colas = 1;
    int getTicket = 2;
    int attend = 3;
    int admin = 4;
    int statistics = 5;
    int exit = 6;

    int currentScreen = 0;
    
    ServicioManager servicioManager;
    UsuarioManager usuarioManager;
    AreaManager areaManager(servicioManager);

    while (currentScreen != 6) {
        try {
            clearScreen();

            if (currentScreen == 0) {
                currentScreen = drawMainMenu();
            }
            else if (currentScreen == 1) {
                drawColas(areaManager, servicioManager, usuarioManager);
                currentScreen = 0;
            }
            else if (currentScreen == 2) {
                createTicket(areaManager, servicioManager, usuarioManager);
                currentScreen = 0;
            }
            else if (currentScreen == 3) {}
            else if (currentScreen == 4) {}
            else if (currentScreen == 5) {}
            else if (currentScreen == 6) {}
        }
        catch (const exception& e) {
            cout << "Error: " << e.what() << endl;
        }
    }

    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
