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
    VariableDifusa var("Hr", etiquetas_5_niveles.size(), 0, 200, false, etiquetas_5_niveles);
    configurarHeartRate(&var);
    return var;
}

VariableDifusa GeneradorVariables::crearOxygenSaturation() {
    VariableDifusa var("O2", etiquetas_3_niveles.size(), 0, 100, false, etiquetas_3_niveles);
    configurarOxygenSaturation(&var);
    return var;
}

VariableDifusa GeneradorVariables::crearBodyTemp() {
    VariableDifusa var("Bt", etiquetas_5_niveles.size(), 0, 45, false, etiquetas_5_niveles);
    configurarBodyTemp(&var);
    return var;
}

VariableDifusa GeneradorVariables::crearSystolicBP() {
    VariableDifusa var("SysBP", etiquetas_5_niveles.size(), 0, 220, false, etiquetas_5_niveles);
    configurarSystolicBP(&var);
    return var;
}

VariableDifusa GeneradorVariables::crearDiastolicBP() {
    VariableDifusa var("DiaBP", etiquetas_5_niveles.size(), 0, 160, false, etiquetas_5_niveles);
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

    var->getConjunto(0)->setPrioridad(2); // rojo_izq
    var->getConjunto(1)->setPrioridad(1); // amarillo_izq
    var->getConjunto(2)->setPrioridad(0); // verde
    var->getConjunto(3)->setPrioridad(1); // amarillo_der
    var->getConjunto(4)->setPrioridad(2); // rojo_der

    // heartrate rojo_izq: <40, amarillo_izq <60, verde 60-80, amarillo_der >110, rojo_der > 130}
    var->getConjunto(0)->setNucleoSupP(40);

    var->getConjunto(1)->setLimiteInferiorP(40);
    var->getConjunto(1)->setNucleoInfP(50);
    var->getConjunto(1)->setNucleoSupP(50);
    var->getConjunto(1)->setLimiteSuperiorP(60);

    var->getConjunto(2)->setNucleoInfP(60);
    var->getConjunto(2)->setNucleoSupP(80);
    var->getConjunto(2)->setLimiteSuperiorP(110);

    var->getConjunto(3)->setLimiteInferiorP(80);
    var->getConjunto(3)->setNucleoInfP(110);
    var->getConjunto(3)->setNucleoSupP(110);
    var->getConjunto(3)->setLimiteSuperiorP(130);

    var->getConjunto(4)->setLimiteInferiorP(110);
    var->getConjunto(4)->setNucleoInfP(130);
    var->getConjunto(4)->setNucleoSupP(150);
    var->getConjunto(4)->setLimiteSuperiorP(150);
}

void GeneradorVariables::configurarOxygenSaturation(VariableDifusa* var) {

    var->getConjunto(0)->setPrioridad(2); // rojo
    var->getConjunto(1)->setPrioridad(1); // amarillo
    var->getConjunto(2)->setPrioridad(0); // verde

    // Oxygen saturation rojo <70, amarillo 71 - 89, verde >90
    var->getConjunto(0)->setLimiteSuperiorP(80);
    var->getConjunto(0)->setNucleoSupP(70);
    
    var->getConjunto(1)->setLimiteSuperiorP(90);
    var->getConjunto(1)->setNucleoSupP(80);
    var->getConjunto(1)->setNucleoInfP(80);
    var->getConjunto(1)->setLimiteInferiorP(70);

    var->getConjunto(2)->setLimiteSuperiorP(100);
    var->getConjunto(2)->setNucleoSupP(100);
    var->getConjunto(2)->setNucleoInfP(90);
    var->getConjunto(2)->setLimiteInferiorP(80);
}

