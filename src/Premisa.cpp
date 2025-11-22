#include "Premisa.h"
#include <stdexcept>

//  Constructores 
Premisa::Premisa() {
    variableRef = nullptr;
    etiqueta = "";
    tipo = TipoPremisa::AFIRMACION;
}

Premisa::Premisa(VariableDifusa* _var, const std::string& _etiqueta, TipoPremisa _tipo) {
    setVariable(_var);
    setEtiqueta(_etiqueta);
    setTipo(_tipo);
}

// Métodos Protegidos (Implementación y Validaciones) 

void Premisa::setVariable(VariableDifusa* _var) {
    if (_var == nullptr) {
        throw std::invalid_argument("Error: La referencia a la VariableDifusa no puede ser nula.");
    }
    variableRef = _var;
}

VariableDifusa* Premisa::getVariable() const {
    return variableRef;
}

void Premisa::setEtiqueta(const std::string& _etiqueta) {
    if (_etiqueta.empty()) {
        throw std::invalid_argument("Error: La etiqueta de la premisa no puede estar vacía.");
    }
    // Opcional: Podríamos validar aquí si la etiqueta existe en la variable,
    // pero eso requeriría que la variable ya esté totalmente configurada.
    etiqueta = _etiqueta;
}

std::string Premisa::getEtiqueta() const {
    return etiqueta;
}

void Premisa::setTipo(TipoPremisa _tipo) {
    tipo = _tipo;
}

TipoPremisa Premisa::getTipo() const {
    return tipo;
}

//  Métodos Públicos  

void Premisa::setVariableP(VariableDifusa* _var) {
    setVariable(_var);
}

void Premisa::setEtiquetaP(const std::string& _etiqueta) {
    setEtiqueta(_etiqueta);
}

void Premisa::setTipoP(TipoPremisa _tipo) {
    setTipo(_tipo);
}

//  Lógica Principal 

double Premisa::evaluar() {
    if (!variableRef) return 0.0;

    // 1. Obtenemos el conjunto difuso asociado a la etiqueta para saber su ID
    ConjuntoDifuso* conjunto = variableRef->getConjunto(etiqueta);
    
    // 2. Obtenemos el ID del conjunto (recordando que IDs empiezan en 1)
    int idConjunto = conjunto->getID(); 

    // 3. Obtenemos el vector actual de membresías calculadas
    std::vector<double> membresias = variableRef->getMembresias();

    // 4. Extraemos el valor de verdad (mu)
    // El vector es índice 0, pero los IDs son índice 1, así que restamos 1.
    double valorVerdad = 0.0;
    if (idConjunto - 1 < membresias.size()) {
        valorVerdad = membresias[idConjunto - 1];
    }

    // 5. Aplicamos el modificador (Afirmación o Negación)
    if (tipo == TipoPremisa::NEGACION) {
        return 1.0 - valorVerdad; // Complemento
    }
    
    return valorVerdad;
}

std::string Premisa::toString() const {
    std::string nombreVar = (variableRef) ? variableRef->getVariable() : "NULL";
    std::string verbo = (tipo == TipoPremisa::AFIRMACION) ? " IS " : " IS NOT ";
    return "(" + nombreVar + verbo + etiqueta + ")";
}