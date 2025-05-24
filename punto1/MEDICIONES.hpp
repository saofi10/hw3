#ifndef MEDICIONES_HPP
#define MEDICIONES_HPP

#include <string>
#include <iostream>
#include <fstream>
#include <memory>

//--------------------interfazMediciones----------------------------------------------- 
class IMediciones{
    public:
        virtual void serializar(std::ofstream& out) const = 0;
        virtual void deserializar(std::ifstream& in) = 0;
        virtual ~IMediciones() = default; 
};
//------------------------------ MedicionBAse----------------------------------------------- 
class MedicionBase: public IMediciones{
    protected:
        std::unique_ptr<float> tiempoMedicion;
    public:
        explicit MedicionBase(float tiempo); // si es explicit va a prevenir conversion de tipos automatica, evita que un float x ej se convierta en clase MEdicion base
        virtual ~MedicionBase() = default;

        //para c 
        MedicionBase(const MedicionBase& other);  //copy constructor
        MedicionBase& operator=(const MedicionBase& other);  // Operador de asignación

        float getTiempo() const;
        virtual void imprimir() const=0;
};
//-----------------------------------Presion----------------------------------------------- 
class Presion : public MedicionBase{
    public:
        float presionEstatica, presionDinamica;//respectivamente p, q
    //constructor
        Presion(float p, float q, float t);
        void imprimir() const override; 
        void serializar(std::ofstream& out) const override ;
        void deserializar(std::ifstream& in) override ;
};
//----------------------------------------------- Posicion----------------------------------------------- 
class Posicion : public MedicionBase{
    public:
        float latitud, longitud, altitud;
    //constructor
        Posicion(float lat,float lon, float alt, float t);
        void imprimir() const override;
        void serializar(std::ofstream& out) const override ;
        void deserializar(std::ifstream& in) override ;
};
//----------------------------------------------- SaveFlightData----------------------------------------------- 
class SaveFlightData {
    public:
        Posicion posicion; // atributos x valor
        Presion presion;
    // pero aca recibe por referencia
        // constructor por defecto para empezarlos en 000, sino no seria agregacion porque si o si tendrias que tener presion y posicion.
        SaveFlightData() : posicion(0, 0, 0, 0), presion(0, 0, 0) {}  
        SaveFlightData(const Posicion& p, const Presion& q);
        void imprimir() const;         
        void serializar(std::ofstream& out) const;
        void deserializar(std::ifstream& in);
};
 
#endif