#include "Usuario.h"
#include <stdexcept>
#include <iostream>
#pragma once

int contarLineas(const string& archivo) {
    ifstream archivoEntrada(archivo);
    int lineas = 0;
    string linea;

    while (getline(archivoEntrada, linea)) {
        ++lineas;
    }
    archivoEntrada.close();
    return lineas;
}

Usuario* leerUsuarios(const string& archivo, int& cantidadUsuarios) {
    cantidadUsuarios = contarLineas(archivo);
    Usuario* usuarios = new Usuario[cantidadUsuarios];

    ifstream archivoEntrada(archivo);
    string linea;
    int index = 0;

    if (!archivoEntrada.is_open()) {
        cerr << "Error al abrir el archivo de usuarios." << endl;
        return usuarios;
    }

    while (getline(archivoEntrada, linea)) {
        if (linea.empty()) continue;
        stringstream ss(linea);
        string usuario, password, rol;
        getline(ss, usuario, ',');
        getline(ss, password, ',');
        getline(ss, rol, ',');

        if (usuario.empty() || password.empty() || rol.empty()) {
            cerr << "Error: Campos vacios en la linea " << index + 1 << endl;
            continue;
        }

        usuarios[index].usuario = usuario;
        usuarios[index].rol = rol;
        usuarios[index].password = password;
        ++index;
    }

    archivoEntrada.close();
    return usuarios;
}
