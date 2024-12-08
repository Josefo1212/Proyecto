#ifndef CLIENTES_H
#define CLIENTES_H

#include<iostream>
using namespace std;

class Clientes{
    private:
        int cedula;
        string nombre;
        string apellido;
        string email;
        int vehiculosRentados;
        string direccion;
        bool activo;
    public:
        //Getters
        int getCedula() const;
        string getNombre() const;
        string getApellido() const;
        string getEmail()const;
        int getVehiculosRentados() const;
        string getDireccion() const;
        bool getActivo() const;

        //Setters
        void setCedula(const int &cedula);
        void setNombre(const string &nombre);
        void setApellido(const string &apellido);
        void setEmail(const string &email);
        void setVehiculosRentados(const int &vehiculosRentados);
        void setDireccion(const string &direccion);
        void setActivo(const bool &activo);
};

#endif