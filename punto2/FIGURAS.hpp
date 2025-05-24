#ifndef FIGURAS_HPP
#define FIGURAS_HPP
#include <type_traits> // Para static_assert

//--------------------------------  Punto --------------------------------
class Punto {
private:
    double x,y;
public:
    Punto(double x = 0.0, double y = 0.0);
    double getX() const;
    double getY() const;
    void setX(double x);
    void setY(double y);
};

//--------------------------------  Circulo ---------------------
class Circulo {
private:
    Punto centro; //Composicion
    double radio;
public:
    Circulo(double x = 0.0, double y = 0.0, double r = 1.0);
    double getRadio() const;
    void setRadio(double r);
    void setCentro(double x, double y); //y tinee q pasarlo a punto
};

//------------------------------- Elipse -----------------------------
class Elipse {
private:
    Punto centro; //Composicion
    double semiejeMayor, semiejeMenor;
public:
    Elipse(double x = 0.0, double y = 0.0, double a = 1.0, double b = 1.0);
    double getSemiejeMayor() const;
    double getSemiejeMenor() const;

    void setSemiejeMayor(double a);
    void setSemiejeMenor(double b);
    void setCentro(double x, double y);
};

//--------------------------------  Rectangulo ----------------------------
class Rectangulo {
private:
    Punto verticeInfIzq; //Composicion
    double ancho, alto;
public:
    Rectangulo(double x = 0.0, double y = 0.0, double a = 1.0, double h = 1.0);
    double getAncho() const;
    double getAlto() const;

    void setAncho(double a);
    void setAlto(double h);
    void setPosicion(double x, double y);
};

//--------------------------------ProcesadorFigura con plantilla de especializacion ------------------------
template<typename T>
class ProcesadorFigura {
public:
    static double calcularArea(const T&) {
        static_assert(std::is_same_v<T, void>, "No se acepta este tipo. Tipos soportados: Punto,Circulo, Elipse, Rectangulo"); // falla siempre, es para escapar si no se especializa, si se le ingresa algo que no sean estas 4 figs
        return 0;
    }
};// static no necesita instancia. acepta cualq figura por ref constante
template<> double ProcesadorFigura<Punto>::calcularArea(const Punto&); //ziempre va a dar 0
template<> double ProcesadorFigura<Circulo>::calcularArea(const Circulo&);
template<> double ProcesadorFigura<Elipse>::calcularArea(const Elipse&);
template<> double ProcesadorFigura<Rectangulo>::calcularArea(const Rectangulo&);

#endif