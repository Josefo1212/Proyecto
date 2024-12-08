#ifndef REPUESTOS_H
#define REPUESTOS_H
#include<string>
#pragma once
using namespace std;

class Repuestos{
    private:
        string modeloRepuesto;
        string marcaRepuesto;
        string nombreRepuesto;
        string modeloAuto;
        int yearAuto;
        float precioRepuesto;
        int existencias;
    public:
        //Getters
        string getModeloRepuesto() const;
        string getMarcaRepuesto() const;
        string getNombreRepuesto() const;
        string getModeloAuto() const;
        int getYearAuto() const;
        float getPrecioRepuesto() const;
        int getExistencias() const;

        //Setters
        void setModeloRepuesto(const string &modeloRepusto);
        void setMarcaRepuesto(const string &marcaRepuesto);
        void setNombreRepuesto(const string &nombreRepuesto);
        void setModeloAuto(const string &modeloAuto);
        void setYearAuto(const int &yearAuto);
        void setPrecioRepuesto(const float &precioRepuesto);
        void setExistencias(const int &existencias);
};


#endif