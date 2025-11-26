
#pragma once
#include <algorithm>
#include <fstream>
#include <iostream>
#include <math.h>
#include <string>
#include <variant>
#include <vector>
enum class ColumnType { Int, Double, String };

class DataFrame {
public:
  struct column {
    std::string name;
    std::vector<int> ints;
    ColumnType tipo;
    std::vector<double> doubles;
    std::vector<std::string> strings;
  };

  std::vector<column> columns;

private:
  size_t nrows = 0;

public:
  DataFrame() = default;
  DataFrame(const std::vector<std::string> &colnames);
  void addColNames(const std::vector<std::string> &colnames);
  size_t rows() const { return nrows; }
  size_t cols() const { return columns.size(); }
  double min(const column &col) const;
  double max(const column &col) const;
  double mean(const column &col) const;
  double std(const column &col) const;
  std::vector<double> cuartil(const column &col) const;

  void add_row(const std::vector<std::string> &row);
  column &operator[](const std::string &name);
  const column &operator[](const std::string &name) const;
  void print() const;
  void print_cols();
  void info();
  void info(const column &valor);
};

DataFrame read_csv(const std::string &file_path, char separation = ',');
std::vector<std::string> split_fast(std::string line, char separation);
