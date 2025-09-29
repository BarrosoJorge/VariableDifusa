#pragma once
#include "ConjuntoDifuso.h"
#include <iostream>
#include <stdexcept>
#include <limits>
class Triangular : public ConjuntoDifuso {
    public:
        
        Triangular(); 
        Triangular(const std::string& _etiqueta, int _id); 
        Triangular(const std::vector<double>& _parametros, const std::string& _etiqueta, int _id); 

        void create() override;
        void show() const override;
        double membership(double x) const override;

        void setLimiteInferiorP(double valor);
        double getLimiteInferiorP() const;

        void setNucleoP(double valor);
        double getNucleoP() const;

        void setLimiteSuperiorP(double valor);
        double getLimiteSuperiorP() const;

        void setForma(const int& _forma) override;

    protected:
        // Setters y getters protegidos con validaciones
        void setLimiteInferior(const double& _LimInferior);
        double getLimiteInferior() const;

        void setNucleo(const double& _Nucleo);
        double getNucleo() const;

        void setLimiteSuperior(const double& _LimSuperior);
        double getLimiteSuperior() const;

        // Para Trapezoidal lanza excepci�n si se llama desde Triangular
        void setNucleoInfP(double); 
        double getNucleoInfP() const;
        void setNucleoSupP(double); 
        double getNucleoSupP() const; 
};

