#include "MAKEJSON.hpp"
#include <iostream>

int main() {
    // cargar datos
    JsonDataManager dataManager;
    
    dataManager.addData(std::vector<double>{1.2, 25.17, 25.052025});
    dataManager.addData(std::vector<std::string>{"Hola", "Mundo"});
    dataManager.addData(std::vector<std::vector<int>>{{1, 2}, {3, 4}});

    // Construir JSON
    JsonComposer composer;
    composer.addLabeledData("vec_doubles", dataManager);
    composer.addLabeledData("palabras", dataManager);
    composer.addLabeledData("listas", dataManager);
    

    // Mostrar resultado
    std::cout << composer.buildJson() << std::endl; //retorna un string
    composer.saveJsonAsFile("salidaPunto3.json"); //guardarlo como archivo
    return 0;
}