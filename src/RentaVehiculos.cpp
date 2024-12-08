#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "./Models/Vehiculos.cpp"
#include "./Models/clientes.cpp"
#include "./Models/repuestos.cpp"
#include "./Controller/funcionVehiculos.cpp"
#include "./Controller/funcionClientes.cpp"
#include "./Controller/funcionRepuestos.cpp"
#include "./views/interfaz.cpp"
using namespace std;

Vehiculos* vehiculosPtr = nullptr;
int vehiculosCount = 0;

Clientes* clientesPtr = nullptr;
int clientesCount = 0;

Repuestos* repuestosPtr = nullptr;
int repuestosCount = 0;

int main() {
    leerVehiculos("../bin/coches.csv");
    leerClientes("../bin/clientes.csv");
    leerRepuestos("../bin/repuestosCoches.csv");

    int opcion;
    string placa;
    int cedula;
    string modeloRepuesto, marcaRepuesto, nombreRepuesto, modeloAuto;

    do {
        mostrarMenu();
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
                    cout << vehiculo.getModelo()
                         << ", " << vehiculo.getMarca()
                         << ", " << vehiculo.getPlaca()
                         << ", " << vehiculo.getColor()
                         << ", " << vehiculo.getYear()
                         << ", " << vehiculo.getKilometraje()
                         << ", " << (vehiculo.getRentado() ? "1" : "0")
                         << ", " << vehiculo.getMotor()
                         << ", " << vehiculo.getPrecioRenta()
                         << ", " << vehiculo.getCedCliente()
                         << ", " << vehiculo.getFechaEntrega() << endl;
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
                cout << "Ingrese el nombre del repuesto a actualizar: ";
                getline(cin, nombreRepuesto);
                cout << "Ingrese el modelo del Vehiculo del repuesto a actualizar: ";
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
                            if (vehiculosPtr[i].getPlaca() == placa) {
                                const Vehiculos &vehiculo = vehiculosPtr[i];
                                cout << vehiculo.getModelo() << ", "
                                     << vehiculo.getMarca() << ", "
                                     << vehiculo.getPlaca() << ", "
                                     << vehiculo.getColor() << ", "
                                     << vehiculo.getYear() << ", "
                                     << vehiculo.getKilometraje() << ", "
                                     << (vehiculo.getRentado() ? "1" : "0") << ", "
                                     << vehiculo.getMotor() << ", "
                                     << vehiculo.getPrecioRenta() << ", "
                                     << vehiculo.getCedCliente() << ", "
                                     << vehiculo.getFechaEntrega() << endl;
                                break;
                            }
                        }
                        break;
                    case 2:
                        cout << "Ingrese la cedula del cliente: ";
                        cin >> cedula;
                        for (int i = 0; i < clientesCount; ++i) {
                            if (clientesPtr[i].getCedula() == cedula) {
                                const Clientes &cliente = clientesPtr[i];
                                cout << cliente.getNombre() << ", "
                                     << cliente.getApellido() << ", "
                                     << cliente.getCedula() << ", "
                                     << cliente.getEmail() << ", "
                                     << cliente.getVehiculosRentados() << ", "
                                     << cliente.getDireccion() << ", "
                                     << (cliente.getActivo() ? "1" : "0") << endl;
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
                            if (repuestosPtr[i].getModeloRepuesto() == modeloRepuesto && repuestosPtr[i].getMarcaRepuesto() == marcaRepuesto && repuestosPtr[i].getNombreRepuesto() == nombreRepuesto && repuestosPtr[i].getModeloAuto() == modeloAuto) {
                                const Repuestos &repuesto = repuestosPtr[i];
                                cout << repuesto.getModeloRepuesto() << ", "
                                     << repuesto.getMarcaRepuesto() << ", "
                                     << repuesto.getNombreRepuesto() << ", "
                                     << repuesto.getModeloAuto() << ", "
                                     << repuesto.getYearAuto() << ", "
                                     << repuesto.getPrecioRepuesto() << ", "
                                     << repuesto.getExistencias() << endl;
                                break;
                            }
                        }
                        break;
                    default:
                        cout << "Opcion no valida." << endl;
                        break;
                }
            }
            break;
            case 14:
                cout << "Saliendo." << endl;
                break;
            default:
                cout << "Opcion no valida." << endl;
                break;
        }
    } while (opcion != 14);

    return 0;
}