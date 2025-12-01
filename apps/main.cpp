#include "GeneradorVariables.h"
#include "SistemaDifuso.h"
#include "VariableDifusa.h"
#include "reader.h"
#include <stdexcept>
#include <vector>
#include <opencv2/opencv.hpp>

struct Paciente {
    int id;                 // ID del dataset (fila)
    std::string colorTriage;// "rojo", "amarillo", "verde"
    int prioridad;          // 2 (Rojo), 1 (Amarillo), 0 (Verde)
    double membresia;       // Fuerza de disparo (0.0 a 1.0) para desempate

    // Constructor actualizado (sin nombre)
    Paciente(int _id, std::string c, int p, double m) 
        : id(_id), colorTriage(c), prioridad(p), membresia(m) {}
};

struct ComparadorPacientes {
    bool operator()(const Paciente& a, const Paciente& b) {
        
        // 1. Criterio Principal: La Categoría (Rojo > Amarillo > Verde)
        if (a.prioridad != b.prioridad) {
            return a.prioridad < b.prioridad; 
        }

        // 2. Criterio de Desempate: La Intensidad (Fuzzy Membership)
        return a.membresia < b.membresia;
    }
};


class FuzzyModel {
private:
  std::vector<VariableDifusa> variables;
  SistemaDifuso motor;
  std::vector<std::string> predicciones;

public:
  FuzzyModel() {
    GeneradorVariables generator;
    variables.push_back(generator.crearHeartRate());
    variables.push_back(generator.crearOxygenSaturation());
    variables.push_back(generator.crearBodyTemp());
    variables.push_back(generator.crearSystolicBP());
    variables.push_back(generator.crearDiastolicBP());
    variables.push_back(generator.crearColorOutput());

    configurar_reglas();
  }
  void mostrarGraficas() {
      std::cout << "Generando gráficas de conjuntos difusos..." << std::endl;
      std::cout << "Se abrirán 6 ventanas. Presiona CUALQUIER TECLA en una de ellas para cerrar todas y continuar..." << std::endl;

      // Iteramos sobre todas las variables
      for (auto& var : variables) {
          // Ahora dibujar() es void y se encarga de abrir su propia ventana
          // con el nombre correcto. Ya no recibimos una cv::Mat.
          var.dibujar(1000, 400); 
      }

      // Este waitKey es fundamental: mantiene el programa pausado mostrando
      // todas las ventanas hasta que el usuario decida continuar.
      cv::waitKey(0); 
      
      // Limpiamos las ventanas antes de seguir con el procesamiento de datos
      cv::destroyAllWindows(); 
  }
  void mostrarConjuntosTerminal() {
    for (const auto &var : variables) {
      std::cout << "Variable Difusa: " << var.getVariable() << std::endl;
      var.mostrarConjuntos();
      std::cout << "==============================" << std::endl;
    }
  }

