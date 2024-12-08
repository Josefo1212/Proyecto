#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include"../Models/Repuestos.h"
#pragma once
using namespace std;

extern Repuestos* repuestosPtr;
extern int repuestosCount;

void leerRepuestos(const string &repuestos) {
    ifstream archivoRepuestos(repuestos);
    string linea;

    if (!archivoRepuestos.is_open()) {
        cout << "No se pudo abrir el archivo " << repuestos << endl;
        return;
    }
    getline(archivoRepuestos, linea);
    while (getline(archivoRepuestos, linea)) {
        Repuestos repuesto;
        stringstream ss(linea);
        string tempStr;
        int tempInt;
        double tempDouble;

        getline(ss, tempStr, ',');
        repuesto.setModeloRepuesto(tempStr);
        getline(ss, tempStr, ',');
        repuesto.setMarcaRepuesto(tempStr);
        getline(ss, tempStr, ',');
        repuesto.setNombreRepuesto(tempStr);
        getline(ss, tempStr, ',');
        repuesto.setModeloAuto(tempStr);
        ss >> tempInt;
        repuesto.setYearAuto(tempInt);
        ss.ignore();
        ss >> tempDouble;
        repuesto.setPrecioRepuesto(tempDouble);
        ss.ignore();
        ss >> tempInt;
        repuesto.setExistencias(tempInt);

        Repuestos* temp = new Repuestos[repuestosCount + 1];
        for (int i = 0; i < repuestosCount; ++i) {
            temp[i] = repuestosPtr[i];
        }
        temp[repuestosCount] = repuesto;
        delete[] repuestosPtr;
        repuestosPtr = temp;
        repuestosCount++;
    }
    archivoRepuestos.close();
}

void guardarRepuesto(const string &archivo) {
    ofstream archivoRepuestos(archivo);
    if (!archivoRepuestos.is_open()) {
        cout << "No se pudo abrir el archivo " << archivo << endl;
        return;
    }
    archivoRepuestos << "modeloRepuesto,marcaRepuesto,nombreRepuesto,modeloAuto,yearAuto,precioRepuesto,existencias\n";
    for (int i = 0; i < repuestosCount; ++i) {
        archivoRepuestos << repuestosPtr[i].getModeloRepuesto() << ","
                         << repuestosPtr[i].getMarcaRepuesto() << ","
                         << repuestosPtr[i].getNombreRepuesto() << ","
                         << repuestosPtr[i].getModeloAuto() << ","
                         << repuestosPtr[i].getYearAuto() << ","
                         << repuestosPtr[i].getPrecioRepuesto() << ","
                         << repuestosPtr[i].getExistencias() << "\n";
    }
    archivoRepuestos.close();
}

void insertarRepuesto() {
    Repuestos repuesto;
    string tempStr;
    int tempInt;
    double tempDouble;

    cout << "Ingrese datos del repuesto (modeloRepuesto, marcaRepuesto, nombreRepuesto, modeloAuto, yearAuto, precioRepuesto, existencias): " << endl;
    cin.ignore(); 
    getline(cin, tempStr);
    repuesto.setModeloRepuesto(tempStr);
    getline(cin, tempStr);
    repuesto.setMarcaRepuesto(tempStr);
    getline(cin, tempStr);
    repuesto.setNombreRepuesto(tempStr);
    getline(cin, tempStr);
    repuesto.setModeloAuto(tempStr);
    cin >> tempInt;
    repuesto.setYearAuto(tempInt);
    cin >> tempDouble;
    repuesto.setPrecioRepuesto(tempDouble);
    cin >> tempInt;
    repuesto.setExistencias(tempInt);
    cin.ignore(); 

    cout << "Confirma la insercion del repuesto? (s/n): ";
    char confirmacion;
    cin >> confirmacion;
    if (confirmacion == 's' || confirmacion == 'S') {
        Repuestos* temp = new Repuestos[repuestosCount + 1];
        for (int i = 0; i < repuestosCount; ++i) {
            temp[i] = repuestosPtr[i];
        }
        temp[repuestosCount] = repuesto;
        delete[] repuestosPtr;
        repuestosPtr = temp;
        repuestosCount++;
        guardarRepuesto("../bin/repuestosCoches.csv");
        cout << "Repuesto insertado." << endl;
    } else {
        cout << "Insercion cancelada." << endl;
    }
}

