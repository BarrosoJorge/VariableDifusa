#include "GeneradorVariables.h"
#include "SistemaDifuso.h"
#include "VariableDifusa.h"
#include "reader.h"
#include <stdexcept>
#include <vector>

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
      vector.push_back(this->motor.resolver());
    }
    return vector;
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
    std::cout << "Preicision: " << precision << std::endl;
    std::cout << "F1-score: " << f1score << std::endl;
  }
};
int main() {
  std::cout << "Inicializando Sistema de Triage" << std::endl;
  FuzzyModel model;
  DataFrame df = read_csv("../data/dataset_final_2.csv");
  DataFrame y = df["Risk Category"];
  auto cuentas = y.value_counts(y.columns[0]);
  for (const auto &pares : cuentas)
    std::cout << pares.first << ":" << pares.second << std::endl;
  DataFrame X = df.drop("Risk Category");
  std::vector<std::string> y_pred = model.fit(X);
  std::vector<int> confusion =
      model.evalue(y.get_column_values<std::string>(y.columns[0].name), y_pred);
  for (const auto &elemento : confusion)
    std::cout << elemento << std::endl;
  Evaluador ev(confusion);
  ev.imprimir();
  return 0;
}
