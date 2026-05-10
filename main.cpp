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
    if (maxIndex < 0 || minIndex > maxIndex) {
        throw runtime_error("Implementacion erronea de getNumValue");
    }

    int res;
    bool gotten = false;

    while (!gotten) {
        cout << "Ingrese un numero entero entre " << minIndex << " y " << maxIndex << ": ";
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
    bool stop = false;
    while (!stop) {
        if (minReqs(am, sm, um)) {
            int option = 0;
            cout << "Ingrese la opcion deseada: " << endl;
            cout << "1. Crear tiquete" << endl;
            cout << "2. Regresar al menu" << endl;
            option = getNumValue(2, 1);
            if (option == 1) {
                cout << "Seleccione el tipo de usuario y el servicio requerido:" << endl;
                um.mostrarUsuarios();
                Usuario& tipoU = um.getUsuario(getNumValue(um.size() - 1, 0));
                cout << "Usuario seleccionado: " << tipoU.getNombre() << endl;
                sm.mostrarServicios();
                Servicio& tipoS = sm.getServicio(getNumValue(sm.size() - 1, 0));
                cout << "Servicio seleccionado: " << tipoS.getDescripcion() << endl;
                Tiquete t(tipoS.getArea()[0], tipoU.getPrioridad(), tipoS.getPrioridad(), tipoS.getDescripcion(), tipoU.getNombre());
                tipoS.addTiqueteCant();
                tipoU.addTiqueteCant();
                cout << "Tiquete generado: " << t << endl;
                int pos = am.getAreaIndex(tipoS.getArea());
                am.addTiqueteArea(pos, t);
            }
            else if (option == 2) {
                stop = true;
            }
            else {
                throw runtime_error("Opcion invalida seleccionada.");
            }
        }
        else {
            cout << "No se ha cumplido la cantidad minima de Areas, Usuarios y Servicios requeridos para utilizar el programa." << endl;
            waitEnter();
            stop = true;
        }
    }
}

void attendT(AreaManager& am, ServicioManager& sm, UsuarioManager& um) {
    if (minReqs(am, sm, um)) {
        am.mostrarAreas();
        cout << "Seleccione el area donde desea antender un tiquete: " << endl;
        int index = getNumValue(am.size() - 1 , 0);
        Area* a = am.getArea(index);
        if (a->getCantT() <=0) {
            cout << "No hay tiquetes en esta area" << endl;
            waitEnter();
            return;
        }
        else {
            cout << "Siguiente tiquete a atender: " << a->getMinTicket() << endl;
            cout << endl;
            a->printVentanillas();
            cout << "Seleccione la ventanilla donde desea antender: " << endl;
            int vIndex = getNumValue(a->getCantV() - 1, 0);
            string vName = a->getVName(vIndex);
            a->attend(vName);
        }
    }
    else {
        cout << "No se ha cumplido la cantidad minima de Areas, Usuarios y Servicios requeridos para utilizar el programa." << endl;
        waitEnter();
    }
}

void adminUsuarios(AreaManager& am, ServicioManager& sm, UsuarioManager& um) {
    bool stop = false;
    int option = 0;
    while (!stop) {
        clearScreen();
        if (option == 0) {
            cout << "Administrador de usuarios" << endl;
            cout << "Ingrese la opcion deseada: " << endl;
            cout << "1. Agregar usuario" << endl;
            cout << "2. Eliminar usuario" << endl;
            cout << "3. Regresar" << endl;
            option = getNumValue(3, 1);
        }
        else if (option == 1) {
            cout << "Ingrese los datos solicitados para agregar un tipo de usuario: " << endl;
            string nombre = getStringValue("Nombre");
            cout << "Prioridad: " << endl;
            int prioridad = getNumValue(1024, 0);
            um.agregarUsuario(nombre, prioridad);
            cout << "Se agrego el usuario tipo " << nombre << " de prioridad " << prioridad << endl;
            waitEnter();
            option = 0;
        }
        else if (option == 2) {
            if (um.size() > 0) {
                cout << "Seleccione el tipo de usuario que desea borrar (con su indice): " << endl;
                um.mostrarUsuarios();
                int choice = getNumValue(um.size() - 1, 0);
                string uName = um.getUsuario(choice).getNombre();
                um.eliminarUsuario(choice);
                am.deleteUsuarioTickets(uName);
                waitEnter();
                option = 0;
            }
            else {
                cout << "No hay usuarios por borrar" << endl;
                waitEnter();
                option = 0;
            }
        }
        else if (option == 3) {
            stop = true;
        }
        else {
            throw runtime_error("Opcion invalida seleccionada.");
        }
    }
}

