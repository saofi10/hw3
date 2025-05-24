#ifndef JSON_BUILDER_HPP
#define JSON_BUILDER_HPP

#include <vector>
#include <string>
#include <map>
#include <variant>
//solo almacena los vecs, mats
class JsonDataManager {
public:
    template<typename T>
    void addData(const std::vector<T>& data);

    // getters
    const std::vector<double>& getDoubles() const;
    const std::vector<std::string>& getStrings() const;
    const std::vector<std::vector<int>>& getIntMatrices() const;

private:
    std::vector<double> vecDoubles;
    std::vector<std::string> vecStrings;
    std::vector<std::vector<int>> vecIntMatrices;
};
//construye json 
class JsonComposer {
public:
    void addLabeledData(const std::string& label, const JsonDataManager& manager);
    std::string buildJson() const; //este es el metodo de serializacion
    void saveJsonAsFile(const std::string& filename) const;

private:
    std::map<std::string, JsonDataManager> labeledData;
};

#endif 