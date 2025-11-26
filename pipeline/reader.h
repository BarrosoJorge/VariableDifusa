
#pragma once
#include <algorithm>
#include <fstream>
#include <iostream>
#include <math.h>
#include <string>
#include <variant>
#include <vector>
class DataFrame {
public:
  using Cell = std::variant<int, double, std::string>;

  struct column {
    std::string name;
    std::vector<Cell> data;
  };

private:
  std::vector<column> columns;
  size_t nrows = 0;

public:
  DataFrame() = default;
  DataFrame(const std::vector<std::string> &colnames);
  void addColNames(const std::vector<std::string> &colnames);
  size_t rows() const { return nrows; }
  size_t cols() const { return columns.size(); }
  double min(std::vector<Cell> &valor);
  double max(std::vector<Cell> &valor);
  double mean(std::vector<Cell> &valor);
  double std(std::vector<Cell> &valor);
  std::vector<double> cuartil(std::vector<Cell> &valor);

  void add_row(const std::vector<Cell> &row);
  column &operator[](const std::string &name);
  const column &operator[](const std::string &name) const;
  void print() const;
  void print_cols();
  void info(std::vector<Cell> &valor);
  void info();
};

DataFrame read_csv(const std::string &file_path, char separation = ',');
std::vector<std::string> split_fast(std::string line, char separation);
