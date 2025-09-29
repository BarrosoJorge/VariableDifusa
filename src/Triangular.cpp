#include "Triangular.h"

Triangular::Triangular(){
    forma = 0;
    id = 0;
    etiqueta = "";
    parametros.resize(3, 0.0);
}

Triangular::Triangular(const std::string& _etiqueta, int _id) {
    forma = 0;
    id = _id;
    etiqueta = _etiqueta;
    parametros.resize(3, 0.0);
}

Triangular::Triangular(const std::vector<double>& _parametros, const std::string& _etiqueta, int _id) {
    forma = 0;
    id = _id;
    etiqueta = _etiqueta;
    parametros = _parametros;
}


void Triangular::create() {
    double inf, nucleo, sup;
    std::string etiqueta;
    std::cout << "Creando conjunto difuso triangular...\n";
    std::cout << "Ingrese limite inferior: ";
    while (!(std::cin >> inf)){
        std::cout << "Entrada no numerica para limite inferior.";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    std::cout << "Ingrese nucleo: ";
    while (!(std::cin >> nucleo)) {
        std::cout << "Entrada no numerica para nucleo.";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    std::cout << "Ingrese limite superior: ";
    while (!(std::cin >> sup)) {
        std::cout << "Entrada no numerica para limite superior.";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    while (!(inf <= nucleo && nucleo <= sup)) {
        std::cout << "Error de logica: limite_inferior <= nucleo <= limite_superior." << std::endl;
        std::cout << "Ingrese limite inferior: "; std::cin >> inf;
        std::cout << "Ingrese nucleo: "; std::cin >> nucleo;
        std::cout << "Ingrese limite superior: "; std::cin >> sup;
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << "Ingrese etiqueta: ";
    std::getline(std::cin, etiqueta);
    while (std::getline(std::cin, etiqueta), etiqueta.empty()) {
        std::cout << "Etiqueta no puede estar vacía. Intente nuevamente: ";
        std::getline(std::cin, etiqueta);
    }
    parametros={inf, nucleo, sup};
    this->etiqueta = etiqueta;
    std::cout << "Conjunto triangular creado exitosamente.\n";   
}

void Triangular::show() const {
    std::cout << "Conjunto Difuso Triangular [" << etiqueta << "]\n";
    std::cout << "Parametros: (" << parametros[0] << ", " << parametros[1] << ", " << parametros[2] << ")\n";
    std::cout << "ID: " << id << std::endl;
}

double Triangular::membership(double x) const {
    double a = parametros[0], b = parametros[1], c = parametros[2];

    if (x <= a || x >= c) return 0.0;
    else if (x == b) return 1.0;
    else if (x > a && x < b) return (x - a) / (b - a);
    else if (x > b && x < c) return (c - x) / (c - b);

    return 0.0;
}

//LimiteInferiorP
void Triangular::setLimiteInferiorP(double valor) { 
    setLimiteInferior(valor); 
}

double Triangular::getLimiteInferiorP() const { 
    return getLimiteInferior(); 
}
//NucleoP
void Triangular::setNucleoP(double valor) { 
    setNucleo(valor); 
}

double Triangular::getNucleoP() const { 
    return getNucleo(); 
}
//LimiteSuperiorP
void Triangular::setLimiteSuperiorP(double valor) { 
    setLimiteSuperior(valor); 
}

double Triangular::getLimiteSuperiorP() const { 
    return getLimiteSuperior(); 
}

void Triangular::setLimiteInferior(const double& _LimInferior) {
	std::cout << "centro actual: " << parametros[1] << std::endl;
    if (_LimInferior > parametros[1]) 
        throw std::invalid_argument("Error: El limite inferior debe ser menor o igual que el nucleo.");
    parametros[0] = _LimInferior;
}

double Triangular::getLimiteInferior() const {
    return parametros.size() > 0 ? parametros[0] : 0.0;
}

void Triangular::setNucleo(const double& _Nucleo) {
    if (!(_Nucleo >= parametros[0] && _Nucleo <= parametros[2])) 
        throw std::invalid_argument("Error: El nucleo debe estar entre el limite inferior y el limite superior.");
    parametros[1] = _Nucleo;
}

double Triangular::getNucleo() const {
    return parametros.size() > 1 ? parametros[1] : 0.0;
}

void Triangular::setLimiteSuperior(const double& _LimSuperior) {
    if (_LimSuperior >= parametros[1]) parametros[2] = _LimSuperior;
    else cout << "Error: El limite superior debe ser mayor o igual que el nucleo." << endl;
}

double Triangular::getLimiteSuperior() const {
    return parametros.size() > 2 ? parametros[2] : 0.0;
}

void Triangular::setForma(const int& _forma) {
    if (_forma == 1) { 
        double nucleo = getNucleo();
        setLimiteInferior(nucleo);
        setLimiteSuperior(nucleo);
    }
    ConjuntoDifuso::setForma(_forma);
}


// Para Trapezoidal lanza excepci�n si se llama desde Triangular
void Triangular::setNucleoInfP(double) { throw logic_error("No aplicable a Triangular"); }
double Triangular::getNucleoInfP() const { throw logic_error("No aplicable a Triangular"); }
void Triangular::setNucleoSupP(double) { throw logic_error("No aplicable a Triangular"); }
double Triangular::getNucleoSupP() const { throw logic_error("No aplicable a Triangular"); }