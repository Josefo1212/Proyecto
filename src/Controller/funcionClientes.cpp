#include "../Models/Clientes.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#pragma once
using namespace std;

extern Clientes* clientesPtr;
extern int clientesCount;

void leerClientes(const string &clientes) {
    ifstream archivoClientes(clientes);
    string linea;

    if (!archivoClientes.is_open()) {
        cout << "No se pudo abrir el archivo " << clientes << endl;
        return;
    }
    getline(archivoClientes, linea); 
    while (getline(archivoClientes, linea)) {
        Clientes cliente;
        stringstream ss(linea);
        string tempStr;
        int tempInt;

        ss >> tempInt;
        cliente.setCedula(tempInt);
        ss.ignore();
        getline(ss, tempStr, ',');
        cliente.setNombre(tempStr);
        getline(ss, tempStr, ',');
        cliente.setApellido(tempStr);
        getline(ss, tempStr, ',');
        cliente.setEmail(tempStr);
        ss >> tempInt;
        cliente.setVehiculosRentados(tempInt);
        ss.ignore();
        getline(ss, tempStr, ',');
        cliente.setDireccion(tempStr);
        getline(ss, tempStr, ',');
        cliente.setActivo(tempStr == "1");

        Clientes* temp = new Clientes[clientesCount + 1];
        for (int i = 0; i < clientesCount; ++i) {
            temp[i] = clientesPtr[i];
        }
        temp[clientesCount] = cliente;
        delete[] clientesPtr;
        clientesPtr = temp;
        clientesCount++;
    }
    archivoClientes.close();
}

void guardarClientes(const string &clientes) {
    ofstream archivoClientes(clientes);
    archivoClientes << "cedula,nombre,apellido,email,vehiculosRentados,direccion,activo" << endl; 
    for (int i = 0; i < clientesCount; ++i) {
        const Clientes &cliente = clientesPtr[i];
        archivoClientes << cliente.getCedula() << ","
                        << cliente.getNombre() << ","
                        << cliente.getApellido() << ","
                        << cliente.getEmail() << ","
                        << cliente.getVehiculosRentados() << ","
                        << cliente.getDireccion() << ","
                        << (cliente.getActivo() ? "1" : "0") << endl;
    }
    archivoClientes.close();
}

void insertarCliente() {
    Clientes cliente;
    cout << "Ingrese datos del cliente (cedula, nombre, apellido, email, vehiculosRentados, direccion, activo(1/0)): " << endl;
    int tempInt;
    string tempStr;
    cin >> tempInt;
    cliente.setCedula(tempInt);
    cin.ignore();
    getline(cin, tempStr);
    cliente.setNombre(tempStr);
    getline(cin, tempStr);
    cliente.setApellido(tempStr);
    getline(cin, tempStr);
    cliente.setEmail(tempStr);
    cin >> tempInt;
    cliente.setVehiculosRentados(tempInt);
    cin.ignore();
    getline(cin, tempStr);
    cliente.setDireccion(tempStr);
    int activo;
    cin >> activo;
    cliente.setActivo(activo == 1);

    cout << "Confirma la insercion del cliente? (s/n): ";
    char confirmacion;
    cin >> confirmacion;
    if (confirmacion == 's' || confirmacion == 'S') {
        Clientes* temp = new Clientes[clientesCount + 1];
        for (int i = 0; i < clientesCount; ++i) {
            temp[i] = clientesPtr[i];
        }
        temp[clientesCount] = cliente;
        delete[] clientesPtr;
        clientesPtr = temp;
        clientesCount++;
        guardarClientes("../bin/clientes.csv");
        cout << "Cliente insertado." << endl;
    } else {
        cout << "Insercion cancelada." << endl;
    }
}

void actualizarCliente(int cedula) {
    for (int i = 0; i < clientesCount; ++i) {
        if (clientesPtr[i].getCedula() == cedula) {
            Clientes original = clientesPtr[i];
            Clientes &cliente = clientesPtr[i];
            cout << "Ingrese nuevos datos (nombre, apellido, email, vehiculosRentados, direccion, activo(1/0)): " << endl;
            string tempStr;
            int tempInt;
            cin.ignore();
            getline(cin, tempStr);
            cliente.setNombre(tempStr);
            getline(cin, tempStr);
            cliente.setApellido(tempStr);
            getline(cin, tempStr);
            cliente.setEmail(tempStr);
            cin >> tempInt;
            cliente.setVehiculosRentados(tempInt);
            cin.ignore();
            getline(cin, tempStr);
            cliente.setDireccion(tempStr);
            int activo;
            cin >> activo;
            cliente.setActivo(activo == 1);

            cout << "Confirma los cambios? (s/n): ";
            char confirmacion;
            cin >> confirmacion;
            if (confirmacion == 's' || confirmacion == 'S') {
                guardarClientes("../bin/clientes.csv");
                cout << "Cambios confirmados y guardados." << endl;
            } else {
                clientesPtr[i] = original;
                cout << "Cambios revertidos." << endl;
            }
            return;
        }
    }
    cout << "Cliente no encontrado." << endl;
}

void borrarCliente(int cedula) {
    for (int i = 0; i < clientesCount; ++i) {
        if (clientesPtr[i].getCedula() == cedula) {
            cout << "Esta seguro de que desea eliminar el cliente con cedula " << cedula << "? (s/n): ";
            char confirmacion;
            cin >> confirmacion;
            if (confirmacion == 's' || confirmacion == 'S') {
                Clientes* temp = new Clientes[clientesCount - 1];
                for (int j = 0, k = 0; j < clientesCount; ++j) {
                    if (j != i) {
                        temp[k++] = clientesPtr[j];
                    }
                }
                delete[] clientesPtr;
                clientesPtr = temp;
                clientesCount--;
                guardarClientes("../bin/clientes.csv");
                cout << "Cliente eliminado." << endl;
            } else {
                cout << "Eliminacion cancelada." << endl;
            }
            return;
        }
    }
    cout << "Cliente no encontrado." << endl;
}

void leerClientesDesdeArray() {
    for (int i = 0; i < clientesCount; ++i) {
        const Clientes &cliente = clientesPtr[i];
        cout << cliente.getCedula() << ", "
             << cliente.getNombre() << ", "
             << cliente.getApellido() << ", "
             << cliente.getEmail() << ", "
             << cliente.getVehiculosRentados() << ", "
             << cliente.getDireccion() << ", "
             << (cliente.getActivo() ? "1" : "0") << endl;
    }
}
