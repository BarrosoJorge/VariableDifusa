#include "SistemaDifuso.h"
#include "reader.h"
#include <variant>
/*
 *
 *
 * for (const auto value : df["Heart Rate"].data) {
    std::visit([](const auto &celda) { std::cout << celda << std::endl; },
               value);
  }

 * */

int main() {
  auto df = read_csv("../data/dataset_final_2.csv");
  df.print_cols();
  df.info();
  return 0;
}
