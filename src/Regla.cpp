#include "Regla.h"
#include <iostream>
#include <limits> 

//  Constructores 
Regla::Regla() {
    etiquetaConsecuente = "";
    idConsecuente = 0;
    fuerzaDisparo = 0.0;
    operador = TipoOperador::AND; // Por defecto sigue siendo AND
}

Regla::Regla(const std::string& _etiquetaConsecuente, int _idConsecuente) {
    etiquetaConsecuente = _etiquetaConsecuente;
    idConsecuente = _idConsecuente;
    fuerzaDisparo = 0.0;
    operador = TipoOperador::AND; // Por defecto
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
        return 0.0; 
    }

    double resultado = 0.0;

    if (operador == TipoOperador::AND) {
        // Lógica AND (Mínimo)
        resultado = 1.0; 
        for (auto& premisa : antecedentes) {
            double val = premisa.evaluar();
            if (val < resultado) {
                resultado = val; // Nos quedamos con el menor
            }
        }
    } 
    else {
        // Lógica OR (Máximo)
        resultado = 0.0; 
        for (auto& premisa : antecedentes) {
            double val = premisa.evaluar();
            if (val > resultado) {
                resultado = val;
            }
        }
    }

    fuerzaDisparo = resultado;
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
    std::string opStr = (operador == TipoOperador::AND) ? " AND " : " OR ";
    std::string texto = "IF ";
    
    for (size_t i = 0; i < antecedentes.size(); ++i) {
        texto += antecedentes[i].toString();
        if (i < antecedentes.size() - 1) {
            texto += opStr;
        }
    }
    texto += " THEN Output IS " + etiquetaConsecuente;
    return texto;
}



//Nuevo
void Regla::setOperador(TipoOperador _op) {
    operador = _op;
}