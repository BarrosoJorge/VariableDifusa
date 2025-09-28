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
    while (true) {
        try {
            cout << "Creando conjunto difuso triangular...\n";

            cout << "Ingrese limite inferior: ";
            if (!(cin >> inf)) throw invalid_argument("Entrada no numerica para limite inferior.");

            cout << "Ingrese nucleo: ";
            if (!(cin >> nucleo)) throw invalid_argument("Entrada no numerica para nucleo.");

            cout << "Ingrese limite superior: ";
            if (!(cin >> sup)) throw invalid_argument("Entrada no numerica para limite superior.");

            // Validar orden
            if (!(inf <= nucleo && nucleo <= sup)) {
                throw logic_error("limite_inferior <= nucleo <= limite_superior.");
            }

            cout << "Ingrese etiqueta: ";
            if (!(cin >> etiqueta)) throw invalid_argument("Entrada no numerica para etiqueta.");

            parametros[0] = inf;
            parametros[1] = nucleo;
            parametros[2] = sup;

            cout << "Conjunto triangular creado exitosamente.\n";
            break;
        }
        catch (const invalid_argument& e) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Error: " << e.what() << endl;
        }
        catch (const logic_error& e) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Error de logica: " << e.what() << endl;
        }
    }
}

void Triangular::show() const {
    cout << "Conjunto Difuso Triangular [" << etiqueta << "]\n";
    cout << "Parametros: (" << parametros[0] << ", " << parametros[1] << ", " << parametros[2] << ")\n";
    cout << "ID: " << id << endl;
}

double Triangular::membership(double x) const {
    double a = parametros[0], b = parametros[1], c = parametros[2];

    if (x <= a || x >= c) return 0.0;
    else if (x == b) return 1.0;
    else if (x > a && x < b) return (x - a) / (b - a);
    else if (x > b && x < c) return (c - x) / (c - b);

    return 0.0;
}

void Triangular::setLimiteInferiorP(double valor) { 
    setLimiteInferior(valor); 
}

double Triangular::getLimiteInferiorP() const { 
    return getLimiteInferior(); 
}

void Triangular::setNucleoP(double valor) { 
    setNucleo(valor); 
}

double Triangular::getNucleoP() const { 
    return getNucleo(); 
}

void Triangular::setLimiteSuperiorP(double valor) { 
    setLimiteSuperior(valor); 
}

double Triangular::getLimiteSuperiorP() const { 
    return getLimiteSuperior(); 
}

void Triangular::setLimiteInferior(const double& _LimInferior) {
	cout << "centro actual: " << parametros[1] << endl;
    if (_LimInferior <= parametros[1]) parametros[0] = _LimInferior;
    else cout << "Error: El limite inferior debe ser menor o igual que el nucleo." << endl;
}

double Triangular::getLimiteInferior() const {
    return parametros.size() > 0 ? parametros[0] : 0.0;
}

void Triangular::setNucleo(const double& _Nucleo) {
    if (_Nucleo >= parametros[0] && _Nucleo <= parametros[2]) parametros[1] = _Nucleo;
    else cout << "Error: El nucleo debe estar entre el limite inferior y el limite superior." << endl;
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


// Para Trapezoidal lanza excepción si se llama desde Triangular
void Triangular::setNucleoInfP(double) { throw logic_error("No aplicable a Triangular"); }
double Triangular::getNucleoInfP() const { throw logic_error("No aplicable a Triangular"); }
void Triangular::setNucleoSupP(double) { throw logic_error("No aplicable a Triangular"); }
double Triangular::getNucleoSupP() const { throw logic_error("No aplicable a Triangular"); }