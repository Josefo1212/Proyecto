#include <iostream>
#include <fstream>
#include <ctime>
#include <string>
#pragma once
using namespace std;

string obtenerFechaActual(int &year, int &mes, int &dia, int &hora, int &minuto, int &segundo) {
    time_t ahora = time(0);
    tm* tiempoLocal = localtime(&ahora);
    year = 1900 + tiempoLocal->tm_year;
    mes = 1 + tiempoLocal->tm_mon;
    dia = tiempoLocal->tm_mday;
    hora = tiempoLocal->tm_hour;
    minuto = tiempoLocal->tm_min;
    segundo = tiempoLocal->tm_sec;
}

bool hacerCopiaDeSeguridad(const string& archivoOrigen, const string& CarpetaDestino) {
    int year, mes, dia, hora, minuto, segundo;
    obtenerFechaActual(year, mes, dia, hora, minuto, segundo);

    char buffer[100];
    snprintf(buffer, sizeof(buffer), "%04d%02d%02d_%02d%02d%02d", year, mes, dia, hora, minuto, segundo);
    string fechaActual(buffer);

    string nombreArchivo = archivoOrigen.substr(archivoOrigen.find_last_of("/\\") + 1);
    string archivoDestino = CarpetaDestino + "/" + nombreArchivo + "_" + fechaActual;

    ifstream archivoEntrada(archivoOrigen, ios::binary);
    if (!archivoEntrada) {
        cerr << "Error al abrir el archivo origen: " << archivoOrigen << endl;
        return false;
    }

    ofstream archivoSalida(archivoDestino, ios::binary);
    if (!archivoSalida) {
        cerr << "Error al crear el archivo destino: " << archivoDestino << endl;
        return false;
    }

    archivoSalida << archivoEntrada.rdbuf();

    cout << "Copia de seguridad realizada exitosamente de " << archivoOrigen << " a " << archivoDestino << endl;
    return true;
}
