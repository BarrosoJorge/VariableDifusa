#include "Trapezoidal.h"
#include <iostream>
#include <limits>
#include <stdexcept>


Trapezoidal::Trapezoidal() {
    forma = 1;
    id = 0;
    etiqueta = "";
    parametros.resize(4, 0.0);
}

Trapezoidal::Trapezoidal(const std::string& _etiqueta, int _id) {
    forma = 1;
    id = _id;
    etiqueta = _etiqueta;
    parametros.resize(4, 0.0);
}

Trapezoidal::Trapezoidal(const std::vector<double>& _parametros, const std::string& _etiqueta, int _id) {
    forma = 1;
    id = _id;
    etiqueta = _etiqueta;
    parametros = _parametros;
}

void Trapezoidal::create() {
    double a, b, c, d;
    std::string etiqueta;
    std::cout << "Creando conjunto difuso trapezoidal...\n";
    std::cout << "Ingrese limite inferior: ";
    do{

        while (!(std::cin >> a)){
            std::cout << "Entrada no numerica para limite inferior.";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        } 
        std::cout << "Ingrese nucleo inferior: ";
        while (!(std::cin >> b)){
            std::cout << "Entrada no numerica para nucleo inferior.";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        std::cout << "Ingrese nucleo superior: ";
        while (!(std::cin >> c)){
            std::cout << "Entrada no numerica para nucleo superior.";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        std::cout << "Ingrese limite superior: ";
        while (!(std::cin >> d)) {
            std::cout << "Entrada no numerica para limite superior.";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }    while (!(a <= b && b <= c && c <= d)&&       std::cout << "Error de logica: limite_inferior <= nucleo_inferior <= nucleo_superior <= limite_superior." << std::endl);

    std::cout << "Ingrese etiqueta: ";
    std::getline(std::cin, etiqueta);
    while (etiqueta.empty()) {
        std::cout << "Etiqueta no puede estar vacía. Intente nuevamente: ";
        std::getline(std::cin, etiqueta);
    }
    parametros={a, b, c, d};
    this->etiqueta=etiqueta;
    std::cout << "Conjunto trapezoidal creado exitosamente.\n";
}
void Trapezoidal::setForma(const int& _forma) {
	if (_forma == 0) {
        double nucleo = (getNucleoInfP() + getNucleoSupP()) / 2.0;
		setNucleoP(nucleo);
	}
	ConjuntoDifuso::setForma(_forma);
}
void Trapezoidal::show() const {
    std::cout << "Conjunto Difuso Trapezoidal [" << etiqueta << "]\n";
    std::cout << "Parametros: (" << parametros[0] << ", " << parametros[1]
              << ", " << parametros[2] << ", " << parametros[3] << ")\n";
    std::cout << "ID: " << id << std::endl;
}

double Trapezoidal::membership(double x) const {
    double a = parametros[0], b = parametros[1], c = parametros[2], d = parametros[3];

    if (x <= a || x >= d) return 0.0;
    else if (x >= b && x <= c) return 1.0;
    else if (x > a && x < b) return (x - a) / (b - a);
    else if (x > c && x < d) return (d - x) / (d - c);

    return 0.0;
}
//Limite inferiorP
void Trapezoidal::setLimiteInferiorP(double valor) { 
    setLimiteInferior(valor); 
}
double Trapezoidal::getLimiteInferiorP() const { 
    return getLimiteInferior(); 
}
//Nucleo inferiorP
void Trapezoidal::setNucleoInfP(double valor) { 
    setNucleoInf(valor); 
}
double Trapezoidal::getNucleoInfP() const { 
    return getNucleoInf(); 
}
//Nucleo superiorP
void Trapezoidal::setNucleoSupP(double valor) { 
    setNucleoSup(valor); 
}
double Trapezoidal::getNucleoSupP() const { 
    return getNucleoSup(); 
}
//Limite superiorP
void Trapezoidal::setLimiteSuperiorP(double valor) { 
    setLimiteSuperior(valor); 
}
double Trapezoidal::getLimiteSuperiorP() const { 
    return getLimiteSuperior(); 
}



double Trapezoidal::getLimiteInferior() const { 
    return parametros.size() > 0 ? parametros[0] : 0.0;
}
double Trapezoidal::getNucleoInf() const { 
	return parametros.size() > 1 ? parametros[1] : 0.0;
}
double Trapezoidal::getNucleoSup() const { 
	return parametros.size() > 2 ? parametros[2] : 0.0;
}
double Trapezoidal::getLimiteSuperior() const { 
	return parametros.size() > 3 ? parametros[3] : 0.0;
}

void Trapezoidal::setLimiteInferior(const double& _LimInferior) {
    if (_LimInferior <= parametros[1]) parametros[0] = _LimInferior;
    else std::cout << "Error: Limite inferior debe ser <= nucleo inferior." << std::endl;
}
void Trapezoidal::setNucleoInf(const double& _Nucleo) {
    if (_Nucleo >= parametros[0] && _Nucleo <= parametros[2]) parametros[1] = _Nucleo;
    else throw std::invalid_argument("Error: Nucleo inferior debe estar entre limite inferior y nucleo superior.");
}
void Trapezoidal::setNucleoSup(const double& _Nucleo) {
    if (_Nucleo >= parametros[1] && _Nucleo <= parametros[3]) parametros[2] = _Nucleo;
    else throw std::invalid_argument("Error: Nucleo superior debe estar entre nucleo inferior y limite superior.");
}
void Trapezoidal::setLimiteSuperior(const double& _LimSuperior) {
    if (_LimSuperior >= parametros[2]) parametros[3] = _LimSuperior;
    else throw std::invalid_argument("Error: Limite superior debe ser >= nucleo superior.");
}

void Trapezoidal::setNucleoP(double) { throw std::logic_error("No aplicable a Trapezoidal"); }
double Trapezoidal::getNucleoP() const { throw std::logic_error("No aplicable a Trapezoidal"); }
