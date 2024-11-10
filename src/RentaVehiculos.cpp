#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
using namespace std;

struct Vehiculos{
    string modelo;
    string marca;
    string placa;
    string color;
    int year;
    int kilometraje;
    bool rentado;
    string motor;
    float precioRenta;
    int cedCliente;
    string fechaEntrega;
};

struct Clientes{
    int cedula;
    string nombre;
    string apellido;
    string email;
    int vehiculosRentados;
    string direccion;
    bool activo;
};

struct Repuestos{
    string modeloRepuesto;
    string marcaRepuesto;
    string nombreRepuesto;
    string modeloAuto;
    int yearAuto;
    float precioRepuesto;
    int existencias;
};

// Definir los mapas para almacenar los datos
map<string, Vehiculos> vehiculosMap;
map<int, Clientes> clientesMap;
map<string, Repuestos> repuestosMap;
void leerVehiculos(const string &coches) {
    ifstream archivoVehiculos("../bin/coches.csv");
    string linea;

    if (!archivoVehiculos.is_open()) {
        cout << "No se pudo abrir el archivo " << coches << endl;
    }
            getline(archivoVehiculos, linea); // Leer encabezado y descartar
        while (getline(archivoVehiculos, linea)) {
            Vehiculos vehiculo;
            stringstream ss(linea);
            getline(ss, vehiculo.modelo, ',');
            getline(ss, vehiculo.marca, ',');
            getline(ss, vehiculo.placa, ',');
            getline(ss, vehiculo.color, ',');
            ss >> vehiculo.year;
            ss.ignore();
            ss >> vehiculo.kilometraje;
            ss.ignore();
            string rentado;
            getline(ss, rentado, ',');
            vehiculo.rentado = (rentado == "1");
            getline(ss, vehiculo.motor, ',');
            ss >> vehiculo.precioRenta;
            ss.ignore();
            ss >> vehiculo.cedCliente;
            ss.ignore();
            getline(ss, vehiculo.fechaEntrega, ',');
            vehiculosMap[vehiculo.placa] = vehiculo;
        }
        archivoVehiculos.close();
}

void leerClientes(const string &clientes) {
    ifstream archivoClientes("../bin/clientes.csv");
    string linea;

    if (! archivoClientes.is_open()) {
        cout << "No se pudo abrir el archivo " << clientes << endl;
    }
     getline(archivoClientes, linea); // Leer encabezado y descartar
        while (getline(archivoClientes, linea)) {
            Clientes cliente;
            stringstream ss(linea);
            ss >> cliente.cedula;
            ss.ignore();
            getline(ss, cliente.nombre, ',');
            getline(ss, cliente.apellido, ',');
            getline(ss, cliente.email, ',');
            ss >> cliente.vehiculosRentados;
            ss.ignore();
            getline(ss, cliente.direccion, ',');
            string activo;
            getline(ss, activo, ',');
            cliente.activo = (activo == "1");
            clientesMap[cliente.cedula] = cliente;
        }
        archivoClientes.close();
}

void leerRepuestos(const string &repuestos) {
    ifstream archivoRepuestos("../bin/repuestosCoches.csv");
    string linea;

    if (!archivoRepuestos.is_open()) {
        cout << "No se pudo abrir el archivo " << repuestos << endl;
    }
            getline(archivoRepuestos, linea); // Leer encabezado y descartar
        while (getline(archivoRepuestos, linea)) {
            Repuestos repuesto;
            stringstream ss(linea);
            getline(ss, repuesto.modeloRepuesto, ',');
            getline(ss, repuesto.marcaRepuesto, ',');
            getline(ss, repuesto.nombreRepuesto, ',');
            getline(ss, repuesto.modeloAuto, ',');
            ss >> repuesto.yearAuto;
            ss.ignore();
            ss >> repuesto.precioRepuesto;
            ss.ignore();
            ss >> repuesto.existencias;
            repuestosMap[repuesto.modeloRepuesto] = repuesto;
        }
        archivoRepuestos.close();
}

int main() {
    // Leer datos de los archivos 
    leerVehiculos("../bin/coches.csv");
    leerClientes("../bin/clientes.csv");
    leerRepuestos("../bin/repuestosCoches.csv");

    // Mostrar datos de los vehículos para verificar
    for (const auto &pair : vehiculosMap) {
        const Vehiculos &vehiculo = pair.second;
        cout << vehiculo.modelo
             << ", "<<vehiculo.marca 
             <<", "<< vehiculo.placa
             << ", "<<vehiculo.color
             << ", "<<vehiculo.year
             << ", "<<vehiculo.kilometraje
             << ", "<<vehiculo.rentado
             << ", "<<vehiculo.motor
             << ", "<<vehiculo.precioRenta
             << ", "<<vehiculo.cedCliente
             <<", "<< vehiculo.fechaEntrega<< endl;
    }

    // Mostrar datos de los clientes para verificar
    for (const auto &pair : clientesMap) {
        const Clientes &cliente = pair.second;
        cout << cliente.cedula 
             << ", "<< cliente.nombre 
             <<", " << cliente.apellido
             <<", " <<cliente.email
             <<", " <<cliente.vehiculosRentados
             <<", " <<cliente.direccion
             <<", " <<cliente.activo << endl;
    }

    // Mostrar datos de los repuestos para verificar
    for (const auto &pair : repuestosMap) {
        const Repuestos &repuesto = pair.second;
        cout <<repuesto.modeloRepuesto 
             <<", " <<repuesto.marcaRepuesto 
             <<", " <<repuesto.nombreRepuesto 
             <<", " <<repuesto.modeloAuto
             <<", " <<repuesto.yearAuto
             <<", " <<repuesto.precioRepuesto
             <<", " <<repuesto.existencias<< endl;
    }
    return 0;
}
