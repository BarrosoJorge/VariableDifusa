#include "SistemaDifuso.h"
#include "Regla.h"
#include "GeneradorVariables.h" // Incluimos tu nueva "Fábrica"
#include <iostream>
#include <vector>
#include <string>
#include <queue>

// Estructura para representar a un paciente evaluado
struct Paciente {
    std::string nombre;
    std::string colorTriage; // "rojo", "amarillo", "verde"
    int prioridad;           // 2 (Rojo), 1 (Amarillo), 0 (Verde)
    double membresia;        // Fuerza de disparo

    // Constructor simple
    Paciente(std::string n, std::string c, int p, double m) 
        : nombre(n), colorTriage(c), prioridad(p), membresia(m) {}
};

struct ComparadorPacientes {
    // Devuelve TRUE si el paciente "a" tiene MENOR prioridad que el "b"
    bool operator()(const Paciente& a, const Paciente& b) {
        
        // 1. Criterio Principal: La Categoría (Prioridad entera)
        if (a.prioridad != b.prioridad) {
            return a.prioridad < b.prioridad; 
            // Si A es 1 (Amarillo) y B es 2 (Rojo), A < B es true.
            // B sube a la cima.
        }

        // 2. Criterio de Desempate: La Intensidad (Membresía)
        // Si son del mismo color, atendemos primero al que tenga MAYOR membresía
        // (El amarillo más "puro" pasa antes que el amarillo "dudoso/verde")
        return a.membresia < b.membresia;
    }
};

