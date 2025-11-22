#pragma once
#include <vector>
#include <string>
#include <iostream>
#include "Regla.h"

class SistemaDifuso {
protected:
    std::vector<Regla> baseDeReglas; // El vector que almacena todas tus reglas

public:
    SistemaDifuso();

    //  Gestión de Reglas 
    void agregarReglaP(const Regla& _regla);
    void limpiarReglas();

    //  Motor de Inferencia 
    
    // Evalúa todas las reglas y devuelve la etiqueta de la regla con mayor fuerza de disparo (Max-Membership)
    // equivalente de buscar el maxMu
    std::string resolver();

    // Método opcional para depuración: imprime qué reglas se activaron y con cuánto
    void mostrarReglasActivas() const;
};