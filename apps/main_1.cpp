/*
red_i
yellow
green
cyan
blue
magenta
red_d
plicacion con opencv


*/

#include "VariableDifusa.h"
#include <algorithm>
#include <opencv2/opencv.hpp>
int open_image(std::string name_file, cv::Mat &img) {
  img = cv::imread(name_file);
  if (img.empty()) {
    std::cerr << "Error al cargar la imagen!" << std::endl;
    return 1;
  }
  return 0;
}
void split_channels(const cv::Mat &img, std::vector<cv::Mat> &channels) {
  cv::Mat hsv;
  cvtColor(img, hsv, cv::COLOR_BGR2HSV_FULL);
  cv::split(hsv, channels);
}
int valor(cv::Mat &membresias, VariableDifusa &var,
          std::vector<std::string> etiqueta) {
  double valor = 0;
  for (int row = 0; row < membresias.rows; row++) {
    for (int col = 0; col < membresias.cols; col++) {
      std::string val = etiqueta[col + row * membresias.cols];
      ConjuntoDifuso *conj = var.getConjunto(val);
      valor = (conj->getNucleoSupP() + conj->getNucleoInfP()) / 2;
      if (val == "red_i" || val == "red_d")
        valor = 0.0;
      membresias.at<uchar>(row, col) = valor;
    }
  }
  return 0;
}
int main() {
  std::vector<std::string> etiquetas = {"red_i",  "orange",  "yellow",
                                        "green",  "cyan",    "blue",
                                        "purple", "magenta", "red_d"};
  VariableDifusa fuzzyHue("Hue", etiquetas.size(), 0, 255, false, etiquetas);
  fuzzyHue.mostrarConjuntos();
  cv::Mat img;
  open_image("../asset/rainbow.jpg", img);

  std::vector<cv::Mat> channels;
  split_channels(img, channels);
  // Ahora se hara el sistema de reglas

  cv::Mat hue = channels[0];
  cv::Mat etiquetasImg(hue.size(), CV_8U);
  std::vector<std::string> etiqueta;
  for (int row = 0; row < hue.rows; row++) {
    for (int col = 0; col < hue.cols; col++) {
      uchar pixel = hue.at<uchar>(row, col);
      fuzzyHue.calcularMembresia(pixel);
      etiquetasImg.at<uchar>(row, col) = fuzzyHue.getId();
      etiqueta.push_back(fuzzyHue.getEtiquetaDifusa());
    }
  }
  valor(etiquetasImg, fuzzyHue, etiqueta);

  channels[0] = etiquetasImg;
  channels[1] = cv::Mat::ones(channels[1].size(), CV_8U) * 255;
  channels[2] = cv::Mat::ones(channels[2].size(), CV_8U) * 255;
  cv::Mat hsv;
  cv::merge(channels, hsv);
  cv::Mat bgr;
  cv::cvtColor(hsv, bgr, cv::COLOR_HSV2BGR_FULL);
  cv::imshow("Hue en RGB", bgr);
  cv::waitKey(0);
}

/* ejemplo de implementacion con las nuevas clases, pero aun no esta probado.
int main() {
    // 1. Configurar Variables
    VariableDifusa fuzzyHue(...);
    VariableDifusa fuzzySat(...);

    // 2. Configurar el Sistema
    SistemaDifuso motor;

    // Crear Regla 1: Si Hue es Rojo Y Sat no es Baja -> Es Rojo
    Regla r1("red", 1);
    r1.agregarPremisaP(&fuzzyHue, "red_i", TipoPremisa::AFIRMACION);
    r1.agregarPremisaP(&fuzzySat, "low", TipoPremisa::NEGACION);
    motor.agregarReglaP(r1);

    // Crear Regla 2: Si Hue es Verde -> Es Verde
    Regla r2("green", 2);
    r2.agregarPremisaP(&fuzzyHue, "green", TipoPremisa::AFIRMACION);
    motor.agregarReglaP(r2);

        // loop de la imagen
    for(int row=0; row<rows; row++) {
        for(int col=0; col<cols; col++) {
             // A. Actualizar las variables con el dato crudo
             fuzzyHue.calcularMembresia(pixel_hue);
             fuzzySat.calcularMembresia(pixel_sat);

             // B. El motor decide
             std::string resultado = motor.resolver();

             // C. Usar el resultado
             // etiquetasImg.at<uchar>(row,col) = ...;
        }
    }
}
*/
