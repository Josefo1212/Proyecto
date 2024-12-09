#ifndef USUARIO_H
#define USUARIO_H
#pragma once

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

int contarLineas(const string& archivo);

Usuario* leerUsuarios(const string& archivo, int& cantidadUsuarios);

#endif
