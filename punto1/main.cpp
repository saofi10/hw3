#include "MEDICIONES.hpp" 
//pruebas que pide en b
int main() {
    // datos de prueba
    Posicion pos(-34.6f, -58.4f, 950.0f, 5.3f);
    Presion pres(101.3f, 5.8f, 6.1f);
    SaveFlightData datosOriginales(pos, pres);
    datosOriginales.imprimir();//imprimo aca porque estan nuevos

    // serializar
    std::ofstream out("vuelo.bin", std::ios::binary);
    if (out) {
        datosOriginales.serializar(out);
        out.close();
    }

    //deserializar
    SaveFlightData datosLeidos; //inicializa todos los datos en 0

    std::ifstream in("vuelo.bin", std::ios::binary);
    if (in) {
        datosLeidos.deserializar(in);
        in.close();
    }

    // verificar comparando 1 vs 1
    datosLeidos.imprimir();
    datosOriginales.imprimir(); // imprimo de nuevo aca para mostrar que no se tocaron los del comienzo y que son iguales a los leidos
    return 0;
}

