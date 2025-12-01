#include "GeneradorVariables.h"

// Constructor: Define las etiquetas una sola vez
GeneradorVariables::GeneradorVariables() {
    etiquetas_5_niveles = {
        "rojo_izq", "amarillo_izq", "verde", "amarillo_der", "rojo_der"
    };

    etiquetas_3_niveles = {
        "rojo", "amarillo", "verde"
    };
}


// MÉTODOS PÚBLICOS DE CREACIÓN
VariableDifusa GeneradorVariables::crearHeartRate() {
    VariableDifusa var("Hr", etiquetas_5_niveles.size(), 30, 190, false, etiquetas_5_niveles);
    configurarHeartRate(&var);
    return var;
}

VariableDifusa GeneradorVariables::crearOxygenSaturation() {
    VariableDifusa var("O2", etiquetas_3_niveles.size(), 50, 100, false, etiquetas_3_niveles);
    configurarOxygenSaturation(&var);
    return var;
}

VariableDifusa GeneradorVariables::crearBodyTemp() {
    VariableDifusa var("Bt", etiquetas_5_niveles.size(), 34, 42, false, etiquetas_5_niveles);
    configurarBodyTemp(&var);
    return var;
}

VariableDifusa GeneradorVariables::crearSystolicBP() {
    VariableDifusa var("SysBP", etiquetas_5_niveles.size(), 50, 200, false, etiquetas_5_niveles);
    configurarSystolicBP(&var);
    return var;
}

VariableDifusa GeneradorVariables::crearDiastolicBP() {
    VariableDifusa var("DiaBP", etiquetas_5_niveles.size(), 30, 130, false, etiquetas_5_niveles);
    configurarDiastolicBP(&var);
    return var;
}

VariableDifusa GeneradorVariables::crearColorOutput() {
    // La salida no requiere ajustes manuales de rangos por ahora
    VariableDifusa var("Output", etiquetas_3_niveles.size(), 0, 100, false, etiquetas_3_niveles);

    var.getConjunto(0)->setPrioridad(2); // Rojo
    var.getConjunto(1)->setPrioridad(1); // Amarillo
    var.getConjunto(2)->setPrioridad(0); // Verde

    return var;
}


// logica de triage


void GeneradorVariables::configurarHeartRate(VariableDifusa* var) {
    var->getConjunto(0)->setPrioridad(2); 
    var->getConjunto(1)->setPrioridad(1); 
    var->getConjunto(2)->setPrioridad(0); 
    var->getConjunto(3)->setPrioridad(1); 
    var->getConjunto(4)->setPrioridad(2);

    // 0: Rojo Izq (< 40)
    var->getConjunto(0)->setParametros({0, 0, 39, 41});

    // 1: Amarillo Izq (40 - 60)
    var->getConjunto(1)->setParametros({39, 41, 59, 61});

    // 2: Verde (60 - 80) 
    var->getConjunto(2)->setParametros({59, 61, 79, 81});

    // 3: Amarillo Der (80 - 130)
    var->getConjunto(3)->setParametros({79, 81, 129, 131});

    // 4: Rojo Der (> 130)
    var->getConjunto(4)->setParametros({129, 131, 200, 200});
}

void GeneradorVariables::configurarOxygenSaturation(VariableDifusa* var) {
    var->getConjunto(0)->setPrioridad(2); 
    var->getConjunto(1)->setPrioridad(1); 
    var->getConjunto(2)->setPrioridad(0); 

    // 0: Rojo (< 70)
    var->getConjunto(0)->setParametros({0, 0, 69, 71});

    // 1: Amarillo (70 - 89)
    var->getConjunto(1)->setParametros({69, 71, 89, 91});

    // 2: Verde (> 90)
    var->getConjunto(2)->setParametros({89, 91, 100, 100});
}

void GeneradorVariables::configurarBodyTemp(VariableDifusa* var) {
    var->getConjunto(0)->setPrioridad(2); 
    var->getConjunto(1)->setPrioridad(1); 
    var->getConjunto(2)->setPrioridad(0); 
    var->getConjunto(3)->setPrioridad(1); 
    var->getConjunto(4)->setPrioridad(2);

    // 0: Rojo Izq (< 35.5)
    var->getConjunto(0)->setParametros({30, 30, 35.4, 35.6});

    // 1: Amarillo Izq (35.5 - 36.5)
    var->getConjunto(1)->setParametros({35.4, 35.6, 36.4, 36.6});

    // 2: Verde (36.5 - 37.5) ESTRICTO
    var->getConjunto(2)->setParametros({36.4, 36.6, 37.4, 37.6});

    // 3: Amarillo Der (37.5 - 40)
    var->getConjunto(3)->setParametros({37.4, 37.6, 39.9, 40.1});

    // 4: Rojo Der (> 40)
    var->getConjunto(4)->setParametros({39.9, 40.1, 45, 45});
}

void GeneradorVariables::configurarSystolicBP(VariableDifusa* var) {
    var->getConjunto(0)->setPrioridad(2); 
    var->getConjunto(1)->setPrioridad(1); 
    var->getConjunto(2)->setPrioridad(0); 
    var->getConjunto(3)->setPrioridad(1); 
    var->getConjunto(4)->setPrioridad(2);

    // 0: Rojo Izq (< 90)
    var->getConjunto(0)->setParametros({0, 0, 89, 91});

    // 1: Amarillo Izq (90 - 100)
    var->getConjunto(1)->setParametros({89, 91, 99, 101});

    // 2: Verde (100 - 140)
    var->getConjunto(2)->setParametros({99, 101, 139, 141});

    // 3: Amarillo Der (140 - 200) 
    // Completamos el hueco hasta 200 donde empieza el rojo estricto
    var->getConjunto(3)->setParametros({139, 141, 199, 201});

    // 4: Rojo Der (> 200)
    var->getConjunto(4)->setParametros({199, 201, 300, 300});
}

void GeneradorVariables::configurarDiastolicBP(VariableDifusa* var) {
    var->getConjunto(0)->setPrioridad(2); 
    var->getConjunto(1)->setPrioridad(1); 
    var->getConjunto(2)->setPrioridad(0); 
    var->getConjunto(3)->setPrioridad(1); 
    var->getConjunto(4)->setPrioridad(2);

    // Estrategia: Verde es 60-100.
    // Rojo Izq < 50 (Severo)
    // Amarillo Izq 50-60
    
    // 0: Rojo Izq (< 50) 
    var->getConjunto(0)->setParametros({0, 0, 49, 51});

    // 1: Amarillo Izq (50 - 60)
    var->getConjunto(1)->setParametros({49, 51, 59, 61});

    // 2: Verde (60 - 100)
    var->getConjunto(2)->setParametros({59, 61, 99, 101});

    // 3: Amarillo Der (100 - 120)
    var->getConjunto(3)->setParametros({99, 101, 119, 121});

    // 4: Rojo Der (> 120)
    var->getConjunto(4)->setParametros({119, 121, 200, 200});
}