void adminAreas(AreaManager& am, ServicioManager& sm, UsuarioManager& um) {
    bool stop = false;
    int option = 0;
    while (!stop) {
        clearScreen();
        if (option == 0) {
            cout << "Administrador de areas" << endl;
            cout << "Ingrese la opcion deseada: " << endl;
            cout << "1. Agregar area" << endl;
            cout << "2. Eliminar area" << endl;
            cout << "3. Modificar cantidad de ventanillas" << endl;
            cout << "4. Regresar" << endl;
            option = getNumValue(4, 1);
        }
        else if (option == 1) {
            cout << "Ingrese los datos solicitados para agregar un area: " << endl;
            string codigo = getStringValue("Codigo");
            string descripcion = getStringValue("Descripcion corta");
            cout << "Ingrese la cantidad de ventanillas que debe tener el area: " << endl;
            int cantVentanillas = getNumValue(10, 1);
            am.createArea(descripcion, codigo, cantVentanillas);
            cout << "Se agrego el area " << codigo << "(" << descripcion << ")" << " con " << cantVentanillas << " ventanillas" << endl;
            waitEnter();
            option = 0;
        }
        else if (option == 2) {
            if (am.size() > 0) {
                cout << "Seleccione el area que desea borrar (con su indice): " << endl;
                am.mostrarAreas();
                int choice = getNumValue(am.size() - 1, 0);
                cout << "Se borraran los siguientes servicios junto al area" << endl;
                am.mostrarServiciosRelacionados(choice);
                cout << "Si desea proceder con la eliminacion del area y sus servicios relacionados, ingrese 0" << endl;
                cout << "Si no desea seguir adelante, ingrese 1" << endl;
                int confirmacion = getNumValue(1, 0);
                if (confirmacion == 0) {
                    am.deleteArea(choice);
                }
                waitEnter();
                option = 0;
            }
            else {
                cout << "Aun no existen areas para eliminar" << endl;
                waitEnter();
                option = 0;
            }
        }
        else if (option == 3) {
            if (am.size() > 0) {
                cout << "Seleccione el area al que le desea modificar la cantidad de ventanillas: " << endl;
                am.mostrarAreas();
                int choice = getNumValue(am.size() - 1, 0);
                cout << "Indique la cantidad de ventanillas que desea tener: " << endl;
                int cant = getNumValue(10, 1);
                am.modifyAreaVentanillas(cant, choice);
                cout << "Area de " << am.getArea(choice)->getCodigo() << " ahora tiene " << cant << " ventanillas" << endl;
                waitEnter();
                option = 0;
            }
            else {
                cout << "Aun no existen areas para modificar" << endl;
                waitEnter();
                option = 0;
            }
        }
        else if (option == 4) {
            stop = true;
        }
        else {
            throw runtime_error("Opcion invalida seleccionada.");
        }
    }
}