  void configurar_reglas() {
    motor = SistemaDifuso();
    // Reglas que activan la salida Roja
    Regla reglaRojo(
        "rojo",
        0); // Consecuente: Output es "rojo" (ID conjunto 0 en Output)
    reglaRojo.setOperador(TipoOperador::OR);
    // Agregamos todas las condiciones que disparan rojo
    reglaRojo.agregarPremisaP(&variables[0], "rojo_izq",
                              TipoPremisa::AFIRMACION);
    reglaRojo.agregarPremisaP(&variables[0], "rojo_der",
                              TipoPremisa::AFIRMACION);
    reglaRojo.agregarPremisaP(&variables[1], "rojo", TipoPremisa::AFIRMACION);
    reglaRojo.agregarPremisaP(&variables[2], "rojo_izq",
                              TipoPremisa::AFIRMACION);
    reglaRojo.agregarPremisaP(&variables[2], "rojo_der",
                              TipoPremisa::AFIRMACION);
    reglaRojo.agregarPremisaP(&variables[3], "rojo_izq",
                              TipoPremisa::AFIRMACION);
    reglaRojo.agregarPremisaP(&variables[3], "rojo_der",
                              TipoPremisa::AFIRMACION);
    reglaRojo.agregarPremisaP(&variables[4], "rojo_izq",
                              TipoPremisa::AFIRMACION);
    reglaRojo.agregarPremisaP(&variables[4], "rojo_der",
                              TipoPremisa::AFIRMACION);
    motor.agregarReglaP(reglaRojo);

    Regla reglaAmarillo("amarillo", 1);
    reglaAmarillo.setOperador(TipoOperador::OR);
    reglaAmarillo.agregarPremisaP(&variables[0], "amarillo_izq",
                                  TipoPremisa::AFIRMACION);
    reglaAmarillo.agregarPremisaP(&variables[0], "amarillo_der",
                                  TipoPremisa::AFIRMACION);
    reglaAmarillo.agregarPremisaP(&variables[1], "amarillo",
                                  TipoPremisa::AFIRMACION);
    reglaAmarillo.agregarPremisaP(&variables[2], "amarillo_izq",
                                  TipoPremisa::AFIRMACION);
    reglaAmarillo.agregarPremisaP(&variables[2], "amarillo_der",
                                  TipoPremisa::AFIRMACION);
    reglaAmarillo.agregarPremisaP(&variables[3], "amarillo_izq",
                                  TipoPremisa::AFIRMACION);
    reglaAmarillo.agregarPremisaP(&variables[3], "amarillo_der",
                                  TipoPremisa::AFIRMACION);
    reglaAmarillo.agregarPremisaP(&variables[4], "amarillo_izq",
                                  TipoPremisa::AFIRMACION);
    reglaAmarillo.agregarPremisaP(&variables[4], "amarillo_der",
                                  TipoPremisa::AFIRMACION);
    motor.agregarReglaP(reglaAmarillo);

    Regla reglaVerde("verde", 2);
    reglaVerde.setOperador(TipoOperador::AND);
    reglaVerde.agregarPremisaP(&variables[0], "verde", TipoPremisa::AFIRMACION);
    reglaVerde.agregarPremisaP(&variables[1], "verde", TipoPremisa::AFIRMACION);
    reglaVerde.agregarPremisaP(&variables[2], "verde", TipoPremisa::AFIRMACION);
    reglaVerde.agregarPremisaP(&variables[3], "verde", TipoPremisa::AFIRMACION);
    reglaVerde.agregarPremisaP(&variables[4], "verde", TipoPremisa::AFIRMACION);
    motor.agregarReglaP(reglaVerde);
  }
  std::vector<std::string> fit(DataFrame &X) {
    if (X.columns.size() != this->variables.size() - 1)
      throw std::runtime_error("Different sizes");
    std::vector<std::string> vector;
    for (size_t i = 0; i < X.rows(); i++) {
      // std::cout << "Paciente " << i + 1;
      for (size_t j = 0; j < this->variables.size() - 1; j++) {

        const auto &col = X.columns[j];
        double valor;
        switch (col.tipo) {
        case ColumnType::Int:
          valor = static_cast<double>(X.get_column_values<int>(col.name)[i]);
          break;
        case ColumnType::Double:
          valor = X.get_column_values<double>(col.name)[i];
          break;
        default:
          throw std::runtime_error(
              "Unsopported column type in Calcular memebresia");
        }
        this->variables[j].calcularMembresia(valor);
      }
      std::pair<std::string, double> resultado = this->motor.resolver();
      vector.push_back(resultado.first);
    }
    return vector;
  }
  Paciente evaluarPaciente(int index, const std::vector<double>& valores) {
      if (valores.size() != variables.size() - 1) 
          throw std::runtime_error("Error en dimensiones de paciente");

      // 1. Fuzzificar
      for (size_t j = 0; j < valores.size(); j++) {
          variables[j].calcularMembresia(valores[j]);
      }

      // 2. Resolver Sistema
      std::pair<std::string, double> resultado = motor.resolver();
      std::string etiqueta = resultado.first;
      double mu = resultado.second;

      // 3. Convertir etiqueta a prioridad numérica
      int prioridad = 0;
      if (etiqueta == "rojo") prioridad = 2;
      else if (etiqueta == "amarillo") prioridad = 1;
      else prioridad = 0;

      // Retornamos Paciente SIN nombre, solo ID
      return Paciente(index, etiqueta, prioridad, mu);
  }
  std::vector<int> evalue(std::vector<std::string> &y_test,
                          std::vector<std::string> &y_pred) {
    std::vector<std::string> auxiliar;
    for (auto &label : y_pred)
      auxiliar.push_back((label == "amarillo" || label == "rojo") ? "High Risk"
                                                                  : "Low Risk");
    std::vector<int> confusion(4, 0);
    // TP FP FN TN
    for (int i = 0; i < y_pred.size(); i++) {
      if (auxiliar[i] == "High Risk" && y_test[i] == "High Risk")
        confusion[0]++; // TP
      if (auxiliar[i] == "High Risk" && y_test[i] == "Low Risk")
        confusion[1]++; // FP
      if (auxiliar[i] == "Low Risk" && y_test[i] == "High Risk")
        confusion[2]++; // FN
      if (auxiliar[i] == "Low Risk" && y_test[i] == "Low Risk")
        confusion[3]++; // TN
    }
    return confusion;
  }
};
class Evaluador {
private:
  double accuracy;
  double recall;
  double precision;
  double f1score;
  std::vector<int> confusion;
  void accuracy_score() {
    this->accuracy =
        (double)(confusion[0] + confusion[3]) /
        (confusion[0] + confusion[1] + confusion[2] + confusion[3]);
  }
  void recall_score() {
    this->recall = (double)(confusion[0]) / (confusion[0] + confusion[2]);
  }
  void precision_score() {
    this->precision = (double)(confusion[0]) / (confusion[0] + confusion[1]);
  }
  void f1_score() {
    this->f1score = (double)2 * (this->precision * this->recall) /
                    (this->precision + this->recall);
  }

public:
  Evaluador(std::vector<int> &confusion_m) : confusion(confusion_m) {
    accuracy_score();
    recall_score();
    precision_score();
    f1_score();
  }
  void imprimir() {

    std::cout << "Accuracy: " << accuracy << std::endl;
    std::cout << "Recall: " << recall << std::endl;
    std::cout << "Precision: " << precision << std::endl;
    std::cout << "F1-score: " << f1score << std::endl;
  }
};

