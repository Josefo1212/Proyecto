#include<iostream>
#include "../Models/Usuario.cpp"
#include "../Models/Permisos.cpp"
#include "../Controller/funcionAdmin.cpp"
#pragma once
using namespace std;

void mostrarMenu(const string& rol){
    cout << "Seleccione una opcion: " << endl;
    if (rol == "admin" || rol == "manager") {
        cout << "1. Insertar Vehiculo" << endl
             << "2. Actualizar Vehiculo" << endl
             << "3. Borrar Vehiculo" << endl
             << "4. Leer Vehiculos" << endl;
    }
    if (rol == "admin" || rol == "manager" ) {
        cout << "5. Insertar Cliente" << endl
             << "6. Actualizar Cliente" << endl
             << "7. Borrar Cliente" << endl
             << "8. Leer Clientes" << endl;
    }
    if (rol == "admin" || rol == "manager") {
        cout << "9. Insertar Repuesto" << endl
             << "10. Actualizar Repuesto" << endl
             << "11. Borrar Repuesto" << endl
             << "12. Leer Repuestos" << endl;
    }
    if (rol == "admin" || rol == "empleado") {
        cout << "13. Realizar consultas especificas" << endl;
    }
    if (rol == "admin") {
        cout << "14. Realizar copia de seguridad" << endl;
    }
    if (rol == "admin" || rol == "empleado") {
        cout << "15. Rentar un Vehiculo" << endl;
    }
    if (rol == "admin") {
        cout << "16. Agregar un usuario" << endl;
    }
    cout << "17. Salir" << endl;
}