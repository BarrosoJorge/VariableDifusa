#pragma once
#include "VariableDifusa.h"
#include <vector>
#include <string>

class GeneradorVariables {
private:
    // Vectores de etiquetas reutilizables
    std::vector<std::string> etiquetas_5_niveles;
    std::vector<std::string> etiquetas_3_niveles;

    // Métodos auxiliares internos para aplicar la configuración de rangos
    void configurarHeartRate(VariableDifusa* var);
    void configurarOxygenSaturation(VariableDifusa* var);
    void configurarBodyTemp(VariableDifusa* var);
    void configurarSystolicBP(VariableDifusa* var);
    void configurarDiastolicBP(VariableDifusa* var);

public:
    // Constructor: Inicializa las etiquetas
    GeneradorVariables();

    // Métodos de Fábrica: Devuelven la variable lista para usar
    VariableDifusa crearHeartRate();
    VariableDifusa crearOxygenSaturation();
    VariableDifusa crearBodyTemp();
    VariableDifusa crearSystolicBP();
    VariableDifusa crearDiastolicBP();
    
    // Variable de salida (Color)
    VariableDifusa crearColorOutput();
};