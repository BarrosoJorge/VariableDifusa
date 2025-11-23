#pragma once

#include <vector>
#include <string>
#include <algorithm> 
#include "Premisa.h"

class Regla {
protected:
    std::vector<Premisa> antecedentes; // Lista de condiciones (IF...)
    std::string etiquetaConsecuente;   // La salida (THEN...)
    int idConsecuente;                 // ID numérico de la salida (opcional, para defuzzificar)
    double fuerzaDisparo;              // Resultado de la última evaluación

    //  Métodos protegidos de gestión interna 
    
    // Agrega una premisa ya construida al vector
    void agregarAntecedente(const Premisa& _premisa);
    
    // Configura la consecuencia de la regla
    void setConsecuente(const std::string& _etiqueta, int _id);

    // Calcula el MINIMO de todas las premisas (Lógica AND)
    double calcularActivacion();

public:
    // Constructores 
    Regla();
    Regla(const std::string& _etiquetaConsecuente, int _idConsecuente);

    //  Métodos Públicos Seguros  
    
    // Crea y agrega una premisa en un solo paso
    // Ejemplo: agregarPremisaP(&hue, "red", AFIRMACION);
    void agregarPremisaP(VariableDifusa* _var, const std::string& _etiqueta, TipoPremisa _tipo);

    void setConsecuenteP(const std::string& _etiqueta, int _id = 0);

    // Ejecuta la regla y devuelve la fuerza de disparo (0.0 a 1.0)
    double evaluarP();

    // Getters 
    double getFuerzaDisparo() const;
    std::string getEtiquetaConsecuente() const;

    // Genera el texto legible de la regla
    // Ej: "IF (Hue IS red) AND (Sat IS NOT low) THEN Output IS Red"
    std::string toString() const;
};