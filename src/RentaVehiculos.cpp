#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;

// Estructuras de datos
struct Vehiculos {
    string modelo;
    string marca;
    string placa;
    string color;
    int year;
    float kilometraje;
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


Vehiculos* vehiculosPtr = nullptr;
int vehiculosCount = 0;

Clientes* clientesPtr = nullptr;
int clientesCount = 0;

Repuestos* repuestosPtr = nullptr;
int repuestosCount = 0;

// Funciones para leer vehículos, clientes y repuestos
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

void leerClientes(const string &clientes) {
    ifstream archivoClientes(clientes);
    string linea;

    if (!archivoClientes.is_open()) {
        cout << "No se pudo abrir el archivo " << clientes << endl;
        return;
    }
    getline(archivoClientes, linea); 
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

        Clientes* temp = new Clientes[clientesCount + 1];
        for (int i = 0; i < clientesCount; ++i) {
            temp[i] = clientesPtr[i];
        }
        temp[clientesCount] = cliente;
        delete[] clientesPtr;
        clientesPtr = temp;
        clientesCount++;
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
    getline(archivoRepuestos, linea);
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

// Funciones para manejar vehículos
void guardarVehiculos(const string &coches) {
    ofstream archivoVehiculos(coches);
    archivoVehiculos << "modelo,marca,placa,color,year,kilometraje,rentado,motor,precioRenta,cedCliente,fechaEntrega" << endl; // Encabezado
    for (int i = 0; i < vehiculosCount; ++i) {
        const Vehiculos &vehiculo = vehiculosPtr[i];
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

void actualizarVehiculo(const string &placa) {
    for (int i = 0; i < vehiculosCount; ++i) {
        if (vehiculosPtr[i].placa == placa) {
            Vehiculos original = vehiculosPtr[i];
            Vehiculos &vehiculo = vehiculosPtr[i];
            cout << "Ingrese nuevos datos (modelo, marca, color, year, kilometraje, rentado(1/0), motor, precioRenta, cedCliente, fechaEntrega): " << endl;
            cin >> vehiculo.modelo >> vehiculo.marca >> vehiculo.color >> vehiculo.year >> vehiculo.kilometraje;
            int rentado;
            cin >> rentado;
            vehiculo.rentado = rentado == 1;
            cin >> vehiculo.motor >> vehiculo.precioRenta >> vehiculo.cedCliente >> vehiculo.fechaEntrega;

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
    cin >> vehiculo.modelo >> vehiculo.marca >> vehiculo.placa >> vehiculo.color >> vehiculo.year >> vehiculo.kilometraje;
    int rentado;
    cin >> rentado;
    vehiculo.rentado = rentado == 1;
    cin >> vehiculo.motor >> vehiculo.precioRenta >> vehiculo.cedCliente >> vehiculo.fechaEntrega;

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
        if (vehiculosPtr[i].placa == placa) {
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

// Funciones para manejar clientes
void guardarClientes(const string &clientes) {
    ofstream archivoClientes(clientes);
    archivoClientes << "cedula,nombre,apellido,email,vehiculosRentados,direccion,activo" << endl; 
    for (int i = 0; i < clientesCount; ++i) {
        const Clientes &cliente = clientesPtr[i];
        archivoClientes << cliente.cedula << ","
                        << cliente.nombre << ","
                        << cliente.apellido << ","
                        << cliente.email << ","
                        << cliente.vehiculosRentados << ","
                        << cliente.direccion << ","
                        << (cliente.activo ? "1" : "0") << endl;
    }
    archivoClientes.close();
}

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

    cout << "Confirma la insercion del cliente? (s/n): ";
    char confirmacion;
    cin >> confirmacion;
    if (confirmacion == 's' || confirmacion == 'S') {
        Clientes* temp = new Clientes[clientesCount + 1];
        for (int i = 0; i < clientesCount; ++i) {
            temp[i] = clientesPtr[i];
        }
        temp[clientesCount] = cliente;
        delete[] clientesPtr;
        clientesPtr = temp;
        clientesCount++;
        guardarClientes("../bin/clientes.csv");
        cout << "Cliente insertado." << endl;
    } else {
        cout << "Insercion cancelada." << endl;
    }
}

void actualizarCliente(int cedula) {
    for (int i = 0; i < clientesCount; ++i) {
        if (clientesPtr[i].cedula == cedula) {
            Clientes original = clientesPtr[i];
            Clientes &cliente = clientesPtr[i];
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

            cout << "Confirma los cambios? (s/n): ";
            char confirmacion;
            cin >> confirmacion;
            if (confirmacion == 's' || confirmacion == 'S') {
                guardarClientes("../bin/clientes.csv");
                cout << "Cambios confirmados y guardados." << endl;
            } else {
                clientesPtr[i] = original;
                cout << "Cambios revertidos." << endl;
            }
            return;
        }
    }
    cout << "Cliente no encontrado." << endl;
}

void borrarCliente(int cedula) {
    for (int i = 0; i < clientesCount; ++i) {
        if (clientesPtr[i].cedula == cedula) {
            cout << "Esta seguro de que desea eliminar el cliente con cedula " << cedula << "? (s/n): ";
            char confirmacion;
            cin >> confirmacion;
            if (confirmacion == 's' || confirmacion == 'S') {
                Clientes* temp = new Clientes[clientesCount - 1];
                for (int j = 0, k = 0; j < clientesCount; ++j) {
                    if (j != i) {
                        temp[k++] = clientesPtr[j];
                    }
                }
                delete[] clientesPtr;
                clientesPtr = temp;
                clientesCount--;
                guardarClientes("../bin/clientes.csv");
                cout << "Cliente eliminado." << endl;
            } else {
                cout << "Eliminacion cancelada." << endl;
            }
            return;
        }
    }
    cout << "Cliente no encontrado." << endl;
}

void leerClientesDesdeArray() {
    for (int i = 0; i < clientesCount; ++i) {
        const Clientes &cliente = clientesPtr[i];
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
void guardarRepuesto(const string &repuestos) {
    ofstream archivoRepuestos(repuestos);
    archivoRepuestos << "Modelo,Marca,Nombre,Modelo_Auto,Year_Auto,Precio,Existencias" << endl; 
    for (int i = 0; i < repuestosCount; ++i) {
        const Repuestos &repuesto = repuestosPtr[i];
        archivoRepuestos << repuesto.modeloRepuesto << ","
                         << repuesto.marcaRepuesto << ","
                         << repuesto.nombreRepuesto << ","
                         << repuesto.modeloAuto << ","
                         << repuesto.yearAuto << ","
                         << repuesto.precioRepuesto << ","
                         << repuesto.existencias << endl;
    }
    archivoRepuestos.close();
}

void insertarRepuesto() {
    Repuestos repuesto;
    cout << "Ingrese datos del repuesto (modeloRepuesto, marcaRepuesto, nombreRepuesto, modeloAuto, yearAuto, precioRepuesto, existencias): " << endl;
    cin.ignore(); 
    getline(cin, repuesto.modeloRepuesto);
    getline(cin, repuesto.marcaRepuesto);
    getline(cin, repuesto.nombreRepuesto);
    getline(cin, repuesto.modeloAuto);
    cin >> repuesto.yearAuto >> repuesto.precioRepuesto >> repuesto.existencias;
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
        if (repuestosPtr[i].modeloRepuesto == modeloRepuesto && repuestosPtr[i].marcaRepuesto == marcaRepuesto && repuestosPtr[i].nombreRepuesto == nombreRepuesto && repuestosPtr[i].modeloAuto == modeloAuto) {
            Repuestos original = repuestosPtr[i];
            Repuestos &repuesto = repuestosPtr[i];
            cout << "Ingrese nuevos datos (marcaRepuesto, nombreRepuesto, modeloAuto, yearAuto, precioRepuesto, existencias): " << endl;
            cin.ignore();
            getline(cin, repuesto.marcaRepuesto);
            getline(cin, repuesto.nombreRepuesto);
            getline(cin, repuesto.modeloAuto);
            cin >> repuesto.yearAuto >> repuesto.precioRepuesto >> repuesto.existencias;

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
        if (repuestosPtr[i].modeloRepuesto == modeloRepuesto && repuestosPtr[i].marcaRepuesto == marcaRepuesto && repuestosPtr[i].nombreRepuesto == nombreRepuesto && repuestosPtr[i].modeloAuto == modeloAuto) {
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
    string modeloRepuesto, marcaRepuesto, nombreRepuesto, modeloAuto;

    do {
        cout << "Seleccione una opcion: " << endl
             << "1. Insertar Vehiculo" << endl
             << "2. Actualizar Vehiculo" << endl
             << "3. Borrar Vehiculo" << endl
             << "4. Leer Vehiculos" << endl
             << "5. Insertar Cliente" << endl
             << "6. Actualizar Cliente" << endl
             << "7. Borrar Cliente" << endl
             << "8. Leer Clientes" << endl
             << "9. Insertar Repuesto" << endl
             << "10. Actualizar Repuesto" << endl
             << "11. Borrar Repuesto" << endl
             << "12. Leer Repuestos" << endl
             << "13. Realizar consultas especificas" << endl
             << "14. Salir"<<endl;
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
                for (int i = 0; i < vehiculosCount; ++i) {
                    const Vehiculos &vehiculo = vehiculosPtr[i];
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
                insertarCliente();
                break;
            case 6:
                cout << "Ingrese la cedula del cliente a actualizar: ";
                cin >> cedula;
                actualizarCliente(cedula);
                break;
            case 7:
                cout << "Ingrese la cedula del cliente a borrar: ";
                cin >> cedula;
                borrarCliente(cedula);
                break;
            case 8:
                leerClientesDesdeArray();
                break;
            case 9:
                insertarRepuesto();
                break;
            case 10:
                cout << "Ingrese el modelo del repuesto a actualizar: ";
                cin.ignore(); 
                getline(cin, modeloRepuesto);
                cout << "Ingrese la marca del repuesto a actualizar: ";
                getline(cin, marcaRepuesto);
                cout<< "Ingrese el nombre del repuesto a actualizar: ";
                getline(cin, nombreRepuesto);
                cout<< "Ingrese el modelo del Vehiculo del repuesto a actualizar: ";
                getline(cin, modeloAuto);
                actualizarRepuesto(modeloRepuesto, marcaRepuesto, nombreRepuesto, modeloAuto);
                break;
            case 11:
                cout << "Ingrese el modelo del repuesto a borrar: ";
                cin.ignore(); 
                getline(cin, modeloRepuesto);
                cout << "Ingrese la marca del repuesto a borrar: ";
                getline(cin, marcaRepuesto);
                cout << "Ingrese el nombre del repuesto a borrar: ";
                getline(cin, nombreRepuesto);
                cout << "Ingrese el modelo del carro del repuesto a borrar: ";
                getline(cin, modeloAuto);
                borrarRepuesto(modeloRepuesto, marcaRepuesto, nombreRepuesto, modeloAuto);
                break;
            case 12:
                leerRepuestosDesdeArray();
                break;
            case 13: {
                int subOpcion;
                cout << "Seleccione la consulta que desea realizar: " << endl
                     << "1. Consultar un Vehiculo" << endl
                     << "2. Consultar un Cliente" << endl
                     << "3. Consultar un Repuesto" << endl;
                cin >> subOpcion;
                string clave;

                switch (subOpcion) {
                    case 1:
                        cout << "Ingrese la placa del vehiculo: ";
                        cin >> placa;
                        for (int i = 0; i < vehiculosCount; ++i) {
                            if (vehiculosPtr[i].placa == placa) {
                                const Vehiculos &vehiculo = vehiculosPtr[i];
                                cout << vehiculo.modelo << ", "
                                     << vehiculo.marca << ", "
                                     << vehiculo.placa << ", "
                                     << vehiculo.color << ", "
                                     << vehiculo.year << ", "
                                     << vehiculo.kilometraje << ", "
                                     << (vehiculo.rentado ? "1" : "0") << ", "
                                     << vehiculo.motor << ", "
                                     << vehiculo.precioRenta << ", "
                                     << vehiculo.cedCliente << ", "
                                     << vehiculo.fechaEntrega << endl;
                                break;
                            }
                        }
                        break;
                    case 2:
                        cout << "Ingrese la cedula del cliente: ";
                        cin >> cedula;
                        for (int i = 0; i < clientesCount; ++i) {
                            if (clientesPtr[i].cedula == cedula) {
                                const Clientes &cliente = clientesPtr[i];
                                cout << cliente.nombre << ", "
                                     << cliente.apellido << ", "
                                     << cliente.cedula << ", "
                                     << cliente.email << ", "
                                     << cliente.vehiculosRentados << ", "
                                     << cliente.direccion << ", "
                                     << (cliente.activo ? "1" : "0") << endl;
                                break;
                            }
                        }
                        break;
                    case 3:
                        cout << "Ingrese el modelo del repuesto: ";
                        cin.ignore();
                        getline(cin, modeloRepuesto);
                        cout << "Ingrese la marca del repuesto: ";
                        getline(cin, marcaRepuesto);
                        cout << "Ingrese el nombre del repuesto: ";
                        getline(cin, nombreRepuesto);
                        cout << "Ingrese el modelo del carro del repuesto: ";
                        getline(cin, modeloAuto);
                        for (int i = 0; i < repuestosCount; ++i) {
                            if (repuestosPtr[i].modeloRepuesto == modeloRepuesto && repuestosPtr[i].marcaRepuesto == marcaRepuesto && repuestosPtr[i].nombreRepuesto == nombreRepuesto && repuestosPtr[i].modeloAuto == modeloAuto) {
                                const Repuestos &repuesto = repuestosPtr[i];
                                cout << repuesto.modeloRepuesto << ", "
                                     << repuesto.marcaRepuesto << ", "
                                     << repuesto.nombreRepuesto << ", "
                                     << repuesto.modeloAuto << ", "
                                     << repuesto.yearAuto << ", "
                                     << repuesto.precioRepuesto << ", "
                                     << repuesto.existencias << endl;
                                break;
                            }
                        }
                        break;
                    default:
                        cout<< "Opcion no valida." << endl;
                        break;
                }
            }
            break;
            case 14:
                cout<< "Saliendo." << endl;
                break;
            default:
                cout<< "Opcion no valida." << endl;
                break;
        }
    } while (opcion != 14);
    
    return 0;
}