#include "Trapezoidal.h"
#include <iostream>
#include <limits>
#include <stdexcept>
using namespace std;


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
    while (true) {
        try {
            cout << "Creando conjunto difuso trapezoidal...\n";

            cout << "Ingrese limite inferior: ";
            if (!(cin >> a)) throw invalid_argument("Entrada no numerica para limite inferior.");

            cout << "Ingrese nucleo inferior: ";
            if (!(cin >> b)) throw invalid_argument("Entrada no numerica para nucleo inferior.");

            cout << "Ingrese nucleo superior: ";
            if (!(cin >> c)) throw invalid_argument("Entrada no numerica para nucleo superior.");

            cout << "Ingrese limite superior: ";
            if (!(cin >> d)) throw invalid_argument("Entrada no numerica para limite superior.");

            if (!(a <= b && b <= c && c <= d)) {
                throw logic_error("Limite_inferior <= Nucleo_inferior <= Nucleo_superior <= Limite_superior.");
            }

            cout << "Ingrese etiqueta: ";
            if (!(cin >> etiqueta)) throw invalid_argument("Entrada no valida para etiqueta.");

            parametros[0] = a;
            parametros[1] = b;
            parametros[2] = c;
            parametros[3] = d;

            cout << "Conjunto trapezoidal creado exitosamente.\n";
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
void Trapezoidal::setForma(const int& _forma) {
	if (_forma == 0) {
        double nucleo = (getNucleoInfP() + getNucleoSupP()) / 2.0;
		setNucleoP(nucleo);
	}
	ConjuntoDifuso::setForma(_forma);
}
void Trapezoidal::show() const {
    cout << "Conjunto Difuso Trapezoidal [" << etiqueta << "]\n";
    cout << "Parametros: (" << parametros[0] << ", " << parametros[1]
        << ", " << parametros[2] << ", " << parametros[3] << ")\n";
    cout << "ID: " << id << endl;
}

double Trapezoidal::membership(double x) const {
    double a = parametros[0], b = parametros[1], c = parametros[2], d = parametros[3];

    if (x <= a || x >= d) return 0.0;
    else if (x >= b && x <= c) return 1.0;
    else if (x > a && x < b) return (x - a) / (b - a);
    else if (x > c && x < d) return (d - x) / (d - c);

    return 0.0;
}

void Trapezoidal::setLimiteInferiorP(double valor) { 
    setLimiteInferior(valor); 
}
double Trapezoidal::getLimiteInferiorP() const { 
    return getLimiteInferior(); 
}

void Trapezoidal::setNucleoInfP(double valor) { 
    setNucleoInf(valor); 
}
double Trapezoidal::getNucleoInfP() const { 
    return getNucleoInf(); 
}

void Trapezoidal::setNucleoSupP(double valor) { 
    setNucleoSup(valor); 
}
double Trapezoidal::getNucleoSupP() const { 
    return getNucleoSup(); 
}

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
    else cout << "Error: Limite inferior debe ser <= nucleo inferior." << endl;
}
void Trapezoidal::setNucleoInf(const double& _Nucleo) {
    if (_Nucleo >= parametros[0] && _Nucleo <= parametros[2]) parametros[1] = _Nucleo;
    else cout << "Error: Nucleo inferior debe estar entre limite inferior y nucleo superior." << endl;
}
void Trapezoidal::setNucleoSup(const double& _Nucleo) {
    if (_Nucleo >= parametros[1] && _Nucleo <= parametros[3]) parametros[2] = _Nucleo;
    else cout << "Error: Nucleo superior debe estar entre nucleo inferior y limite superior." << endl;
}
void Trapezoidal::setLimiteSuperior(const double& _LimSuperior) {
    if (_LimSuperior >= parametros[2]) parametros[3] = _LimSuperior;
    else cout << "Error: Limite superior debe ser >= nucleo superior." << endl;
}

void Trapezoidal::setNucleoP(double) { throw logic_error("No aplicable a Trapezoidal"); }
double Trapezoidal::getNucleoP() const { throw logic_error("No aplicable a Trapezoidal"); }