void print_confussion(std::vector<int> matriz) {
  std::cout << "TP: " << matriz[0] << std::endl;
  std::cout << "FP: " << matriz[1] << std::endl;
  std::cout << "FN: " << matriz[2] << std::endl;
  std::cout << "TN: " << matriz[3] << std::endl;
}

int main() {
  std::cout << "Inicializando Sistema de Triage" << std::endl;
  FuzzyModel model;

  // model.mostrarConjuntosTerminal();
  model.mostrarGraficas();

  DataFrame df = read_csv("../data/dataset_good.csv");
  DataFrame y = df["Risk Category"];

  DataFrame X = df.drop("Risk Category");

  // 3. Crear Cola de Prioridad
  std::priority_queue<Paciente, std::vector<Paciente>, ComparadorPacientes> salaDeEspera;

  // 4. Simulación de llegada de pacientes (Muestreo)
  int step = 10000; // Tomar 1 de cada 100 para no saturar
  std::cout << "\n--- SIMULANDO LLEGADA DE PACIENTES (Muestra: 1 de cada " << step << ") ---\n";
  
  for (size_t i = 0; i < X.rows(); i += step) {
      std::vector<double> valoresPaciente;
      
      // Extraer valores de la fila
      for (size_t j = 0; j < X.columns.size(); j++) {
          const auto &col = X.columns[j];
          double valor = 0.0;
          if (col.tipo == ColumnType::Int) 
              valor = static_cast<double>(X.get_column_values<int>(col.name)[i]);
          else 
              valor = X.get_column_values<double>(col.name)[i];
          
          valoresPaciente.push_back(valor);
      }

      // Evaluar y meter a la cola
      Paciente p = model.evaluarPaciente(i, valoresPaciente); // i es el ID
      salaDeEspera.push(p);
  }

  std::cout << "\nTotal en Sala de Espera: " << salaDeEspera.size() << " pacientes." << std::endl;
  std::cout << "Ordenando por Gravedad (Color) y Urgencia (Membresia)...\n" << std::endl;

  // 5. Atender pacientes en orden
  std::cout << "================ LISTA DE ATENCION ================" << std::endl;
  std::cout << std::left << std::setw(10) << "TURNO" 
            << std::setw(15) << "ID PACIENTE" 
            << std::setw(15) << "TRIAGE" 
            << std::setw(15) << "MEMBRESIA" << std::endl;
  std::cout << "---------------------------------------------------" << std::endl;

  int turno = 1;
  while (!salaDeEspera.empty()) {
      Paciente p = salaDeEspera.top();
      salaDeEspera.pop();

      // Códigos de color ANSI para la terminal
      std::string colorCode = "";
      if (p.colorTriage == "rojo") colorCode = "\033[1;31m";      // Red
      else if (p.colorTriage == "amarillo") colorCode = "\033[1;33m"; // Yellow
      else colorCode = "\033[1;32m"; // Green
      std::string resetColor = "\033[0m";

      std::cout << std::left << std::setw(10) << ("#" + std::to_string(turno++))
                << std::setw(15) << p.id 
                << colorCode << std::setw(15) << p.colorTriage << resetColor
                << std::setw(15) << std::fixed << std::setprecision(4) << p.membresia 
                << std::endl;
  }

  std::cout << "\n--- Evaluacion Global del Modelo ---" << std::endl;
  auto cuentas = y.value_counts(y.columns[0]);
  for (const auto &pares : cuentas)
    std::cout << pares.first << ":" << pares.second << std::endl;
  std::vector<std::string> y_pred = model.fit(X);
  std::vector<int> confusion =
      model.evalue(y.get_column_values<std::string>(y.columns[0].name), y_pred);
  print_confussion(confusion);
  Evaluador ev(confusion);
  ev.imprimir();
  return 0;
}
