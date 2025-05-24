#include "Figuras.hpp"
#include <iostream>
#include <iomanip>
#include <vector>
#include <typeinfo>

// funcion para imprimir resultados con formato
void imprimirResultado(const std::string& figura, double area, const std::string& detalles = "") {
    std::cout << std::setw(12) << std::left << figura 
              << " | Area: " << std::setw(10) << std::fixed << std::setprecision(4) << area
              << " | " << detalles << "\n";
}

// plantilla para probar el calculo de area. Si salae bien imprime sino muestra claro el error
template<typename T>
void probarArea(const T& figura, const std::string& nombreFigura) {
    try {
        double area = ProcesadorFigura<T>::calcularArea(figura);
        imprimirResultado(nombreFigura, area, "Tipo: " + std::string(typeid(T).name())); //typeid va a incluir un nro delante del nombre del tipo, por eso en la impresion sale 5punto, pq punto tiene long 5 xej
    } catch (const std::exception& e) {
        std::cerr << " Error con " << nombreFigura << ": " << e.what() << "\n";
    }
}

// --------------------------------Test de casos borde--------------------------------
void testCasosBorde() {
    std::cout << "\nTesting Casos Borde:\n";
    //radio muy chico pero ok
    Circulo circMicro(0, 0, 1e-10);
    probarArea(circMicro, "Circulo micro");

    //rectangulo muy chico pero ok
    Rectangulo rectMin(0, 0, 1e-10, 1e-10);
    probarArea(rectMin, "Rectangulo min");
}

// --------------------------------Test de manejo de errores--------------------------------
void testErrores() {
    std::cout << "\nTesting Manejo de Errores:\n";
    
    try {
        Circulo circInvalido(0, 0, -2.0);
        probarArea(circInvalido, "Circulo no permitido");
    } catch (const std::exception& e) {
        std::cerr << " ok! " << e.what() << "\n";
    }

    try {
        Elipse elipsInvalida(0, 0, -3.0, 4.0);
        probarArea(elipsInvalida, "Elipse no permitida");
    } catch (const std::exception& e) {
        std::cerr << " ok! " << e.what() << "\n";
    }
}

int main() {
    std::cout << "===================== TESTING FIGURAS PUNTO 2 =====================\n";

    // Casos básicos
    std::cout << "\n Casos basicos:\n";
    probarArea(Punto(0,6), "Punto random");
    probarArea(Circulo(0, 0, 5.0), "Circulo r=20");
    probarArea(Elipse(0, 0, 3.0, 4.0), "Elipse 3x4");
    probarArea(Rectangulo(0, 0, 4.0, 5.0), "Rectangulo 4x5");

    //otros tests 
    testCasosBorde();
    testErrores();

    std::cout << "\n======================== PRUEBAS COMPLETADAS ========================\n";
    return 0;
}
