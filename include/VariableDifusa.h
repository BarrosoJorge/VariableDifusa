#pragma once
#include <vector>
#include <string>
#include <memory>

#include "Triangular.h"
#include "Trapezoidal.h" 
#include <opencv2/opencv.hpp>

class VariableDifusa {
    protected:
        std::vector<std::unique_ptr<ConjuntoDifuso>> conjuntos;
        std::string variable;
        int numConjuntos;
        double Minimo;
        double Maximo;
        std::vector<double> membresias;
        std::string etiquetaDif;
        int id;
        // M�todos de gesti�n de conjuntos
        void agregarConjunto(std::unique_ptr<ConjuntoDifuso> nuevo); //recibe un conjunto ya armado

        void agregarConjuntoTringular(double limInf, double nucleo, double limSup, const std::string& etiqueta);
        // crea y configura uno si triangular == true trabaja normal, si es false, usa a nucleo para los limites del nucleo de trapezoidal

        void agregarConjuntoTrapezoidal(double _limiteInf, double _nucleoInferior, double _nucleoSuperior, double _limiteSuperior,
            const std::string& etiqueta);// directamente crea y configura un trapezoidal

        void eliminarConjunto(const std::string& _etiqueta);
        void editarConjunto(const std::string& _etiqueta);

    public:
        // Constructores
        VariableDifusa();
        VariableDifusa(const std::string& _variable, int _numConjuntos, double Min, double Max, bool triangular,const std::vector<std::string>& etiquetas);
        VariableDifusa(const std::string& _variable, int _numConjuntos, double Min, double Max, bool triangular);

        //  M�todos p�blicos de gesti�n de conjuntos 
        void agregarConjuntoP(std::unique_ptr<ConjuntoDifuso> nuevo);
        void agregarConjuntoTringularP(double limInf, double nucleo, double limSup, const std::string& etiqueta);
        void agregarConjuntoTrapezoidalP(double _limiteInf, double _nucleoInferior, double _nucleoSuperior, double _limiteSuperior,
            const std::string& etiqueta);

        void eliminarConjuntoP(const std::string& _etiqueta);
        void editarConjuntoP(const std::string& _etiqueta);
        

        // M�todos de visualizaci�n
        void mostrarConjuntos() const;
        void mostrarConjunto(const std::string& _etiqueta) const;
        std::vector<double> getMembresias() const;
        // Membres�a
        void calcularMembresia(double valor);

        // Getters/Setters de la variable
        void setVariable(const std::string& _variable);
        std::string getVariable() const;

        int getNumConjuntos() const;

        std::pair<double, double> getRango() const;
        std::string getEtiquetaDifusa() const;
        int getId()const;
        void setRango(double nuevoMin, double nuevoMax);

        ConjuntoDifuso* getConjunto(int indice) const;
        ConjuntoDifuso* getConjunto(const std::string& etiqueta) const;


        void dibujar(int ancho = 800, int alto = 400);
};
