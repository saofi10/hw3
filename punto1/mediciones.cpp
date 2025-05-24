#include "MEDICIONES.hpp"

//--------------------- implementacion MedicionBase---------------------
//constructor normal
MedicionBase::MedicionBase(float tiempo) : 
tiempoMedicion(std::make_unique<float>(tiempo)) {}
//para copy constructor para punto c
MedicionBase:: MedicionBase(const MedicionBase& other):
        tiempoMedicion(other.tiempoMedicion ? std::make_unique<float>(*other.tiempoMedicion) : nullptr) {}
MedicionBase& MedicionBase:: operator=(const MedicionBase& other){
    if (this!= &other){ // this apunta al obj q ejecut la funcion, o sea a MEdicionbase. evita copiar un obj sobre si mismo
        tiempoMedicion = other.tiempoMedicion ? std::make_unique<float>(*other.tiempoMedicion) : nullptr;
    }
    return *this; //desref el puntero, devuelve el obj en si.
    }

float MedicionBase::getTiempo() const {
    return tiempoMedicion ? *tiempoMedicion : 0.0f; // si hay tiempo de med devolvelo desreferenciado, sino empezalo en 0
}
//----------------------------------------------- implementacion Presion----------------------------
//constructor
Presion:: Presion(float p, float q, float t): MedicionBase(t), presionEstatica(p),presionDinamica(q){} //poner el constructor de la clase base primero
//otros
void Presion::imprimir() const{
        std::cout<<"Presion Estatica: "<< presionEstatica <<std::endl;
        std::cout<<"Presion Dinamica: "<< presionDinamica <<std::endl;
        std::cout<<"Tiempo: "<< getTiempo() <<std::endl;

}

void Presion::serializar(std::ofstream& out) const{ //serializo modo "p q t" en bin
    float tiempo = getTiempo();
    out.write(reinterpret_cast<const char*>(&presionEstatica), sizeof(float));
    out.write(reinterpret_cast<const char*>(&presionDinamica), sizeof(float));
    out.write(reinterpret_cast<const char*>(&tiempo), sizeof(float));
}
void Presion::deserializar(std::ifstream& in) { //deserializa p, q, t
    float tiempo;
    in.read(reinterpret_cast<char*>(&presionEstatica), sizeof(float));
    in.read(reinterpret_cast<char*>(&presionDinamica), sizeof(float));
    in.read(reinterpret_cast<char*>(&tiempo), sizeof(float));
    tiempoMedicion = std::make_unique<float>(tiempo);
}

// -----------------implementacion Posicion--------------------
Posicion::Posicion(float lat, float lon, float alt, float t) : 
    MedicionBase(t), latitud(lat), longitud(lon), altitud(alt) {}

void Posicion::imprimir() const {
    std::cout << "Posicion: Lat:" << latitud 
              << " Lon:" << longitud
              << " Alt:" << altitud
              << " Tiempo:" << getTiempo() << std::endl;
}

void Posicion::serializar(std::ofstream& out) const { //serializa lat, lon, alt, t
    float tiempo = getTiempo();
    out.write(reinterpret_cast<const char*>(&latitud), sizeof(float));
    out.write(reinterpret_cast<const char*>(&longitud), sizeof(float));
    out.write(reinterpret_cast<const char*>(&altitud), sizeof(float));
    out.write(reinterpret_cast<const char*>(&tiempo), sizeof(float));
}

void Posicion::deserializar(std::ifstream& in) { //deresializa lat, lon, alt, t
    float tiempo;
    in.read(reinterpret_cast<char*>(&latitud), sizeof(float));
    in.read(reinterpret_cast<char*>(&longitud), sizeof(float));
    in.read(reinterpret_cast<char*>(&altitud), sizeof(float));
    in.read(reinterpret_cast<char*>(&tiempo), sizeof(float));
    tiempoMedicion = std::make_unique<float>(tiempo);  // asignar tiempo
}

//---------------------implementar SaveFlightData-----------------------
SaveFlightData::SaveFlightData(const Posicion& p, const Presion& q) : 
    posicion(p), presion(q) {}

// serializar
void SaveFlightData::serializar(std::ofstream& out) const {
    if (!out) throw std::runtime_error("Error: archivo no abierto para escritura"); // este chequeo lo hago solo en saveflightdata porque esta clase es la que termina usando a las demas. La qe el usuario invoca entonces en donde finalmente quiero contemplar el error
    
    posicion.serializar(out);  //reuso
    presion.serializar(out);   
}
// deserializar binario
void SaveFlightData::deserializar(std::ifstream& in) {
    if (!in) throw std::runtime_error("Error: archivo no abierto para lectura");
    
    posicion.deserializar(in);  //deserializa Posicion
    presion.deserializar(in);   //deserializa Presion
}
//imprimir 
void SaveFlightData::imprimir() const {
    std::cout << "=== Informacion de Vuelo ===" << std::endl;
    posicion.imprimir();
    presion.imprimir();
}