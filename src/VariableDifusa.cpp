#include "VariableDifusa.h"

using namespace std;

VariableDifusa::VariableDifusa() {
	variable = "";
	numConjuntos = 0;
	Minimo = 0.0;
	Maximo = 0.0;
    membresias={};
}


VariableDifusa::VariableDifusa(const std::string& _variable, int _numConjuntos, double Min, double Max, bool triangular,const std::vector<std::string>& etiquetas={})
{
    variable = _variable;
    numConjuntos = _numConjuntos;
    Minimo = Min;
    Maximo = Max;
    membresias.clear();
    double paso = (Maximo - Minimo) / (numConjuntos - 1);
    for (int i = 0; i < numConjuntos; ++i)
    {
        double centro = Minimo + paso * i;
        std::unique_ptr<ConjuntoDifuso> nuevo;

        if (triangular)
        {
            double inf = (i == 0) ? Minimo : centro - paso;
            double sup = (i == numConjuntos - 1) ? Maximo : centro + paso;
            std::vector<double> parametros = { inf, centro, sup };
            if(etiquetas.size()==numConjuntos){
                nuevo = std::make_unique<Triangular>(parametros, etiquetas[i], i + 1);
            }
            else{
                nuevo = std::make_unique<Triangular>(parametros, "TriangularG" + std::to_string(i + 1), i + 1);
            }
        }
        else
        {
            double Limiteinf = (i == 0) ? Minimo : centro - paso;
            double Limitsup = (i == numConjuntos - 1) ? Maximo : centro + paso;
            std::vector<double> parametros = { Limiteinf, centro, centro, Limitsup };

            if(etiquetas.size()==numConjuntos){
                nuevo = std::make_unique<Trapezoidal>(parametros, etiquetas[i], i + 1);
            }
            else{
                nuevo = std::make_unique<Trapezoidal>(parametros, "TrapezoidalG" + std::to_string(i + 1), i + 1);
            }
        }

        // Asignar la forma dentro del constructor del conjunto
        conjuntos.push_back(std::move(nuevo));
        membresias.push_back(0.0);
    }
}



VariableDifusa::VariableDifusa(const std::string& _variable, int _numConjuntos, double Min, double Max, bool triangular)
{
    variable = _variable;
    numConjuntos = _numConjuntos;
    Minimo = Min;
    Maximo = Max;
    membresias.clear();
    double paso = (Maximo - Minimo) / (numConjuntos - 1);
    for (int i = 0; i < numConjuntos; ++i)
    {
        double centro = Minimo + paso * i;
        std::unique_ptr<ConjuntoDifuso> nuevo;

        if (triangular)
        {
            double inf = (i == 0) ? Minimo : centro - paso;
            double sup = (i == numConjuntos - 1) ? Maximo : centro + paso;
            std::vector<double> parametros = { inf, centro, sup };
            nuevo = std::make_unique<Triangular>(parametros, "TriangularG" + std::to_string(i + 1), i + 1);
        
        }
        else
        {
            double Limiteinf = (i == 0) ? Minimo : centro - paso;
            double Limitsup = (i == numConjuntos - 1) ? Maximo : centro + paso;
            std::vector<double> parametros = { Limiteinf, centro, centro, Limitsup };

            nuevo = std::make_unique<Trapezoidal>(parametros, "TrapezoidalG" + std::to_string(i + 1), i + 1);
            
        }

        // Asignar la forma dentro del constructor del conjunto
        conjuntos.push_back(std::move(nuevo));
        membresias.push_back(0.0);
    }
}

// ------------------------ M�todos de gesti�n protegidos------------------------

void VariableDifusa::agregarConjunto(std::unique_ptr<ConjuntoDifuso> nuevo) {
    conjuntos.push_back(std::move(nuevo));
    membresias.push_back(0.0);
    numConjuntos = (int)(conjuntos.size());
}

void VariableDifusa::agregarConjuntoTringular(double limInf, double nucleo, double limSup, const std::string& etiqueta) {
    std::unique_ptr<ConjuntoDifuso> nuevo;
	std::vector<double> params = { limInf, nucleo, limSup };
	int id = (int)(conjuntos.size()) + 1;
	nuevo = std::make_unique<Triangular>(params, etiqueta, id);
    conjuntos.push_back(std::move(nuevo));
    membresias.push_back(0.0);
    numConjuntos = (int)(conjuntos.size());
}

void VariableDifusa::agregarConjuntoTrapezoidal(double _limiteInf, double _nucleoInferior, double _nucleoSuperior, double _limiteSuperior, const std::string& etiqueta) {
    std::unique_ptr<ConjuntoDifuso> nuevo;
	std::vector<double> params = { _limiteInf, _nucleoInferior, _nucleoSuperior, _limiteSuperior };
	int id = (int)(conjuntos.size()) + 1;
	nuevo = std::make_unique<Trapezoidal>(params, etiqueta, id);
    conjuntos.push_back(std::move(nuevo));
    membresias.push_back(0.0);
    numConjuntos = (int)(conjuntos.size());
}

//editar para que sea en base a la etiqueta
void VariableDifusa::eliminarConjunto(const std::string& _etiqueta) {
    for (auto conjunto = conjuntos.begin(); conjunto != conjuntos.end(); ++conjunto) {
        if ((*conjunto)->getEtiqueta() == _etiqueta) {
            conjuntos.erase(conjunto);
            membresias.pop_back();
            numConjuntos = (int)(conjuntos.size());
            return;
        }
    }
}

