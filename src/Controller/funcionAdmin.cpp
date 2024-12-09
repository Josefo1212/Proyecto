#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;

bool agregarUsuario(const string& archivo, const string& nombre, const string& password, const string& rol) {
    // Verificar que los campos no estén vacíos
    if (nombre.empty() || password.empty() || rol.empty()) {
        cerr << "Error: Los campos nombre, contraseña y rol no deben estar vacíos." << endl;
        return false;
    }

    // Leer el contenido actual del archivo
    ifstream archivoEntrada(archivo);
    if (!archivoEntrada.is_open()) {
        cerr << "Error al abrir el archivo: " << archivo << endl;
        return false;
    }
    stringstream contenido;
    contenido << archivoEntrada.rdbuf();
    archivoEntrada.close();

    // Agregar el nuevo usuario al contenido
    contenido << nombre << "," << password << "," << rol << endl;

    // Escribir el contenido actualizado al archivo
    ofstream archivoSalida(archivo);
    if (!archivoSalida.is_open()) {
        cerr << "Error al abrir el archivo para escribir: " << archivo << endl;
        return false;
    }
    archivoSalida << contenido.str();
    archivoSalida.close();

    return true;
}
