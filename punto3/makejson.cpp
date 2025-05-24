#include "MAKEJSON.hpp"
#include <sstream>
#include <stdexcept>
#include <type_traits>
#include <fstream>
#include <iostream>

// --------------------------implementacion JsonDataManager--------------------------


template<typename T>
void JsonDataManager::addData(const std::vector<T>& data) {
    if constexpr (std::is_same_v<T, double>) {
        vecDoubles = data;
    } 
    else if constexpr (std::is_same_v<T, std::string>) {
        vecStrings = data;
    }
    else if constexpr (std::is_same_v<T, std::vector<int>>) {
        vecIntMatrices = data;
    }
    else {
        static_assert(sizeof(T) == 0, "Tipo de dato no soportado. Usar double, string o vector<int>"); //algo q siempre falle si no le pasaron ninguno de esos tipos
    }
}

//instanciaciones de los tipos permitidos
template void JsonDataManager::addData<double>(const std::vector<double>&);
template void JsonDataManager::addData<std::string>(const std::vector<std::string>&);
template void JsonDataManager::addData<std::vector<int>>(const std::vector<std::vector<int>>&);

const std::vector<double>& JsonDataManager::getDoubles() const {
    return vecDoubles;
}

const std::vector<std::string>& JsonDataManager::getStrings() const {
    return vecStrings;
}

const std::vector<std::vector<int>>& JsonDataManager::getIntMatrices() const {
    return vecIntMatrices;
}

// --------------------------implementacion JsonComposer--------------------------


void JsonComposer::addLabeledData(const std::string& label, const JsonDataManager& manager) {
    labeledData[label] = manager;
}
// esto es como serializar el json, pero serializas no al binario
std::string JsonComposer::buildJson() const {
    std::ostringstream json;
    json << "{\n";

    bool firstElement = true; //es el primer elemento? 

    // funcion aux para agregar comas
    auto addCommaIfNeeded = [&]() { // captura todos las refs
        if (!firstElement) json << ",\n"; // dice que va una coma dps del ult elemento y un salto, salvo q seas el primero, ahi va nada
        firstElement = false;
    };

    // serializar vec_doubles si existe
    if (labeledData.count("vec_doubles")) {
        addCommaIfNeeded();
        json << "  \"vec_doubles\": [";
        const auto& doubles = labeledData.at("vec_doubles").getDoubles();
        for (size_t i = 0; i < doubles.size(); ++i) {
            if (i != 0) json << ", ";
            json << doubles[i];
        }
        json << "]";
    }

    // serializar palabras si existe
    if (labeledData.count("palabras")) {
        addCommaIfNeeded();
        json << "  \"palabras\": [";
        const auto& strings = labeledData.at("palabras").getStrings();
        for (size_t i = 0; i < strings.size(); ++i) {
            if (i != 0) json << ", ";
            json << "\"" << strings[i] << "\"";
        }
        json << "]";
    }

    // serializar listas si existe
    if (labeledData.count("listas")) {
        addCommaIfNeeded();
        json << "  \"listas\": [\n";
        const auto& matrices = labeledData.at("listas").getIntMatrices();
        for (size_t i = 0; i < matrices.size(); ++i) {
            if (i != 0) json << ",\n";
            json << "    [";
            const auto& inner = matrices[i];
            for (size_t j = 0; j < inner.size(); ++j) {
                if (j != 0) json << ", ";
                json << inner[j];
            }
            json << "]";
        }
        json << "\n  ]";
    }

    json << "\n}";
    return json.str();
}

void JsonComposer::saveJsonAsFile(const std::string& filename) const {
    std::ofstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("no se pudo abrir el archivo para escribir el JSON");
    }

    file << buildJson();
    std::cout<<"JSON creado exitosamente. Nombre: SalidaPunto3"<<std::endl;
    file.close();
}