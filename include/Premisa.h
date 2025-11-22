#pragma once
#include <string>
#include <iostream>
#include "VariableDifusa.h" 

// Enum para definir si la premisa busca que sea VERDAD o FALSO
enum class TipoPremisa {
    AFIRMACION = 1, // (Es)
    NEGACION = 0    // (No es)
};

class Premisa {
private:
    VariableDifusa* variableRef; // Puntero a la variable 
    std::string etiqueta;        // La etiqueta que buscamos (ej: "red_i")
    TipoPremisa tipo;            // AFIRMACION o NEGACION

protected:
    // Métodos de gestión interna 
    void setVariable(VariableDifusa* _var);
    VariableDifusa* getVariable() const;

    void setEtiqueta(const std::string& _etiqueta);
    std::string getEtiqueta() const;

    void setTipo(TipoPremisa _tipo);
    TipoPremisa getTipo() const;

public:
    //  Constructores 
    Premisa();
    Premisa(VariableDifusa* _var, const std::string& _etiqueta, TipoPremisa _tipo);

    //  Métodos Públicos   
    void setVariableP(VariableDifusa* _var);
    void setEtiquetaP(const std::string& _etiqueta);
    void setTipoP(TipoPremisa _tipo);

    // Lógica Principal 
    // Evalúa la verdad de la premisa en el instante actual
    double evaluar(); 

    // para ver la premisa como texto
    std::string toString() const;
};