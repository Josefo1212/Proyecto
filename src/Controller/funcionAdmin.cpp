#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#pragma once
using namespace std;

bool agregarUsuario(const string& archivo, const string& nombre, const string& password, const string& rol) {
    if (nombre.empty() || password.empty() || rol.empty()) {
        cerr << "Error: Los campos nombre, password y rol no deben estar vacios." << endl;
        return false;
    }

    ifstream archivoEntrada(archivo);
    if (!archivoEntrada.is_open()) {
        cerr << "Error al abrir el archivo: " << archivo << endl;
        return false;
    }
    stringstream contenido;
    contenido << archivoEntrada.rdbuf();
    archivoEntrada.close();

    contenido << nombre << "," << password << "," << rol << endl;

    ofstream archivoSalida(archivo);
    if (!archivoSalida.is_open()) {
        cerr << "Error al abrir el archivo para escribir: " << archivo << endl;
        return false;
    }
    archivoSalida << contenido.str();
    archivoSalida.close();

    return true;
}
