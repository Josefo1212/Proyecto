#ifndef VEHICULOS_H
#define VEHICULOS_H
#include<string>
using namespace std;

class Vehiculos{
    private:
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

    public:
        //Getters
        string getModelo() const;
        string getMarca() const;
        string getPlaca() const;
        string getColor() const;
        int getYear() const;
        float getKilometraje() const;
        bool getRentado() const;
        string getMotor() const;
        float getPrecioRenta() const;
        int getCedCliente() const;
        string getFechaEntrega() const;

        //Setters
        void setModelo(const string &modelo);
        void setMarca(const string &marca);
        void setPlaca(const string &placa);
        void setColor(const string &color);
        void setYear(const int &year);
        void setKilometraje(const float &kilometraje);
        void setRentado(const bool &rentado);
        void setMotor(const string &motor);
        void setPrecioRenta(const float &precioRenta);
        void setCedCliente(const int &cedCliente);
        void setFechaEntrega(const string &fechaEntrega);
};
#endif