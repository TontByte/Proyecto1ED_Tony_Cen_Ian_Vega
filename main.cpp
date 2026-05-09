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
    string input;
    getline(cin, input);
}

string getStringValue(string datoDeseado) {
    cout << datoDeseado << "(ingrese aqui): ";
    string value;
    getline(cin, value);
    return value;
}

int getNumValue(int maxIndex) {
    if (maxIndex < 0) {
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
        else if (res < 0 || res > maxIndex) {
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

void drawMainMenu(AreaManager& am, ServicioManager& sm, UsuarioManager& um) {
    cout << "--- Sistema de administracion de colas ---" << endl;
    cout << "Cantidad de areas: " << am.getCantAreas() << endl;
    am.printAreas();
    cout << "Presione enter para menu"; //???? mistake
    waitEnter();
}



int main(){
    //definir variables para simplificar semantica
    int mainMenu = 0;
    int getTicket = 1;
    int attend = 2;
    int admin = 3;
    int cleanData = 4;
    int statistics = 5;
    int exit = 6;

    int currentScreen = 0;
    
    ServicioManager servicioManager;
    UsuarioManager usuarioManager;
    AreaManager areaManager(servicioManager);

    while (currentScreen != 0) {
        try {
            clearScreen();

            if (currentScreen == 0) {}
            else if (currentScreen == 1) {}
            else if (currentScreen == 2) {}
            else if (currentScreen == 3) {}
            else if (currentScreen == 4) {}
            else if (currentScreen == 5) {}
            else if (currentScreen == 6) {}
        }
        catch (const exception& e) {
            cout << "Error: " << e.what() << endl;
        }
    }
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
