
#include "VariableDifusa.h"
#include "SistemaDifuso.h" 
#include "Regla.h"



int main() {
    // 1. Configurar Variables

    //heartrate = rojo_izq, amarillo_izq, verde, amarillo_der, rojo_der
    //Oxygen satruarion = rojo, amarillo, verde
    //Body temperature = rojo_izq, amarillo_izq, verde, amarillo_der, rojo_der
    //Systolic blood pressure = rojo_izq, amarillo_izq, verde, amarillo_der, rojo_der
    //Diastolic blood pressure = rojo_izq, amarillo_izq, verde, amarillo_der, rojo_der


    //Hay izquierda y derecha ya que hay colores por encima y por debajo del verde
    std::vector<std::string> etiquetas_variable_1 = {"rojo_izq", "amarillo_izq", "verde", "amarillo_der", "rojo_der"};
    
    // Las usamos para oxygen y para asignar el color de salida
    std::vector<std::string> etiquetas_salida = {"rojo", "amarillo", "verde"};

    //Definidos de manera predeterminada
    VariableDifusa fuzzyHeartrate("Hr", etiquetas_variable_1.size(), 0, 200, false, etiquetas_variable_1);
    VariableDifusa fuzzySaturation("O2", etiquetas_salida.size(), 0, 100, false, etiquetas_salida);
    VariableDifusa fuzzyBodyTemp("Bt", etiquetas_variable_1.size(), 0, 45, false, etiquetas_variable_1);
    VariableDifusa fuzzySystolicBP("SysBP", etiquetas_variable_1.size(), 0, 220, false, etiquetas_variable_1);
    VariableDifusa fuzzyDiastolicBP("DiaBP", etiquetas_variable_1.size(), 0, 160, false, etiquetas_variable_1);

    VariableDifusa fuzzyColorOutput("Output", etiquetas_salida.size(), 0, 100, false, etiquetas_salida);

    // Mostrar los conjuntos para verificar que se crearon correctamente
    //fuzzyHeartrate.mostrarConjuntos();
    //fuzzySaturation.mostrarConjuntos();
    //fuzzyBodyTemp.mostrarConjuntos();
    //fuzzySystolicBP.mostrarConjuntos();
    //fuzzyDiastolicBP.mostrarConjuntos();

    //Modificar los rangos en base al triage
    // heartrate rojo_izq: <40, amarillo_izq <60, verde 60-80, amarillo_der >110, rojo_der > 130
    fuzzyHeartrate.getConjunto(0)->setNucleoSupP(40);

    fuzzyHeartrate.getConjunto(1)->setLimiteInferiorP(40);
    fuzzyHeartrate.getConjunto(1)->setNucleoInfP(50);
    fuzzyHeartrate.getConjunto(1)->setNucleoSupP(50);
    fuzzyHeartrate.getConjunto(1)->setLimiteSuperiorP(60);

    fuzzyHeartrate.getConjunto(2)->setNucleoInfP(60);
    fuzzyHeartrate.getConjunto(2)->setNucleoSupP(80);
    fuzzyHeartrate.getConjunto(2)->setLimiteSuperiorP(110);

    fuzzyHeartrate.getConjunto(3)->setLimiteInferiorP(80);
    fuzzyHeartrate.getConjunto(3)->setNucleoInfP(110);
    fuzzyHeartrate.getConjunto(3)->setNucleoSupP(110);
    fuzzyHeartrate.getConjunto(3)->setLimiteSuperiorP(130);

    fuzzyHeartrate.getConjunto(4)->setLimiteInferiorP(110);
    fuzzyHeartrate.getConjunto(4)->setNucleoInfP(130);
    fuzzyHeartrate.getConjunto(4)->setNucleoSupP(150);
    fuzzyHeartrate.getConjunto(4)->setLimiteSuperiorP(150);

    //std::cout << "Después de modificar heartrate:" << std::endl;
    //fuzzyHeartrate.mostrarConjuntos();

    // Oxygen saturation rojo <70, amarillo 71 - 89, verde >90
    fuzzySaturation.getConjunto(0)->setLimiteSuperiorP(80);
    fuzzySaturation.getConjunto(0)->setNucleoSupP(70);
    
    fuzzySaturation.getConjunto(1)->setLimiteSuperiorP(90);
    fuzzySaturation.getConjunto(1)->setNucleoSupP(80);
    fuzzySaturation.getConjunto(1)->setNucleoInfP(80);
    fuzzySaturation.getConjunto(1)->setLimiteInferiorP(70);

    fuzzySaturation.getConjunto(2)->setLimiteSuperiorP(100);
    fuzzySaturation.getConjunto(2)->setNucleoSupP(100);
    fuzzySaturation.getConjunto(2)->setNucleoInfP(90);
    fuzzySaturation.getConjunto(2)->setLimiteInferiorP(80);

    //std::cout << "Después de modificar Saturation:" << std::endl;
    //fuzzySaturation.mostrarConjuntos();

    // Body temperature rojo_izq <35.5, amarillo_izq <36, verde 36.5-37.5, amarillo_der >38, rojo_der >40
    fuzzyBodyTemp.getConjunto(0)->setLimiteSuperiorP(36);
    fuzzyBodyTemp.getConjunto(0)->setNucleoSupP(35.5);

    fuzzyBodyTemp.getConjunto(1)->setLimiteSuperiorP(36.5);
    fuzzyBodyTemp.getConjunto(1)->setNucleoSupP(36);
    fuzzyBodyTemp.getConjunto(1)->setNucleoInfP(36);
    fuzzyBodyTemp.getConjunto(1)->setLimiteInferiorP(35.5);

    fuzzyBodyTemp.getConjunto(2)->setLimiteSuperiorP(38);
    fuzzyBodyTemp.getConjunto(2)->setNucleoSupP(37.5);
    fuzzyBodyTemp.getConjunto(2)->setNucleoInfP(36.5);
    fuzzyBodyTemp.getConjunto(2)->setLimiteInferiorP(36);

    fuzzyBodyTemp.getConjunto(3)->setLimiteSuperiorP(40);
    fuzzyBodyTemp.getConjunto(3)->setNucleoSupP(38);
    fuzzyBodyTemp.getConjunto(3)->setNucleoInfP(38);
    fuzzyBodyTemp.getConjunto(3)->setLimiteInferiorP(37.5);

    fuzzyBodyTemp.getConjunto(4)->setNucleoInfP(40);
    fuzzyBodyTemp.getConjunto(4)->setLimiteInferiorP(38);


    // std::cout << "Después de modificar BodyTemp:" << std::endl;
    // fuzzyBodyTemp.mostrarConjuntos();

    // Systolic blood pressure: rojo_izq <90, amarillo_izq <110, verde 120-140 amarillo_der >160, rojo_der >200

    fuzzySystolicBP.getConjunto(0)->setLimiteSuperiorP(110);
    fuzzySystolicBP.getConjunto(0)->setNucleoSupP(90);

    fuzzySystolicBP.getConjunto(1)->setLimiteSuperiorP(120);
    fuzzySystolicBP.getConjunto(1)->setNucleoSupP(110);
    fuzzySystolicBP.getConjunto(1)->setNucleoInfP(110);
    fuzzySystolicBP.getConjunto(1)->setLimiteInferiorP(90);

    fuzzySystolicBP.getConjunto(2)->setLimiteSuperiorP(160);
    fuzzySystolicBP.getConjunto(2)->setNucleoSupP(140);
    fuzzySystolicBP.getConjunto(2)->setNucleoInfP(120);
    fuzzySystolicBP.getConjunto(2)->setLimiteInferiorP(110);

    fuzzySystolicBP.getConjunto(3)->setLimiteSuperiorP(200);
    fuzzySystolicBP.getConjunto(3)->setNucleoInfP(160);
    fuzzySystolicBP.getConjunto(3)->setNucleoSupP(160);
    fuzzySystolicBP.getConjunto(3)->setLimiteInferiorP(140);

    fuzzySystolicBP.getConjunto(4)->setNucleoInfP(200);
    fuzzySystolicBP.getConjunto(4)->setLimiteInferiorP(160);


    //std::cout << "Después de modificar Systolic pressure:" << std::endl;
    //fuzzySystolicBP.mostrarConjuntos();


    // Diastolic blood pressure: rojo_izq <60, amarillo_izq <80, verde 80-100 amarillo_der >110, rojo_der >120
    //     0: 0 0 60 70 
    // 1: 60 70 70 80
    // 2: 70 80 100 110
    // 3: 100 110 110 120 
    // 4: 110 120 160 160

    fuzzyDiastolicBP.getConjunto(0)->setLimiteSuperiorP(70);
    fuzzyDiastolicBP.getConjunto(0)->setNucleoSupP(60);

    fuzzyDiastolicBP.getConjunto(1)->setLimiteSuperiorP(80);
    fuzzyDiastolicBP.getConjunto(1)->setNucleoSupP(70);
    fuzzyDiastolicBP.getConjunto(1)->setNucleoInfP(70);
    fuzzyDiastolicBP.getConjunto(1)->setLimiteInferiorP(60);

    fuzzyDiastolicBP.getConjunto(2)->setLimiteSuperiorP(110);
    fuzzyDiastolicBP.getConjunto(2)->setNucleoSupP(100);
    fuzzyDiastolicBP.getConjunto(2)->setNucleoInfP(80);
    fuzzyDiastolicBP.getConjunto(2)->setLimiteInferiorP(70);

    fuzzyDiastolicBP.getConjunto(3)->setLimiteSuperiorP(120);
    fuzzyDiastolicBP.getConjunto(3)->setNucleoInfP(110);
    fuzzyDiastolicBP.getConjunto(3)->setNucleoSupP(110);
    fuzzyDiastolicBP.getConjunto(3)->setLimiteInferiorP(100);

    fuzzyDiastolicBP.getConjunto(4)->setNucleoInfP(120);
    fuzzyDiastolicBP.getConjunto(4)->setLimiteInferiorP(110);

    //std::cout << "Después de modificar Diastolic pressure:" << std::endl;
    //fuzzyDiastolicBP.mostrarConjuntos();


    /*
    // 2. Configurar el Motor Difuso
    SistemaDifuso motor;

    // SI HeartRate ES "rojo_izq" (muy bajo) ENTONCES colorSalida ES "rojo"
    Regla r1(fuzzyColorOutput.getConjunto(0)->getEtiqueta(), 1);
    r1.agregarPremisaP(&fuzzyHeartrate, "rojo_izq", TipoPremisa::AFIRMACION);
    motor.agregarReglaP(r1);

    // --- REGLA DE EJEMPLO 2 ---
    // SI HeartRate ES "verde" (normal) ENTONCES colorSalida ES "verde"
    Regla r2(fuzzyColorOutput.getConjunto(2)->getEtiqueta(), 3);
    r2.agregarPremisaP(&fuzzyHeartrate, "verde", TipoPremisa::AFIRMACION);
    motor.agregarReglaP(r2);


    // 4. Prueba del Sistema
    double valorEntrada = 10.0; // Un valor bajo (debería activar "rojo_izq")
    
    std::cout << "Entrada HeartRate: " << valorEntrada << std::endl;

    // PASO A: Fuzzificar (calcular membresías de la entrada)
    fuzzyHeartrate.calcularMembresia(valorEntrada);

    // PASO B: Resolver (El motor evalúa las reglas)
    std::string resultado = motor.resolver();

    std::cout << "Resultado del Sistema: " << resultado << std::endl;

    // Debug: Ver qué reglas se activaron
    motor.mostrarReglasActivas();
    */
    return 0;

}
