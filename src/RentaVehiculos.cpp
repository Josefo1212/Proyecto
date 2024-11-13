#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
using namespace std;

// Estructuras de datos
struct Vehiculos {
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

struct Clientes {
    int cedula;
    string nombre;
    string apellido;
    string email;
    int vehiculosRentados;
    string direccion;
    bool activo;
};

struct Repuestos {
    string modeloRepuesto;
    string marcaRepuesto;
    string nombreRepuesto;
    string modeloAuto;
    int yearAuto;
    float precioRepuesto;
    int existencias;
};

// Mapas para almacenar los datos
map<string, Vehiculos> vehiculosMap;
map<int, Clientes> clientesMap;
map<string, Repuestos> repuestosMap;

// Funciones para leer vehículos, clientes y repuestos
void leerVehiculos(const string &coches) {
    ifstream archivoVehiculos(coches);
    string linea;

    if (!archivoVehiculos.is_open()) {
        cout << "No se pudo abrir el archivo " << coches << endl;
        return;
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
    ifstream archivoClientes(clientes);
    string linea;

    if (!archivoClientes.is_open()) {
        cout << "No se pudo abrir el archivo " << clientes << endl;
        return;
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
    ifstream archivoRepuestos(repuestos);
    string linea;

    if (!archivoRepuestos.is_open()) {
        cout << "No se pudo abrir el archivo " << repuestos << endl;
        return;
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

// Funciones para manejar vehículos
void actualizarVehiculo(const string &placa) {
    if (vehiculosMap.find(placa) != vehiculosMap.end()) {
        Vehiculos &vehiculo = vehiculosMap[placa];
        cout << "Ingrese nuevos datos (modelo, marca, color, year, kilometraje, rentado(1/0), motor, precioRenta, cedCliente, fechaEntrega): " << endl;
        cin >> vehiculo.modelo >> vehiculo.marca >> vehiculo.color >> vehiculo.year >> vehiculo.kilometraje;
        int rentado;
        cin >> rentado;
        vehiculo.rentado = rentado == 1;
        cin >> vehiculo.motor >> vehiculo.precioRenta >> vehiculo.cedCliente >> vehiculo.fechaEntrega;
    } else {
        cout << "Vehiculo no encontrado." << endl;
    }
}

void insertarVehiculo() {
    Vehiculos vehiculo;
    cout << "Ingrese datos del vehiculo (modelo, marca, placa, color, year, kilometraje, rentado(1/0), motor, precioRenta, cedCliente, fechaEntrega): " << endl;
    cin >> vehiculo.modelo >> vehiculo.marca >> vehiculo.placa >> vehiculo.color >> vehiculo.year >> vehiculo.kilometraje;
    int rentado;
    cin >> rentado;
    vehiculo.rentado = rentado == 1;
    cin >> vehiculo.motor >> vehiculo.precioRenta >> vehiculo.cedCliente >> vehiculo.fechaEntrega;
    vehiculosMap[vehiculo.placa] = vehiculo;
}

void borrarVehiculo(const string &placa) {
    if (vehiculosMap.erase(placa)) {
        cout << "Vehiculo eliminado." << endl;
    } else {
        cout << "Vehiculo no encontrado." << endl;
    }
}

void guardarVehiculos(const string &coches) {
    ofstream archivoVehiculos(coches);
    archivoVehiculos << "modelo,marca,placa,color,year,kilometraje,rentado,motor,precioRenta,cedCliente,fechaEntrega" << endl; // Encabezado
    for (const auto &pair : vehiculosMap) {
        const Vehiculos &vehiculo = pair.second;
        archivoVehiculos << vehiculo.modelo << ","
                         << vehiculo.marca << ","
                         << vehiculo.placa << ","
                         << vehiculo.color << ","
                         << vehiculo.year << ","
                         << vehiculo.kilometraje << ","
                         << (vehiculo.rentado ? "1" : "0") << ","
                         << vehiculo.motor << ","
                         << vehiculo.precioRenta << ","
                         << vehiculo.cedCliente << ","
                         << vehiculo.fechaEntrega << endl;
    }
    archivoVehiculos.close();
}

// Funciones para manejar clientes
void insertarCliente() {
    Clientes cliente;
    cout << "Ingrese datos del cliente (cedula, nombre, apellido, email, vehiculosRentados, direccion, activo(1/0)): " << endl;
    cin >> cliente.cedula;
    cin.ignore();
    getline(cin, cliente.nombre);
    getline(cin, cliente.apellido);
    getline(cin, cliente.email);
    cin >> cliente.vehiculosRentados;
    cin.ignore();
    getline(cin, cliente.direccion);
    int activo;
    cin >> activo;
    cliente.activo = activo == 1;
    clientesMap[cliente.cedula] = cliente;
}

void actualizarCliente(int cedula) {
    if (clientesMap.find(cedula) != clientesMap.end()) {
        Clientes &cliente = clientesMap[cedula];
        cout << "Ingrese nuevos datos (nombre, apellido, email, vehiculosRentados, direccion, activo(1/0)): " << endl;
        cin.ignore();
        getline(cin, cliente.nombre);
        getline(cin, cliente.apellido);
        getline(cin, cliente.email);
        cin >> cliente.vehiculosRentados;
        cin.ignore();
        getline(cin, cliente.direccion);
        int activo;
        cin >> activo;
        cliente.activo = activo == 1;
    } else {
        cout << "Cliente no encontrado." << endl;
    }
}

void borrarCliente(int cedula) {
    if (clientesMap.erase(cedula)) {
        cout << "Cliente eliminado." << endl;
    } else {
        cout << "Cliente no encontrado." << endl;
    }
}

void leerClientesDesdeMap() {
    for (const auto& pair : clientesMap) {
        const Clientes &cliente = pair.second;
        cout << cliente.cedula << ", "
             << cliente.nombre << ", "
             << cliente.apellido << ", "
             << cliente.email << ", "
             << cliente.vehiculosRentados << ", "
             << cliente.direccion << ", "
             << (cliente.activo ? "1" : "0") << endl;
    }
}

// Funciones para manejar repuestos
void insertarRepuesto() {
    Repuestos repuesto;
    cout << "Ingrese datos del repuesto (modeloRepuesto, marcaRepuesto, nombreRepuesto, modeloAuto, yearAuto, precioRepuesto, existencias): " << endl;
    cin.ignore();
    getline(cin, repuesto.modeloRepuesto);
    getline(cin, repuesto.marcaRepuesto);
    getline(cin, repuesto.nombreRepuesto);
    getline(cin, repuesto.modeloAuto);
    cin >> repuesto.yearAuto >> repuesto.precioRepuesto >> repuesto.existencias;
    repuestosMap[repuesto.modeloRepuesto] = repuesto;
}

void actualizarRepuesto(const string &modeloRepuesto) {
    if (repuestosMap.find(modeloRepuesto) != repuestosMap.end()) {
        Repuestos &repuesto = repuestosMap[modeloRepuesto];
        cout << "Ingrese nuevos datos (marcaRepuesto, nombreRepuesto, modeloAuto, yearAuto, precioRepuesto, existencias): " << endl;
        cin.ignore();
        getline(cin, repuesto.marcaRepuesto);
        getline(cin, repuesto.nombreRepuesto);
        getline(cin, repuesto.modeloAuto);
        cin >> repuesto.yearAuto >> repuesto.precioRepuesto >> repuesto.existencias;
    } else {
        cout << "Repuesto no encontrado." << endl;
    }
}

void borrarRepuesto(const string &modeloRepuesto) {
    if (repuestosMap.erase(modeloRepuesto)) {
        cout << "Repuesto eliminado." << endl;
    } else {
        cout << "Repuesto no encontrado." << endl;
    }
}

void leerRepuestosDesdeMap() {
    for (const auto& pair : repuestosMap) {
        const Repuestos &repuesto = pair.second;
        cout << repuesto.modeloRepuesto << ", "
             << repuesto.marcaRepuesto << ", "
             << repuesto.nombreRepuesto << ", "
             << repuesto.modeloAuto << ", "
             << repuesto.yearAuto << ", "
             << repuesto.precioRepuesto << ", "
             << repuesto.existencias << endl;
    }
}

int main() {
    leerVehiculos("../bin/coches.csv");
    leerClientes("../bin/clientes.csv");
    leerRepuestos("../bin/repuestosCoches.csv");

    int opcion;
    string placa;
    int cedula;
    string modeloRepuesto;

    do {
        cout << "Seleccione una opcion: " << endl;
        cout << "1. Insertar Vehiculo" << endl;
        cout << "2. Actualizar Vehiculo" << endl;
        cout << "3. Borrar Vehiculo" << endl;
        cout << "4. Leer Vehiculos" << endl;
        cout << "5. Guardar Vehiculos" << endl;
        cout << "6. Insertar Cliente" << endl;
        cout << "7. Actualizar Cliente" << endl;
        cout << "8. Borrar Cliente" << endl;
        cout << "9. Leer Clientes" << endl;
        cout << "10. Insertar Repuesto" << endl;
        cout << "11. Actualizar Repuesto" << endl;
        cout << "12. Borrar Repuesto" << endl;
        cout << "13. Leer Repuestos" << endl;
        cout << "14. Salir" << endl;
        cin >> opcion;

        switch (opcion) {
            case 1:
                insertarVehiculo();
                break;
            case 2:
                cout << "Ingrese la placa del vehiculo a actualizar: ";
                cin >> placa;
                actualizarVehiculo(placa);
                break;
            case 3:
                cout << "Ingrese la placa del vehiculo a borrar: ";
                cin >> placa;
                borrarVehiculo(placa);
                break;
            case 4:
                // Mostrar datos de los vehículos
                for (const auto &pair : vehiculosMap) {
                    const Vehiculos &vehiculo = pair.second;
                    cout << vehiculo.modelo
                         << ", " << vehiculo.marca
                         << ", " << vehiculo.placa
                         << ", " << vehiculo.color
                         << ", " << vehiculo.year
                         << ", " << vehiculo.kilometraje
                         << ", " << (vehiculo.rentado ? "1" : "0")
                         << ", " << vehiculo.motor
                         << ", " << vehiculo.precioRenta
                         << ", " << vehiculo.cedCliente
                         << ", " << vehiculo.fechaEntrega << endl;
                }
                break;
            case 5:
                guardarVehiculos("../bin/coches.csv");
                cout << "Vehículos guardados en el archivo." << endl;
                break;
            case 6:
                insertarCliente();
                break;
            case 7:
                cout << "Ingrese la cedula del cliente a actualizar: ";
                cin >> cedula;
                actualizarCliente(cedula);
                break;
            case 8:
                cout << "Ingrese la cedula del cliente a borrar: ";
                cin >> cedula;
                borrarCliente(cedula);
                break;
            case 9:
                leerClientesDesdeMap();
                break;
            case 10:
                insertarRepuesto();
                break;
            case 11:
                cout << "Ingrese el modelo del repuesto a actualizar: ";
                cin.ignore(); 
                getline(cin, modeloRepuesto);
                actualizarRepuesto(modeloRepuesto);
                break;
            case 12:
                cout << "Ingrese el modelo del repuesto a borrar: ";
                cin.ignore(); 
                getline(cin, modeloRepuesto);
                borrarRepuesto(modeloRepuesto);
                break;
            case 13:
                leerRepuestosDesdeMap();
                break;
            case 14:
                cout << "Saliendo." << endl;
                break;
            default:
                cout << "Opción no válida." << endl;
                break;
        }
    } while (opcion != 14);

    return 0;
}

