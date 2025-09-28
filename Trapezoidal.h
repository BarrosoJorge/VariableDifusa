#pragma once

#include "ConjuntoDifuso.h"

class Trapezoidal : public ConjuntoDifuso {
public:
    Trapezoidal();
    Trapezoidal(const std::string& _etiqueta, int _id);
    Trapezoidal(const std::vector<double>& _parametros, const std::string& _etiqueta, int _id);

    void create() override;
    void show() const override;
    double membership(double x) const override;
	void setForma(const int& _forma) override;

    void setLimiteInferiorP(double valor);
    double getLimiteInferiorP() const;

    void setNucleoInfP(double valor);
    double getNucleoInfP() const;

    void setNucleoSupP(double valor);
    double getNucleoSupP() const;

    void setLimiteSuperiorP(double valor);
    double getLimiteSuperiorP() const;

protected:
    void setLimiteInferior(const double& _LimInferior);
    double getLimiteInferior() const;

    void setNucleoInf(const double& _Nucleo);
    double getNucleoInf() const;

    void setNucleoSup(const double& _Nucleo);
    double getNucleoSup() const;

    void setLimiteSuperior(const double& _LimSuperior);
    double getLimiteSuperior() const;

    void setNucleoP(double);
    double getNucleoP() const;
};