void adminServicios(AreaManager& am, ServicioManager& sm, UsuarioManager& um) {
    bool stop = false;
    int option = 0;
    while (!stop) {
        clearScreen();
        if (option == 0) {
            cout << "Administrador de servicios" << endl;
            cout << "Ingrese la opcion deseada: " << endl;
            cout << "1. Agregar servicio" << endl;
            cout << "2. Eliminar servicio" << endl;
            cout << "3. Reordenar" << endl;
            cout << "4. Regresar" << endl;
            option = getNumValue(4, 1);
        }
        else if (option == 1) { 
            if (am.size() > 0) {
                cout << "Ingrese los datos solicitados para agregar un servicio: " << endl;
                string descripcion = getStringValue("Descripcion corta");
                cout << "Prioridad: " << endl;
                int prioridad = getNumValue(1024, 0);
                cout << "Seleccione el area a la que esta asociada el servicio: " << endl;
                am.mostrarAreas();
                int index = getNumValue(am.size(), 0);
                string areaCode = am.getArea(index)->getCodigo();
                sm.agregarServicio(descripcion, prioridad, areaCode);
                cout << "Se agrego el servicio " << descripcion << " de prioridad " << prioridad << "asociado al area " << areaCode << endl;
                waitEnter();
                option = 0;
            }
            else {
                cout << "Debe existir al menos 1 area para crear un servicio" << endl;
                waitEnter();
                option = 0;
            }
        }
        else if (option == 2) { 
            if (sm.size() > 0) {
                cout << "Seleccione el servicio que desea borrar (con su indice): " << endl;
                sm.mostrarServicios();
                int choice = getNumValue(sm.size() - 1, 0);
                string sName = sm.getServicio(choice).getDescripcion();
                sm.eliminarServicio(choice);
                am.deleteUsuarioTickets(sName);
                waitEnter();
                option = 0;
            }
            else {
                cout << "No hay servicios por borrar" << endl;
                waitEnter();
                option = 0;
            }
        }
        else if (option == 3) {
            if (sm.size() > 1) {
                cout << "Seleccione el servicio que desea reubicar: " << endl;
                sm.mostrarServicios();
                int origen = getNumValue(sm.size() - 1, 0);
                cout << "Seleccione la posicion destino con el indice: " << endl;
                int destino = getNumValue(sm.size() - 1, 0);
                sm.reordenarServicio(origen, destino);
                waitEnter();
                option = 0;
            }
            else {
                cout << "No hay suficientes servicios para reordenar" << endl;
                waitEnter();
                option = 0;
            }
        }
        else if (option == 4) {
            stop = true;
        }
        else {
            throw runtime_error("Opcion invalida seleccionada.");
        }
    }
}

void reset(AreaManager& am, ServicioManager& sm, UsuarioManager& um) {
    cout << "Se ejecuta limpieza de colas y estadisticas" << endl;
    am.reset();
    sm.reset();
    um.reset();
    waitEnter();
}

void admin(AreaManager& am, ServicioManager& sm, UsuarioManager& um) {
    bool stop = false;
    int option = 0;
    while (!stop) {
        clearScreen();
        if (option == 0) {
            cout << "Ingrese la opcion deseada: " << endl;
            cout << "1. Administrar usuarios" << endl;
            cout << "2. Administrar areas" << endl;
            cout << "3. Administrar servicios" << endl;
            cout << "4. Limpiar colas y estadisticas" << endl;
            cout << "5. Regresar al menu" << endl;
            option = getNumValue(5, 1);
        }
        else if (option == 1) {
            adminUsuarios(am, sm, um);
            option = 0;
        }
        else if (option == 2) {
            adminAreas(am, sm, um);
            option = 0;
        }
        else if (option == 3) {
            adminServicios(am, sm, um);
            option = 0;
        }
        else if (option == 4) {
            reset(am, sm, um);
            option = 0;
        }
        else if (option == 5) {
            stop = true;
        }
        else {
            throw runtime_error("Opcion invalida seleccionada.");
        }
    }
}

void statistics(AreaManager& am, ServicioManager& sm, UsuarioManager& um) {
    if (minReqs(am, sm, um)) {
        cout << "Estadisticas: " << endl;
        cout << "Por area: " << endl;
        am.printAreasStatistics();
        cout << endl;

        cout << "Por ventanilla: " << endl;
        am.printAVStatistics();
        cout << endl;

        cout << "Por servicio: " << endl;
        sm.printStatistics();
        cout << endl;

        cout << "Por tipo de usuario: " << endl;
        um.printStatistics();
        cout << endl;

        waitEnter();
    }
    else {
        cout << "No se ha cumplido la cantidad minima de Areas, Usuarios y Servicios requeridos para utilizar el programa." << endl;
        waitEnter();
    }
}


int main(){
    /*
    definir variables para simplificar semantica
    mainMenu = 0;
    colas = 1;
    getTicket = 2;
    attend = 3;
    admin = 4;
    statistics = 5;
    exit = 6;
    */

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
            else if (currentScreen == 3) {
                attendT(areaManager, servicioManager, usuarioManager);
                currentScreen = 0;
            }
            else if (currentScreen == 4) {
                admin(areaManager, servicioManager, usuarioManager);
                currentScreen = 0;
            }
            else if (currentScreen == 5) {
                statistics(areaManager, servicioManager, usuarioManager);
                currentScreen = 0;
            }
            else if (currentScreen == 6) {
                cout << "Gracias por utilizar nuestro sistema. Adios." << endl;
            }
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
