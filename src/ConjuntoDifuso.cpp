#include "ConjuntoDifuso.h"

ConjuntoDifuso::ConjuntoDifuso() : id(0), etiqueta(""), forma(-1) {}

ConjuntoDifuso::ConjuntoDifuso(const std::string& _etiqueta, int _forma, int _id) : etiqueta(_etiqueta), forma(_forma), id(_id) {}

ConjuntoDifuso::ConjuntoDifuso(const std::vector<double>& _parametros, const std::string& _etiqueta, int _forma, int _id)
    : parametros(_parametros), etiqueta(_etiqueta), forma(_forma), id(_id) {}

ConjuntoDifuso::~ConjuntoDifuso() {}

void ConjuntoDifuso::setEtiqueta(const std::string& _etiqueta) {
    this->etiqueta = _etiqueta;
}

std::string ConjuntoDifuso::getEtiqueta() const {
    return etiqueta;
}

void ConjuntoDifuso::setForma(const int& _forma) {
    this->forma = _forma;
}

int ConjuntoDifuso::getForma() const {
    return forma;
}

void ConjuntoDifuso::setID(int ID) {
    this->id = ID;
}

int ConjuntoDifuso::getID() const {
    return id;
}

void ConjuntoDifuso::setParametros(const std::vector<double>& _parametros) {
    this->parametros = _parametros;
}

//Esto se agrega si en dado caso, no se pasa la variable
//como std::vector, sino como {} denominada temporales
void ConjuntoDifuso::setParametros(const std::vector<double>&& _parametros) {
    this->parametros = std::move(_parametros);
}
std::vector<double> ConjuntoDifuso::getParametros() const {
    return parametros;
}

//metodos de prioridad
void ConjuntoDifuso::setPrioridad(int _prioridad) {
    this->prioridad = _prioridad;
}

int ConjuntoDifuso::getPrioridad() const {
    return this->prioridad;
}
