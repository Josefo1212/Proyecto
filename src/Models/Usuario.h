#ifndef USUARIO_H
#define USUARIO_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

struct Usuario {
    string usuario;
    string password;
    string rol;
};

// Función para contar el número de líneas en el archivo CSV
int contarLineas(const string& archivo);

// Función para leer usuarios del archivo CSV
Usuario* leerUsuarios(const string& archivo, int& cantidadUsuarios);

#endif // USUARIO_H
