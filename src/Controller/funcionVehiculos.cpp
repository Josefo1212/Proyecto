#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include"../Models/Vehiculos.h"
using namespace std;

extern Vehiculos* vehiculosPtr;
extern int vehiculosCount;

void leerVehiculos(const string &coches) {
    ifstream archivoVehiculos("../bin/coches.csv");
    string linea;

    if (!archivoVehiculos.is_open()) {
        cout << "No se pudo abrir el archivo " << coches << endl;
        return;
    }
    getline(archivoVehiculos, linea);
    while (getline(archivoVehiculos, linea)) {
        Vehiculos vehiculo;
        stringstream ss(linea);
        string tempStr;
        int tempInt;
        double tempDouble;

        getline(ss, tempStr, ',');
        vehiculo.setModelo(tempStr);
        getline(ss, tempStr, ',');
        vehiculo.setMarca(tempStr);
        getline(ss, tempStr, ',');
        vehiculo.setPlaca(tempStr);
        getline(ss, tempStr, ',');
        vehiculo.setColor(tempStr);
        ss >> tempInt;
        vehiculo.setYear(tempInt);
        ss.ignore();
        ss >> tempDouble;
        vehiculo.setKilometraje(tempDouble);
        ss.ignore();
        getline(ss, tempStr, ',');
        vehiculo.setRentado(tempStr == "1");
        getline(ss, tempStr, ',');
        vehiculo.setMotor(tempStr);
        ss >> tempDouble;
        vehiculo.setPrecioRenta(tempDouble);
        ss.ignore();
        ss >> tempInt;
        vehiculo.setCedCliente(tempInt);
        ss.ignore();
        getline(ss, tempStr, ',');
        vehiculo.setFechaEntrega(tempStr);

        Vehiculos* temp = new Vehiculos[vehiculosCount + 1];
        for (int i = 0; i < vehiculosCount; ++i) {
            temp[i] = vehiculosPtr[i];
        }
        temp[vehiculosCount] = vehiculo;
        delete[] vehiculosPtr;
        vehiculosPtr = temp;
        vehiculosCount++;
    }
    archivoVehiculos.close();
}
void guardarVehiculos(const string &coches) {
    ofstream archivoVehiculos(coches);
    archivoVehiculos << "modelo,marca,placa,color,year,kilometraje,rentado,motor,precioRenta,cedCliente,fechaEntrega" << endl; // Encabezado
    for (int i = 0; i < vehiculosCount; ++i) {
        const Vehiculos &vehiculo = vehiculosPtr[i];
        archivoVehiculos << vehiculo.getModelo() << ","
                         << vehiculo.getMarca() << ","
                         << vehiculo.getPlaca() << ","
                         << vehiculo.getColor() << ","
                         << vehiculo.getYear() << ","
                         << vehiculo.getKilometraje() << ","
                         << (vehiculo.getRentado() ? "1" : "0") << ","  // Corrected line
                         << vehiculo.getMotor() << ","
                         << vehiculo.getPrecioRenta() << ","
                         << vehiculo.getCedCliente() << ","
                         << vehiculo.getFechaEntrega() << endl;
    }
    archivoVehiculos.close();
}

void actualizarVehiculo(const string &placa) {
    for (int i = 0; i < vehiculosCount; ++i) {
        if (vehiculosPtr[i].getPlaca() == placa) {
            Vehiculos original = vehiculosPtr[i];
            Vehiculos &vehiculo = vehiculosPtr[i];
            cout << "Ingrese nuevos datos (modelo, marca, color, year, kilometraje, rentado(1/0), motor, precioRenta, cedCliente, fechaEntrega): " << endl;
            string modelo, marca, color, motor, fechaEntrega;
            int year, rentado, cedCliente;
            double kilometraje, precioRenta;
            cin >> modelo >> marca >> color >> year >> kilometraje >> rentado >> motor >> precioRenta >> cedCliente >> fechaEntrega;
            vehiculo.setModelo(modelo);
            vehiculo.setMarca(marca);
            vehiculo.setColor(color);
            vehiculo.setYear(year);
            vehiculo.setKilometraje(kilometraje);
            vehiculo.setRentado(rentado == 1);
            vehiculo.setMotor(motor);
            vehiculo.setPrecioRenta(precioRenta);
            vehiculo.setCedCliente(cedCliente);
            vehiculo.setFechaEntrega(fechaEntrega);

            cout << "Confirma los cambios? (s/n): ";
            char confirmacion;
            cin >> confirmacion;
            if (confirmacion == 's' || confirmacion == 'S') {
                // Guardar cambios en archivo
                guardarVehiculos("../bin/coches.csv");
                cout << "Cambios confirmados y guardados." << endl;
            } else {
                vehiculosPtr[i] = original;
                cout << "Cambios revertidos." << endl;
            }
            return;
        }
    }
    cout << "Vehiculo no encontrado." << endl;
}

void insertarVehiculo() {
    Vehiculos vehiculo;
    cout << "Ingrese datos del vehiculo (modelo, marca, placa, color, year, kilometraje, rentado(1/0), motor, precioRenta, cedCliente, fechaEntrega): " << endl;
    string modelo, marca, placa, color, motor, fechaEntrega;
    int year, rentado, cedCliente;
    double kilometraje, precioRenta;
    cin >> modelo >> marca >> placa >> color >> year >> kilometraje >> rentado >> motor >> precioRenta >> cedCliente >> fechaEntrega;
    vehiculo.setModelo(modelo);
    vehiculo.setMarca(marca);
    vehiculo.setPlaca(placa);
    vehiculo.setColor(color);
    vehiculo.setYear(year);
    vehiculo.setKilometraje(kilometraje);
    vehiculo.setRentado(rentado == 1);
    vehiculo.setMotor(motor);
    vehiculo.setPrecioRenta(precioRenta);
    vehiculo.setCedCliente(cedCliente);
    vehiculo.setFechaEntrega(fechaEntrega);

    cout << "Confirma la insercion del vehiculo? (s/n): ";
    char confirmacion;
    cin >> confirmacion;
    if (confirmacion == 's' || confirmacion == 'S') {
        Vehiculos* temp = new Vehiculos[vehiculosCount + 1];
        for (int i = 0; i < vehiculosCount; ++i) {
            temp[i] = vehiculosPtr[i];
        }
        temp[vehiculosCount] = vehiculo;
        delete[] vehiculosPtr;
        vehiculosPtr = temp;
        vehiculosCount++;
        guardarVehiculos("../bin/coches.csv");
        cout << "Vehiculo insertado." << endl;
    } else {
        cout << "Insercion cancelada." << endl;
    }
}
void borrarVehiculo(const string &placa) {
    for (int i = 0; i < vehiculosCount; ++i) {
        if (vehiculosPtr[i].getPlaca() == placa) {
            cout << "Esta seguro de que desea eliminar el vehiculo con placa " << placa << "? (s/n): ";
            char confirmacion;
            cin >> confirmacion;
            if (confirmacion == 's' || confirmacion == 'S') {
                Vehiculos* temp = new Vehiculos[vehiculosCount - 1];
                for (int j = 0, k = 0; j < vehiculosCount; ++j) {
                    if (j != i) {
                        temp[k++] = vehiculosPtr[j];
                    }
                }
                delete[] vehiculosPtr;
                vehiculosPtr = temp;
                vehiculosCount--;
                guardarVehiculos("../bin/coches.csv");
                cout << "Vehiculo eliminado." << endl;
            } else {
                cout << "Eliminacion cancelada." << endl;
            }
            return;
        }
    }
    cout << "Vehiculo no encontrado." << endl;
}

