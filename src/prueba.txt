#include "ConjuntoDifuso.h"
#include "Triangular.h"
#include "Trapezoidal.h"
#include "VariableDifusa.h"
#include<algorithm>
using namespace std;

int main() {
    /*
    // Crear variable Hue con rango 0-360
    VariableDifusa hue("Hue", 7, 0, 360, false);

    //  renombrar
    vector<string> etiquetas = { "RojoIzq", "Amarillo", "Verde", "Cyan", "Azul", "Magenta", "RojoDer" };
e de iteración en 
    for (int i = 0; i < hue.getNumConjuntos(); i++) {
        ConjuntoDifuso* conjunto = hue.getConjunto(i);
        conjunto->setEtiqueta(etiquetas[i]);
    }

    cout << " Conjuntos iniciales Hue (0-360) " << endl;
    hue.mostrarConjuntos();

	//cout << "Forma de verde: " << hue.getConjunto("Verde")->getForma() << endl;
	hue.getConjunto("Verde")->show();
	//hue.editarConjuntoP("Verde");
    //hue.getConjunto("Verde")->setNucleoInfP(90);
	//hue.getConjunto("Verde")->setNucleoSupP(150);
	hue.getConjunto("Verde")->show();


	hue.agregarConjuntoTrapezoidalP(0, 30, 30, 60, "Naranja");
	hue.mostrarConjuntos();
    */

    VariableDifusa Edad("Edad", 5, 20, 60, false);

	// Renombrar conjuntos a mano
    Edad.getConjunto(0)->setEtiqueta("Muy Joven"); //20 a 30
	Edad.getConjunto(1)->setEtiqueta("Joven"); //20 a 40
	Edad.getConjunto(2)->setEtiqueta("Adulto"); //30 a 50
	Edad.getConjunto(3)->setEtiqueta("Maduro"); //40 a 60
	Edad.getConjunto(4)->setEtiqueta("Viejo"); //50 a 60

    Edad.mostrarConjuntos();

    //Expandiendo el rango
	Edad.setRango(10, 80);
	cout << "Rango modificado: (" << Edad.getRango().first << ", " << Edad.getRango().second << ")\n";

	//Agregar un adolescente y un anciano

	Edad.agregarConjuntoTrapezoidalP(10, 10, 15, 20, "Adolescente");
	Edad.agregarConjuntoTrapezoidalP(60, 70, 80, 80, "Anciano");

	Edad.mostrarConjuntos();

	// Calcular membres�a
	Edad.calcularMembresia(22);
	std::vector<double> membresias = Edad.getMembresias();
	std::cout<<"Maximo:"<<*max_element(membresias.begin(), membresias.end())<<std::endl;
	//Eliminar un conjunto y hacer mas grande maduro
	Edad.eliminarConjuntoP("Viejo");
	Edad.getConjunto("Maduro")->setNucleoSupP(55);
	Edad.getConjunto("Maduro")->setLimiteSuperiorP(70);
	Edad.mostrarConjuntos();


    return 0;
}



