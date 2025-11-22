#include "Regla.h"
#include <iostream>
#include <limits> 

//  Constructores 
Regla::Regla() {
    etiquetaConsecuente = "";
    idConsecuente = 0;
    fuerzaDisparo = 0.0;
}

Regla::Regla(const std::string& _etiquetaConsecuente, int _idConsecuente) {
    etiquetaConsecuente = _etiquetaConsecuente;
    idConsecuente = _idConsecuente;
    fuerzaDisparo = 0.0;
}

//  Métodos Protegidos 

void Regla::agregarAntecedente(const Premisa& _premisa) {
    antecedentes.push_back(_premisa);
}

void Regla::setConsecuente(const std::string& _etiqueta, int _id) {
    etiquetaConsecuente = _etiqueta;
    idConsecuente = _id;
}

double Regla::calcularActivacion() {
    if (antecedentes.empty()) {
        return 0.0; // Si no hay condiciones, la regla no hace nada
    }

    // Iniciamos con el valor máximo posible para encontrar el mínimo (Operador AND)
    double minW = 1.0; 

    for (auto& premisa : antecedentes) {
        double valorVerdad = premisa.evaluar();
        
        // Operador AND difuso = Min(a, b)
        if (valorVerdad < minW) {
            minW = valorVerdad;
        }
    }

    fuerzaDisparo = minW;
    return fuerzaDisparo;
}

//  Métodos Públicos 

void Regla::agregarPremisaP(VariableDifusa* _var, const std::string& _etiqueta, TipoPremisa _tipo) {
    // Creamos la premisa temporalmente y la pasamos al vector protegido
    // Validamos que la variable no sea nula antes de crear
    if (_var != nullptr) {
        Premisa nueva(_var, _etiqueta, _tipo);
        agregarAntecedente(nueva);
    } else {
        std::cerr << "Error: Intentando agregar premisa con variable nula." << std::endl;
    }
}

void Regla::setConsecuenteP(const std::string& _etiqueta, int _id) {
    setConsecuente(_etiqueta, _id);
}

double Regla::evaluarP() {
    return calcularActivacion();
}

double Regla::getFuerzaDisparo() const {
    return fuerzaDisparo;
}

std::string Regla::getEtiquetaConsecuente() const {
    return etiquetaConsecuente;
}

std::string Regla::toString() const {
    std::string texto = "IF ";
    
    for (size_t i = 0; i < antecedentes.size(); ++i) {
        texto += antecedentes[i].toString();
        
        // Agregamos el " AND " si no es el último elemento
        if (i < antecedentes.size() - 1) {
            texto += " AND ";
        }
    }
    
    texto += " THEN Output IS " + etiquetaConsecuente;
    return texto;
}