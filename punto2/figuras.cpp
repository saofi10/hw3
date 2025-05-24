#include "Figuras.hpp"
#include<stdexcept>
#define PI 3.141592653589793

//------------------------------- Punto --------------------------------
Punto::Punto(double x, double y) : x(x), y(y) {}

double Punto::getX() const {
    return x;
}

double Punto::getY() const {
    return y;
}

void Punto::setX(double x) {
    this->x = x;
}

void Punto::setY(double y) {
    this->y = y;
}

//------------------------------- Circulo ------------------------------
Circulo::Circulo(double x, double y, double r) 
    : centro(x, y), radio(r) {}

double Circulo::getRadio() const {
    return radio;
}

void Circulo::setRadio(double r) {
    if (r <= 0) throw std::invalid_argument("Radio debe ser positivo");
    radio = r;
}

void Circulo::setCentro(double x, double y) {
    centro = Punto(x, y);
}

//------------------------------- Elipse ------------------------------
Elipse::Elipse(double x, double y, double a, double b)
    : centro(x, y), semiejeMayor(a), semiejeMenor(b) {}

double Elipse::getSemiejeMayor() const {
    return semiejeMayor;
}

double Elipse::getSemiejeMenor() const {
    return semiejeMenor;
}

void Elipse::setSemiejeMayor(double a) {
     if (a <= 0) throw std::invalid_argument("Semieje mayor debe ser positivo");
    semiejeMayor = a;
}

void Elipse::setSemiejeMenor(double b) {
    if (b <= 0) throw std::invalid_argument("Semieje menor debe ser positivo");
    semiejeMenor = b;
}

void Elipse::setCentro(double x, double y) {
    centro = Punto(x, y);
}

//------------------------------- Rectangulo ---------------------------
Rectangulo::Rectangulo(double x, double y, double a, double h)
    : verticeInfIzq(x, y), ancho(a), alto(h) {}

double Rectangulo::getAncho() const {
    return ancho;
}
double Rectangulo::getAlto() const {
    return alto;
}

void Rectangulo::setAncho(double a) {
    if (a <= 0) throw std::invalid_argument("Ancho debe ser positivo");
    ancho = a;
}

void Rectangulo::setAlto(double h) {
    if (h <= 0) throw std::invalid_argument("Ancho debe ser positivo");
    alto = h;
}

void Rectangulo::setPosicion(double x, double y) {
    verticeInfIzq = Punto(x, y);
}

//---------------- ProcesadorFigura (Especializaciones) ----------------
template<>
double ProcesadorFigura<Punto>::calcularArea(const Punto& p) { //issame  compara tipos
     static_assert(std::is_same_v<decltype(p), const Punto&>,
        "Implementación incorrecta para Punto"); //decltype(var) te devuelve el tipo de la bariable
    return 0; //pq siempre es 0
}
template<>
double ProcesadorFigura<Circulo>::calcularArea(const Circulo& c) { //issame  compara tipos
     static_assert(std::is_same_v<decltype(c), const Circulo&>,
        "Implementación incorrecta para Círculo"); //decltype(var) te devuelve el tipo de la bariable
    return PI * c.getRadio() * c.getRadio(); //formula pi.r^2
}

template<>
double ProcesadorFigura<Elipse>::calcularArea(const Elipse& e) {
     static_assert(std::is_same_v<decltype(e), const Elipse&>, 
        "Implementación incorrecta para Elipse"); 
    return PI * e.getSemiejeMayor() * e.getSemiejeMenor(); //formula pi.a.b
}

template<>
double ProcesadorFigura<Rectangulo>::calcularArea(const Rectangulo& r) {
     static_assert(std::is_same_v<decltype(r), const Rectangulo&>, 
        "Implementación incorrecta para Rectangulo");
    return r.getAncho() * r.getAlto(); //formula base.altura
}
