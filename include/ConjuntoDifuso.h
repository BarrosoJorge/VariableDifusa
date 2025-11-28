#pragma once

//#include "Librerias.h"
#include <vector>
#include <string>
// Clase abstracta base
class ConjuntoDifuso {
   protected:
      std::vector<double> parametros;  
      std::string etiqueta;            
      int forma;                       // Tipo de conjunto (0 triangular, 1 trapezoidal, 2 gaussiana)
      int id;


      int prioridad;                   // Prioridad del conjunto (para resolución de conflictos)

   public:
      ConjuntoDifuso();
      ConjuntoDifuso(const std::string& _etiqueta, int _forma, int _id);
      ConjuntoDifuso(const std::vector<double>& _parametros, const std::string& _etiqueta, int _forma, int _id);
      virtual ~ConjuntoDifuso();

      // Setters y Getters
      void setEtiqueta(const std::string& _etiqueta);
      std::string getEtiqueta() const;

      virtual void setForma(const int& _forma);
      int getForma() const;

      void setID(int ID);
      int getID() const;

      void setParametros(const std::vector<double>& _parametros);
      void setParametros(const std::vector<double>&& _parametros);
      std::vector<double> getParametros() const;


      void setPrioridad(int _prioridad);
      int getPrioridad() const;


      // Metodos abstractos 
      virtual void create() = 0;
      virtual void show() const = 0;
      virtual double membership(double x) const = 0;

      // Metodos para Triangular 
      virtual void setLimiteInferiorP(double valor) = 0;
      virtual double getLimiteInferiorP() const = 0;

      virtual void setNucleoP(double valor) = 0;
      virtual double getNucleoP() const = 0;

      virtual void setLimiteSuperiorP(double valor) = 0;
      virtual double getLimiteSuperiorP() const = 0;

      // Metodos para Trapezoidal
      virtual void setNucleoInfP(double valor) = 0;
      virtual double getNucleoInfP() const = 0;

      virtual void setNucleoSupP(double valor) = 0;
      virtual double getNucleoSupP() const = 0;
};
