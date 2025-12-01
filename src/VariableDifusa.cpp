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

void VariableDifusa::dibujar(int ancho, int alto) {
    // Aumentamos resolución para que se vea bien en pantalla completa
    // Si el usuario pide 1000x400, internamente podemos trabajar con eso, 
    // pero al usar WINDOW_NORMAL se estirará. 
    // Los márgenes ahora deben ser proporcionales o fijos.
    
    cv::Mat imagen(alto, ancho, CV_8UC3, cv::Scalar(255, 255, 255));
    
    // Capa temporal para dibujar los rellenos con transparencia
    cv::Mat overlay;
    imagen.copyTo(overlay);

    // Márgenes
    int margen_x = 60;
    int margen_y = 60;
    int plot_w = ancho - 2 * margen_x;
    int plot_h = alto - 2 * margen_y;

    double rango = Maximo - Minimo;

    // Lambdas de conversión
    auto valToX = [&](double val) -> int {
        if (val < Minimo) val = Minimo;
        if (val > Maximo) val = Maximo;
        return margen_x + (int)((val - Minimo) / rango * plot_w);
    };
    auto valToY = [&](double mu) -> int {
        return alto - margen_y - (int)(mu * plot_h);
    };

    // ---------------- ESTRUCTURA PARA DIBUJAR ETIQUETAS EJE X ----------------
    // Guardamos los puntos clave para dibujar sus valores numéricos abajo
    // Usamos un vector de pares (x_pixel, valor_double)
    std::vector<std::pair<int, double>> puntosClave;

    // ---------------- DIBUJO DE CONJUNTOS (TRANSPARENCIA) ----------------
    for (const auto& conjunto : conjuntos) {
        std::vector<double> params = conjunto->getParametros();
        std::vector<cv::Point> puntos;

        double a, b, c, d;
        double centroX = 0; 

        if (params.size() == 3) { // Triangular
            a = params[0]; b = params[1]; c = params[1]; d = params[2];
            centroX = b;
        } else { // Trapezoidal
            a = params[0]; b = params[1]; c = params[2]; d = params[3];
            centroX = (b + c) / 2.0;
        }

        // Guardar puntos para el eje X
        puntosClave.push_back({valToX(a), a});
        puntosClave.push_back({valToX(b), b});
        puntosClave.push_back({valToX(c), c});
        puntosClave.push_back({valToX(d), d});

        puntos.push_back(cv::Point(valToX(a), valToY(0.0))); 
        puntos.push_back(cv::Point(valToX(b), valToY(1.0))); 
        puntos.push_back(cv::Point(valToX(c), valToY(1.0))); 
        puntos.push_back(cv::Point(valToX(d), valToY(0.0))); 

        // Definir Colores
        cv::Scalar colorBorde(0, 0, 0);
        cv::Scalar colorRelleno(200, 200, 200);

        std::string tag = conjunto->getEtiqueta();
        
        if (tag.find("rojo") != std::string::npos || tag.find("red") != std::string::npos) {
            colorBorde = cv::Scalar(0, 0, 255);       // Rojo Borde
            colorRelleno = cv::Scalar(0, 0, 255);     // Rojo Relleno (para mezclar)
        } 
        else if (tag.find("amarillo") != std::string::npos || tag.find("orange") != std::string::npos) {
            colorBorde = cv::Scalar(0, 200, 255);     // Amarillo/Naranja Borde
            colorRelleno = cv::Scalar(0, 255, 255);   // Amarillo Relleno
        }
        else if (tag.find("verde") != std::string::npos || tag.find("green") != std::string::npos) {
            colorBorde = cv::Scalar(0, 150, 0);       // Verde Borde
            colorRelleno = cv::Scalar(0, 255, 0);     // Verde Relleno
        }

        // 1. Dibujar relleno sólido en el OVERLAY
        std::vector<std::vector<cv::Point>> poligonos = { puntos };
        cv::fillPoly(overlay, poligonos, colorRelleno);
        
        // 2. Dibujar borde sólido DIRECTAMENTE en la imagen final (para que quede nítido)
        cv::polylines(imagen, puntos, true, colorBorde, 2, cv::LINE_AA);
        
        // 3. Etiqueta del conjunto (Arriba)
        int baseLine = 0;
        cv::Size textSize = cv::getTextSize(tag, cv::FONT_HERSHEY_SIMPLEX, 0.5, 1, &baseLine);
        int textX = valToX(centroX) - (textSize.width / 2);
        int textY = valToY(1.0) - 10; 
        if (textY < 20) textY = 20;
        if (textX < 0) textX = 5;
        
        cv::putText(imagen, tag, cv::Point(textX, textY), 
                    cv::FONT_HERSHEY_SIMPLEX, 0.5, cv::Scalar(0,0,0), 1, cv::LINE_AA);
    }


    double alpha = 0.3; // 30% de opacidad para el relleno
    cv::addWeighted(overlay, alpha, imagen, 1.0 - alpha, 0, imagen);

    // Ejes
    cv::line(imagen, cv::Point(margen_x, alto - margen_y), cv::Point(ancho - margen_x, alto - margen_y), cv::Scalar(0, 0, 0), 2); 
    cv::line(imagen, cv::Point(margen_x, alto - margen_y), cv::Point(margen_x, margen_y), cv::Scalar(0, 0, 0), 2); 

    // Título Principal
    cv::putText(imagen, this->variable, cv::Point(ancho/2 - 40, 40), cv::FONT_HERSHEY_SIMPLEX, 1.0, cv::Scalar(0,0,0), 2, cv::LINE_AA);

    // Etiquetas Y (0 y 1)
    cv::putText(imagen, "1.0", cv::Point(10, margen_y), cv::FONT_HERSHEY_SIMPLEX, 0.5, cv::Scalar(0,0,0), 1);
    cv::putText(imagen, "0.0", cv::Point(10, alto - margen_y), cv::FONT_HERSHEY_SIMPLEX, 0.5, cv::Scalar(0,0,0), 1);

    std::sort(puntosClave.begin(), puntosClave.end(), [](auto &left, auto &right) {
        return left.first < right.first;
    });

    int lastX = -100; // Para controlar solapamiento horizontal
    int alturaTexto = 0; // Para alternar altura (zig-zag)

    for (const auto& par : puntosClave) {
        int x = par.first;
        double valor = par.second;

        // Si está muy cerca del anterior, saltamos o manejamos lógica especial
        // Aquí dibujamos todos pero alternamos la altura para que no choquen
        if (abs(x - lastX) < 25) { 
            // Si está muy cerca, dibujamos un poco más abajo
            alturaTexto = (alturaTexto == 0) ? 15 : 0; 
        } else {
            alturaTexto = 0;
        }

        // Pequeña línea vertical (tick)
        cv::line(imagen, cv::Point(x, alto - margen_y), cv::Point(x, alto - margen_y + 5), cv::Scalar(0,0,0), 1);

        // Formatear valor a string (sin muchos decimales)
        std::stringstream ss;
        ss << std::fixed << std::setprecision(1) << valor;
        std::string valStr = ss.str();
        // Quitar .0 si es entero
        if (valStr.find(".0") != std::string::npos) valStr = valStr.substr(0, valStr.find(".0"));

        // Dibujar valor
        // La altura base es (alto - margen_y + 20). Le sumamos alturaTexto para el efecto zig-zag
        cv::putText(imagen, valStr, cv::Point(x - 10, alto - margen_y + 20 + alturaTexto), 
                    cv::FONT_HERSHEY_SIMPLEX, 0.35, cv::Scalar(0,0,0), 1, cv::LINE_AA);
        
        lastX = x;
    }

    cv::namedWindow(this->variable, cv::WINDOW_NORMAL); 
    cv::imshow(this->variable, imagen);
}