void actualizarRepuesto(const string &modeloRepuesto, const string &marcaRepuesto, const string &nombreRepuesto, const string &modeloAuto) {
    for (int i = 0; i < repuestosCount; ++i) {
        if (repuestosPtr[i].getModeloRepuesto() == modeloRepuesto && repuestosPtr[i].getMarcaRepuesto() == marcaRepuesto && repuestosPtr[i].getNombreRepuesto() == nombreRepuesto && repuestosPtr[i].getModeloAuto() == modeloAuto) {
            Repuestos original = repuestosPtr[i];
            Repuestos &repuesto = repuestosPtr[i];
            string tempStr;
            int tempInt;
            double tempDouble;

            cout << "Ingrese nuevos datos (marcaRepuesto, nombreRepuesto, modeloAuto, yearAuto, precioRepuesto, existencias): " << endl;
            cin.ignore();
            getline(cin, tempStr);
            repuesto.setMarcaRepuesto(tempStr);
            getline(cin, tempStr);
            repuesto.setNombreRepuesto(tempStr);
            getline(cin, tempStr);
            repuesto.setModeloAuto(tempStr);
            cin >> tempInt;
            repuesto.setYearAuto(tempInt);
            cin >> tempDouble;
            repuesto.setPrecioRepuesto(tempDouble);
            cin >> tempInt;
            repuesto.setExistencias(tempInt);

            cout << "Confirma los cambios? (s/n): ";
            char confirmacion;
            cin >> confirmacion;
            if (confirmacion == 's' || confirmacion == 'S') {
                guardarRepuesto("../bin/repuestosCoches.csv");
                cout << "Cambios realizados." << endl;
            } else {
                repuestosPtr[i] = original;
                cout << "Cambios revertidos." << endl;
            }
            return;
        }
    }
    cout << "Repuesto no encontrado." << endl;
}

void borrarRepuesto(const string &modeloRepuesto, const string &marcaRepuesto, const string &nombreRepuesto, const string &modeloAuto) {
    for (int i = 0; i < repuestosCount; ++i) {
        if (repuestosPtr[i].getModeloRepuesto() == modeloRepuesto && repuestosPtr[i].getMarcaRepuesto() == marcaRepuesto && repuestosPtr[i].getNombreRepuesto() == nombreRepuesto && repuestosPtr[i].getModeloAuto() == modeloAuto) {
            cout << "Esta seguro de que desea eliminar el repuesto " << modeloRepuesto << " de marca " << marcaRepuesto << "? (s/n): ";
            char confirmacion;
            cin >> confirmacion;
            if (confirmacion == 's' || confirmacion == 'S') {
                Repuestos* temp = new Repuestos[repuestosCount - 1];
                for (int j = 0, k = 0; j < repuestosCount; ++j) {
                    if (j != i) {
                        temp[k++] = repuestosPtr[j];
                    }
                }
                delete[] repuestosPtr;
                repuestosPtr = temp;
                repuestosCount--;
                guardarRepuesto("../bin/repuestosCoches.csv");
                cout << "Repuesto eliminado." << endl;
            } else {
                cout << "Eliminacion cancelada." << endl;
            }
            return;
        }
    }
    cout << "Repuesto no encontrado." << endl;
}

void leerRepuestosDesdeArray() {
    if (repuestosCount == 0) {
        cout << "No hay repuestos disponibles." << endl;
        return;
    }
    for (int i = 0; i < repuestosCount; ++i) {
        const Repuestos &repuesto = repuestosPtr[i];
        cout << repuesto.getModeloRepuesto() << ", "
             << repuesto.getMarcaRepuesto() << ", "
             << repuesto.getNombreRepuesto() << ", "
             << repuesto.getModeloAuto() << ", "
             << repuesto.getYearAuto() << ", "
             << repuesto.getPrecioRepuesto() << ", "
             << repuesto.getExistencias() << endl;
    }
}
