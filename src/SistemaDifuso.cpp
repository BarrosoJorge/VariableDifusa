#include "SistemaDifuso.h"

SistemaDifuso::SistemaDifuso() {
    baseDeReglas.clear();
}

void SistemaDifuso::agregarReglaP(const Regla& _regla) {
    baseDeReglas.push_back(_regla);
}

void SistemaDifuso::limpiarReglas() {
    baseDeReglas.clear();
}

std::pair<std::string, double> SistemaDifuso::resolver() {
    double maxActivacion = -1.0;
    std::string etiquetaGanadora = "Ninguna";

    // 1. Recorremos todas las reglas
    for (auto& regla : baseDeReglas) {
        
        // 2. Evaluamos regla
        double activacion = regla.evaluarP();

        // 3. Método de Máxima Pertenencia
        if (activacion > maxActivacion) {
            maxActivacion = activacion;
            etiquetaGanadora = regla.getEtiquetaConsecuente();
        }
    }

    // Si la activación es muy baja
    if (maxActivacion <= 0.0001) {
        return {"Indefinido", 0.0};
    }

    return {etiquetaGanadora, maxActivacion};
}

void SistemaDifuso::mostrarReglasActivas() const {
    std::cout << "--- Estado de las Reglas ---" << std::endl;
    for (const auto& regla : baseDeReglas) {
        if (regla.getFuerzaDisparo() > 0.0) {
            std::cout << "[ACTIVA] (" << regla.getFuerzaDisparo() << ") " 
                      << regla.toString() << std::endl;
        }
    }
}