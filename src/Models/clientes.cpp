#include"clientes.h"
#pragma once
int Clientes::getCedula() const{return cedula;};
string Clientes::getNombre() const{return nombre;};
string Clientes::getApellido() const{return apellido;};
string Clientes::getEmail()const{return email;};
int Clientes::getVehiculosRentados() const{return vehiculosRentados;};
string Clientes::getDireccion() const{return direccion;};
bool Clientes::getActivo() const{return activo;};


void Clientes::setCedula(const int &cedula){this->cedula = cedula;};
void Clientes::setNombre(const string &nombre){this->nombre = nombre;};
void Clientes::setApellido(const string &apellido){this->apellido = apellido;};
void Clientes::setEmail(const string &email){this->email = email;};
void Clientes::setVehiculosRentados(const int &vehiculosRentados){this->vehiculosRentados = vehiculosRentados;};
void Clientes::setDireccion(const string &direccion){this->direccion = direccion;};
void Clientes::setActivo(const bool &activo){this->activo = activo;};