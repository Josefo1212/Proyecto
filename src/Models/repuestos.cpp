#include"repuestos.h"
 string Repuestos::getModeloRepuesto() const{return modeloRepuesto;};
string Repuestos::getMarcaRepuesto() const{return marcaRepuesto;};
string Repuestos::getNombreRepuesto() const{return nombreRepuesto;};
string Repuestos::getModeloAuto() const{return modeloAuto;};
int Repuestos::getYearAuto() const{return yearAuto;};
float Repuestos::getPrecioRepuesto() const{return precioRepuesto;};
int Repuestos::getExistencias() const{return existencias;};

void Repuestos::setModeloRepuesto(const string &modeloRepuesto){this->modeloRepuesto = modeloRepuesto;};
void Repuestos::setMarcaRepuesto(const string &marcaRepuesto){this->marcaRepuesto = marcaRepuesto;};
void Repuestos::setNombreRepuesto(const string &nombreRepuesto){this->nombreRepuesto = nombreRepuesto;};
void Repuestos::setModeloAuto(const string &modeloAuto){this->modeloAuto = modeloAuto;};
void Repuestos::setYearAuto(const int &yearAuto){this->yearAuto = yearAuto;};
void Repuestos::setPrecioRepuesto(const float &precioRepuesto){this->precioRepuesto = precioRepuesto;};
void Repuestos::setExistencias(const int &existencias){this->existencias = existencias;};