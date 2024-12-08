#include"Vehiculos.h"
#pragma once
using namespace std;

string Vehiculos:: getModelo() const{return modelo;};
string Vehiculos::getMarca() const{return marca;};
string Vehiculos::getPlaca() const{return placa;};
string Vehiculos::getColor() const{return color;};
int Vehiculos::getYear() const{return year;};
float Vehiculos::getKilometraje() const{return kilometraje;};
bool Vehiculos::getRentado() const{return rentado;};
string Vehiculos::getMotor() const{return motor;};
float Vehiculos::getPrecioRenta() const{return precioRenta;};
int Vehiculos::getCedCliente() const{return cedCliente;};
string Vehiculos::getFechaEntrega() const{return fechaEntrega;};


void Vehiculos::setModelo(const string &modelo){this->modelo = modelo;};
void Vehiculos::setMarca(const string &marca){this->marca = marca;};
void Vehiculos::setPlaca(const string &placa){this->placa = placa;};
void Vehiculos::setColor(const string &color){this->color = color;};
void Vehiculos::setYear(const int &year){this->year = year;};
void Vehiculos::setKilometraje(const float &kilometraje){this->kilometraje = kilometraje;};
void Vehiculos::setRentado(const bool &rentado){this->rentado = rentado;};
void Vehiculos::setMotor(const string &motor){this->motor = motor;};
void Vehiculos::setPrecioRenta(const float &precioRenta){this->precioRenta = precioRenta;};
void Vehiculos::setCedCliente(const int &cedCliente){this->cedCliente = cedCliente;};
void Vehiculos::setFechaEntrega(const string &fechaEntrega){this->fechaEntrega = fechaEntrega;};