void GeneradorVariables::configurarBodyTemp(VariableDifusa* var) {

    var->getConjunto(0)->setPrioridad(2); 
    var->getConjunto(1)->setPrioridad(1); 
    var->getConjunto(2)->setPrioridad(0); 
    var->getConjunto(3)->setPrioridad(1); 
    var->getConjunto(4)->setPrioridad(2);

    // Body temperature rojo_izq <35.5, amarillo_izq <36, verde 36.5-37.5, amarillo_der >38, rojo_der >40
    var->getConjunto(0)->setLimiteSuperiorP(36);
    var->getConjunto(0)->setNucleoSupP(35.5);

    var->getConjunto(1)->setLimiteSuperiorP(36.5);
    var->getConjunto(1)->setNucleoSupP(36);
    var->getConjunto(1)->setNucleoInfP(36);
    var->getConjunto(1)->setLimiteInferiorP(35.5);

    var->getConjunto(2)->setLimiteSuperiorP(38);
    var->getConjunto(2)->setNucleoSupP(37.5);
    var->getConjunto(2)->setNucleoInfP(36.5);
    var->getConjunto(2)->setLimiteInferiorP(36);

    var->getConjunto(3)->setLimiteSuperiorP(40);
    var->getConjunto(3)->setNucleoSupP(38);
    var->getConjunto(3)->setNucleoInfP(38);
    var->getConjunto(3)->setLimiteInferiorP(37.5);

    var->getConjunto(4)->setNucleoInfP(40);
    var->getConjunto(4)->setLimiteInferiorP(38);
}

void GeneradorVariables::configurarSystolicBP(VariableDifusa* var) {

    var->getConjunto(0)->setPrioridad(2); 
    var->getConjunto(1)->setPrioridad(1); 
    var->getConjunto(2)->setPrioridad(0); 
    var->getConjunto(3)->setPrioridad(1); 
    var->getConjunto(4)->setPrioridad(2);

    // Systolic blood pressure: rojo_izq <90, amarillo_izq <110, verde 120-140 amarillo_der >160, rojo_der >200
    var->getConjunto(0)->setLimiteSuperiorP(110);
    var->getConjunto(0)->setNucleoSupP(90);

    var->getConjunto(1)->setLimiteSuperiorP(120);
    var->getConjunto(1)->setNucleoSupP(110);
    var->getConjunto(1)->setNucleoInfP(110);
    var->getConjunto(1)->setLimiteInferiorP(90);

    var->getConjunto(2)->setLimiteSuperiorP(160);
    var->getConjunto(2)->setNucleoSupP(140);
    var->getConjunto(2)->setNucleoInfP(120);
    var->getConjunto(2)->setLimiteInferiorP(110);

    var->getConjunto(3)->setLimiteSuperiorP(200);
    var->getConjunto(3)->setNucleoInfP(160);
    var->getConjunto(3)->setNucleoSupP(160);
    var->getConjunto(3)->setLimiteInferiorP(140);

    var->getConjunto(4)->setNucleoInfP(200);
    var->getConjunto(4)->setLimiteInferiorP(160);
}

void GeneradorVariables::configurarDiastolicBP(VariableDifusa* var) {

    var->getConjunto(0)->setPrioridad(2); 
    var->getConjunto(1)->setPrioridad(1); 
    var->getConjunto(2)->setPrioridad(0); 
    var->getConjunto(3)->setPrioridad(1); 
    var->getConjunto(4)->setPrioridad(2);

    // Diastolic blood pressure: rojo_izq <60, amarillo_izq <80, verde 80-100 amarillo_der >110, rojo_der >120
    var->getConjunto(0)->setLimiteSuperiorP(70);
    var->getConjunto(0)->setNucleoSupP(60);

    var->getConjunto(1)->setLimiteSuperiorP(80);
    var->getConjunto(1)->setNucleoSupP(70);
    var->getConjunto(1)->setNucleoInfP(70);
    var->getConjunto(1)->setLimiteInferiorP(60);

    var->getConjunto(2)->setLimiteSuperiorP(110);
    var->getConjunto(2)->setNucleoSupP(100);
    var->getConjunto(2)->setNucleoInfP(80);
    var->getConjunto(2)->setLimiteInferiorP(70);

    var->getConjunto(3)->setLimiteSuperiorP(120);
    var->getConjunto(3)->setNucleoInfP(110);
    var->getConjunto(3)->setNucleoSupP(110);
    var->getConjunto(3)->setLimiteInferiorP(100);

    var->getConjunto(4)->setNucleoInfP(120);
    var->getConjunto(4)->setLimiteInferiorP(110);
}