int main() {
    // 1. Instanciar el generador
    GeneradorVariables generator;

    std::cout << "Inicializando Sistema de Triage" << std::endl;

    // 2. Crear las variables médicas (Ya vienen configuradas con los rangos exactos)
    VariableDifusa fuzzyHeartrate   = generator.crearHeartRate();
    VariableDifusa fuzzySaturation  = generator.crearOxygenSaturation();
    VariableDifusa fuzzyBodyTemp    = generator.crearBodyTemp();
    VariableDifusa fuzzySystolicBP  = generator.crearSystolicBP();
    VariableDifusa fuzzyDiastolicBP = generator.crearDiastolicBP();

    // Variable de Salida (Color del Triage)
    VariableDifusa fuzzyColorOutput = generator.crearColorOutput();

    // 3. Verificación Visual (Opcional)
    // Muestra un par de variables para confirmar que los rangos especiales se aplicaron
    //std::cout << "\nVariable Ritmo Cardiaco" << std::endl;
    //fuzzyHeartrate.mostrarConjuntos();

    //std::cout << "\nVariable Presion Diastolica" << std::endl;
    //fuzzyDiastolicBP.mostrarConjuntos();

    // 4. Configuración del Motor (Aquí irán las reglas de la Tarea 3)
    SistemaDifuso motor;

    // REGLA 1: PRIORIDAD ALTA (ROJO)
    // Lógica: Si CUALQUIER signo vital es crítico, la salida es ROJO.
    // Operador: OR 

    Regla reglaRojo("rojo", 0); // Consecuente: Output es "rojo" (ID conjunto 0 en Output)
    reglaRojo.setOperador(TipoOperador::OR); 

    // Agregamos todas las condiciones que disparan rojo

    reglaRojo.agregarPremisaP(&fuzzyHeartrate, "rojo_izq", TipoPremisa::AFIRMACION);
    reglaRojo.agregarPremisaP(&fuzzyHeartrate, "rojo_der", TipoPremisa::AFIRMACION);
    

    reglaRojo.agregarPremisaP(&fuzzySaturation, "rojo", TipoPremisa::AFIRMACION);
    

    reglaRojo.agregarPremisaP(&fuzzyBodyTemp, "rojo_izq", TipoPremisa::AFIRMACION);
    reglaRojo.agregarPremisaP(&fuzzyBodyTemp, "rojo_der", TipoPremisa::AFIRMACION);
    
 
    reglaRojo.agregarPremisaP(&fuzzySystolicBP, "rojo_izq", TipoPremisa::AFIRMACION);
    reglaRojo.agregarPremisaP(&fuzzySystolicBP, "rojo_der", TipoPremisa::AFIRMACION);


    reglaRojo.agregarPremisaP(&fuzzyDiastolicBP, "rojo_izq", TipoPremisa::AFIRMACION);
    reglaRojo.agregarPremisaP(&fuzzyDiastolicBP, "rojo_der", TipoPremisa::AFIRMACION);

    motor.agregarReglaP(reglaRojo);

    // REGLA 2: PRIORIDAD MEDIA (AMARILLO)
    // Lógica: Si algún signo es de alerta, considera Amarillo.

    Regla reglaAmarillo("amarillo", 1); 
    reglaAmarillo.setOperador(TipoOperador::OR);

 
    reglaAmarillo.agregarPremisaP(&fuzzyHeartrate, "amarillo_izq", TipoPremisa::AFIRMACION);
    reglaAmarillo.agregarPremisaP(&fuzzyHeartrate, "amarillo_der", TipoPremisa::AFIRMACION);
    

    reglaAmarillo.agregarPremisaP(&fuzzySaturation, "amarillo", TipoPremisa::AFIRMACION);


    reglaAmarillo.agregarPremisaP(&fuzzyBodyTemp, "amarillo_izq", TipoPremisa::AFIRMACION);
    reglaAmarillo.agregarPremisaP(&fuzzyBodyTemp, "amarillo_der", TipoPremisa::AFIRMACION);


    reglaAmarillo.agregarPremisaP(&fuzzySystolicBP, "amarillo_izq", TipoPremisa::AFIRMACION);
    reglaAmarillo.agregarPremisaP(&fuzzySystolicBP, "amarillo_der", TipoPremisa::AFIRMACION);


    reglaAmarillo.agregarPremisaP(&fuzzyDiastolicBP, "amarillo_izq", TipoPremisa::AFIRMACION);
    reglaAmarillo.agregarPremisaP(&fuzzyDiastolicBP, "amarillo_der", TipoPremisa::AFIRMACION);

    motor.agregarReglaP(reglaAmarillo);

    // REGLA 3: PRIORIDAD BAJA (VERDE)
    // Lógica: Para estar sano, TODOS los signos deben estar en rango normal.
    // Operador: AND (Mínimo)

    Regla reglaVerde("verde", 2);
    reglaVerde.setOperador(TipoOperador::AND); 

    reglaVerde.agregarPremisaP(&fuzzyHeartrate, "verde", TipoPremisa::AFIRMACION);
    reglaVerde.agregarPremisaP(&fuzzySaturation, "verde", TipoPremisa::AFIRMACION);
    reglaVerde.agregarPremisaP(&fuzzyBodyTemp, "verde", TipoPremisa::AFIRMACION);
    reglaVerde.agregarPremisaP(&fuzzySystolicBP, "verde", TipoPremisa::AFIRMACION);
    reglaVerde.agregarPremisaP(&fuzzyDiastolicBP, "verde", TipoPremisa::AFIRMACION);

    motor.agregarReglaP(reglaVerde);



    // 3. PRUEBA DE CASO (Simulación de un paciente)

    std::cout << "Simulación de Paciente" << std::endl;
    // Caso: Paciente con hipoxia severa (Sat 65 - Rojo) pero signos vitales normales en lo demas
    double in_hr = 70;      // Verde
    double in_sat = 65;     // Rojo (<70)
    double in_temp = 37;    // Verde
    double in_sys = 120;    // Verde
    double in_dia = 80;     // Verde

    std::cout << "Entradas: HR=" << in_hr << ", Sat=" << in_sat << ", Temp=" << in_temp << "..." << std::endl;

    // Fuzzificación
    fuzzyHeartrate.calcularMembresia(in_hr);
    fuzzySaturation.calcularMembresia(in_sat);
    fuzzyBodyTemp.calcularMembresia(in_temp);
    fuzzySystolicBP.calcularMembresia(in_sys);
    fuzzyDiastolicBP.calcularMembresia(in_dia);

    // Inferencia
    std::pair<std::string, double> res = motor.resolver();
    std::string resultado = res.first;
    
    std::cout << "Diagnóstico Sugerido: " << resultado << std::endl;
    
    motor.mostrarReglasActivas();


    std::cout << "\n\nGESTIÓN DE SALA DE ESPERA" << std::endl;

    // Creamos la cola de prioridad usando nuestro comparador
    std::priority_queue<Paciente, std::vector<Paciente>, ComparadorPacientes> salaDeEspera;
    
    // Paciente A: Amarillo MUY CLARO (Casi rojo o amarillo puro) -> Urgente
    salaDeEspera.push(Paciente("Juan (Amarillo Fuerte)", "amarillo", 1, 0.95));

    // Paciente B: Verde 
    salaDeEspera.push(Paciente("Luis (Verde)", "verde", 0, 0.8));

    // Paciente C: Rojo
    salaDeEspera.push(Paciente("Ana (Rojo)", "rojo", 2, 0.6)); 
    // Nota: Aunque su membresía es 0.6, su prioridad es 2, así que debe ganar.

    // Paciente D: Amarillo DUDOSO (Casi verde)
    salaDeEspera.push(Paciente("Pedro (Amarillo Debil)", "amarillo", 1, 0.4));

    std::cout << "Pacientes ingresados en desorden... Atendiendo por prioridad:\n" << std::endl;

    int turno = 1;
    while (!salaDeEspera.empty()) {
        Paciente p = salaDeEspera.top(); // Tomamos al de mayor prioridad
        salaDeEspera.pop();              // Lo sacamos de la fila

        std::cout << "Turno " << turno++ << ": " << p.nombre 
                  << " | Nivel: " << p.colorTriage 
                  << " (" << p.membresia << ")" << std::endl;
    }

    return 0;
}