void VariableDifusa::editarConjunto(const std::string& _etiqueta) {
    for (auto& conjunto : conjuntos) {
        if (conjunto->getEtiqueta() == _etiqueta) {
            cout << "Editar conjunto con etiqueta: " << _etiqueta << endl;
            cout << "Valores actuales:\n";
            conjunto->show();

            cout << "\nIngrese los nuevos valores...\n";
            conjunto->create(); // reutiliza el m�todo create de cada hijo

            cout << "Conjunto actualizado con �xito.\n";
            return;
        }
    }
    cout << "No se encontr� un conjunto con la etiqueta: " << _etiqueta << endl;
}


// ------------------------ Visualizaci�n ------------------------

void VariableDifusa::mostrarConjuntos() const {
    for (const auto& conjunto : conjuntos) {
        conjunto->show();
        cout << "----------------------\n";
    }
}

void VariableDifusa::mostrarConjunto(const std::string& _etiqueta) const {
    for (const auto& conjunto : conjuntos) {
        if (conjunto->getEtiqueta() == _etiqueta) {
            conjunto->show();
            return;
        }
    }
    cout << "Conjunto con etiqueta " << _etiqueta << " no encontrado." << endl;
}

// ------------------------ Membres�a ------------------------

void VariableDifusa::calcularMembresia(double valor) {
    //cout << "Valor: " << valor << endl;
    double maxMu=0.0;
    for (const auto& conjunto : conjuntos) {
        double mu = conjunto->membership(valor);
        membresias.at(conjunto->getID() - 1) = mu;
        if(mu>maxMu){
            maxMu=mu;
            this->etiquetaDif=conjunto->getEtiqueta();
            this->id=conjunto->getID();
        }
        //cout << "Conjunto [" << conjunto->getEtiqueta() << "] = " << mu << endl;
    }
}
std::string VariableDifusa::getEtiquetaDifusa() const {
    return etiquetaDif;
}
// ------------------------ Getters/Setters ------------------------

void VariableDifusa::setVariable(const std::string& _variable) {
    variable = _variable;
}

std::string VariableDifusa::getVariable() const {
    return variable;
}
int VariableDifusa::getId()const{
    return this->id;
}
int VariableDifusa::getNumConjuntos() const {
    return (int)(conjuntos.size());
}

std::pair<double, double> VariableDifusa::getRango() const {
    return { Minimo, Maximo };
}

void VariableDifusa::setRango(double nuevoMin, double nuevoMax) {
    if (nuevoMin >= nuevoMax) {
        throw std::invalid_argument("El minimo debe ser menor que el maximo.");
    }

    // Validar que los conjuntos est�n dentro del rango
    for (const auto& conjunto : conjuntos) {
        const auto& params = conjunto->getParametros();
        for (double p : params) {
            if (p < nuevoMin || p > nuevoMax) {
                throw std::out_of_range("Un conjunto queda fuera del nuevo rango.");
            }
        }
    }

    Minimo = nuevoMin;
    Maximo = nuevoMax;
}

ConjuntoDifuso* VariableDifusa::getConjunto(int index) const {
    if (index < 0 || index >= (int)(conjuntos.size())) {
        throw out_of_range("�ndice fuera de rango en getConjunto().");
    }
    return conjuntos[index].get();
}

ConjuntoDifuso* VariableDifusa::getConjunto(const std::string& etiqueta) const {
    for (const auto& conjunto : conjuntos) {
        if (conjunto->getEtiqueta() == etiqueta) {
            // Retorna la clase derivada si es triangular o trapezoidal
            if (dynamic_cast<Triangular*>(conjunto.get())) {
                return conjunto.get();  // Triangular
            }
            else if (dynamic_cast<Trapezoidal*>(conjunto.get())) {
                return conjunto.get();  // Trapezoidal
            }
            else {
                throw invalid_argument("Tipo de conjunto desconocido.");
            }
        }
    }
    throw invalid_argument("No se encontro un conjunto con la etiqueta: " + etiqueta);
}

//Publicos
void VariableDifusa::agregarConjuntoP(std::unique_ptr<ConjuntoDifuso> nuevo) {
    // Llama a la lógica protegida de agregar
    agregarConjunto(std::move(nuevo));
}

void VariableDifusa::agregarConjuntoTringularP(double limInf, double nucleo, double limSup, const std::string& etiqueta) {
    // Llama a la lógica protegida
    agregarConjuntoTringular(limInf, nucleo, limSup, etiqueta);
}

void VariableDifusa::agregarConjuntoTrapezoidalP(double _limiteInf, double _nucleoInferior, double _nucleoSuperior,
    double _limiteSuperior, const std::string& etiqueta) {
    // Llama a la l�gica protegida
    agregarConjuntoTrapezoidal(_limiteInf, _nucleoInferior, _nucleoSuperior, _limiteSuperior, etiqueta);
}

void VariableDifusa::eliminarConjuntoP(const std::string& _etiqueta) {
    // Llama a la l�gica protegida
    eliminarConjunto(_etiqueta);
}

void VariableDifusa::editarConjuntoP(const std::string& _etiqueta) {
    // Llama a la l�gica protegida
    editarConjunto(_etiqueta);
}

std::vector<double> VariableDifusa::getMembresias() const {
    return membresias;
}

