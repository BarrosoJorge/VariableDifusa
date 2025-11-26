#include "reader.h"
#include <algorithm>
#include <cmath>
#include <cstdio>
#include <functional>
#include <stdexcept>
#include <variant>
#include <vector>
DataFrame::DataFrame(const std::vector<std::string> &colnames) {
  addColNames(colnames);
}
void DataFrame::addColNames(const std::vector<std::string> &colnames) {
  for (const auto &names : colnames) {
    this->columns.push_back({names, {}});
  }
}
void DataFrame::add_row(const std::vector<Cell> &row) {
  for (size_t i = 0; i < row.size(); i++) {
    this->columns[i].data.push_back(row[i]);
  }
}
void DataFrame::print_cols() {
  std::cout << "Columnas: \n";
  for (const auto &columna : this->columns)
    std::cout << columna.name << std::endl;
}
DataFrame::column &DataFrame::operator[](const std::string &name) {
  for (auto &cols : this->columns) {
    if (cols.name == name) {
      return cols;
    }
  }
  throw std::out_of_range("Column does not exist: " + name);
}
double DataFrame::min(std::vector<Cell> &valor) {
  double min = 0.0;
  bool encontro = false;
  for (auto &column : valor) {
    if (std::holds_alternative<int>(column)) {
      double valor = (double)std::get<int>(column);
      if (!encontro) {
        min = valor;
        encontro = true;
      }
      if (min > valor)
        min = valor;
    }
    if (std::holds_alternative<double>(column)) {
      double valor = std::get<double>(column);
      if (!encontro) {
        min = valor;
        encontro = true;
      }
      if (min > valor)
        min = valor;
    } else {
      break;
    }
  }
  if (!encontro)
    std::runtime_error("No encontro");

  return min;
}
double DataFrame::max(std::vector<Cell> &valor) {
  double max = 0.0;
  bool encontro = false;
  for (auto &column : valor) {
    if (std::holds_alternative<int>(column)) {
      double valor = (double)std::get<int>(column);
      if (!encontro) {
        max = valor;
        encontro = true;
      }
      if (max < valor)
        max = valor;
    }
    if (std::holds_alternative<double>(column)) {
      double valor = std::get<double>(column);
      if (!encontro) {
        max = valor;
        encontro = true;
      }
      if (max < valor)
        max = valor;
    } else {
      break;
    }
  }
  if (!encontro)
    std::runtime_error("No encontro");

  return max;
}
double DataFrame::mean(std::vector<Cell> &valor) {
  double mean = 0.0;
  bool encontro = false;
  for (auto &column : valor) {
    if (std::holds_alternative<int>(column)) {
      double valor = (double)std::get<int>(column);
      mean += valor;
      encontro = true;
    }
    if (std::holds_alternative<double>(column)) {
      double valor = std::get<double>(column);
      mean += valor;
      encontro = true;
    } else {
      break;
    }
  }
  if (!encontro)
    std::runtime_error("No encontro");

  return mean / (double)valor.size();
}
double DataFrame::std(std::vector<Cell> &valor) {
  double suma = 0.0;
  bool encontro = false;
  double mean = this->mean(valor);
  for (auto &column : valor) {
    if (std::holds_alternative<int>(column)) {
      double valor = (double)std::get<int>(column);
      suma += (valor - mean) * (valor - mean);
      encontro = true;
    }
    if (std::holds_alternative<double>(column)) {
      double valor = std::get<double>(column);
      suma += (valor - mean) * (valor - mean);
      encontro = true;
    } else {
      break;
    }
  }
  if (!encontro)
    std::runtime_error("No encontro");

  return sqrt(suma / valor.size());
}
void DataFrame::info(std::vector<Cell> &valor) {
  double minimo = this->min(valor);
  double maximo = this->max(valor);
  double promedio = this->mean(valor);
  double desviacion = this->std(valor);
  std::vector<double> cuartil = this->cuartil(valor);
  std::cout << "minimo: " << minimo << std::endl;
  std::cout << "maximo: " << maximo << std::endl;
  std::cout << "promedio: " << promedio << std::endl;
  std::cout << "desviacion: " << desviacion << std::endl;
  std::cout << "q1: " << cuartil[0] << std::endl;
  std::cout << "q2: " << cuartil[1] << std::endl;
  std::cout << "q3: " << cuartil[2] << std::endl;
}
std::vector<double> DataFrame::cuartil(std::vector<Cell> &valor) {
  std::vector<double> copia;
  std::vector<double> cuartiles;
  cuartiles.reserve(3);
  bool encontro = false;
  for (auto &column : valor) {
    if (std::holds_alternative<int>(column)) {
      double valor = (double)std::get<int>(column);
      encontro = true;
      copia.push_back(valor);
    }
    if (std::holds_alternative<double>(column)) {
      double valor = std::get<double>(column);
      encontro = true;
      copia.push_back(valor);
    } else {
      break;
    }
  }
  std::sort(copia.begin(), copia.end());
  for (int i = 1; i <= 3; i++) {
    size_t cuartil_idx = (copia.size() - 1) * i / 4;
    double cuartil = (double)(copia.size() - 1) * 1 / 4;
    cuartiles.push_back(copia[cuartil_idx] +
                        (cuartil - cuartil_idx) *
                            (copia[cuartil_idx + 1] - copia[cuartil_idx]));
  }

  if (!encontro)
    std::runtime_error("No encontro");

  return cuartiles;
}

const DataFrame::column &DataFrame::operator[](const std::string &name) const {
  for (const auto &col : columns) {
    if (col.name == name) {
      return col;
    }
  }
  throw std::out_of_range("Column does not exist: " + name);
}
DataFrame read_csv(const std::string &file_path, char separation) {
  DataFrame d;
  std::fstream fs(file_path, std::fstream::in);
  if (!fs.is_open()) {
    throw std::runtime_error("Error al leer el archivo");
  }
  std::string line;
  std::getline(fs, line);
  auto cols = split_fast(line, separation);
  d.addColNames(cols);
  while (getline(fs, line)) {
    auto row_separated = split_fast(line, separation);
    std::vector<DataFrame::Cell> row;
    for (const auto &value : row_separated) {

      try {
        row.push_back(std::stod(value));
      } catch (...) {
        try {
          row.push_back(std::stoi(value));
        } catch (...) {
          row.push_back(value);
        }
      }
    }
    d.add_row(row);
  }
  fs.close();
  return d;
}

std::vector<std::string> split_fast(std::string line, char separation) {
  std::vector<std::string> out;
  size_t start = 0;
  size_t end = line.find(separation);
  while (end != std::string::npos) {
    out.emplace_back(line.substr(start, end - start));
    start = end + 1;
    end = line.find(separation, start);
  }
  out.emplace_back(line.substr(start));
  return out;
}
