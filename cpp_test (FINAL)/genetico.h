#ifndef GENETICO_H
#define GENETICO_H

#include <opencv2/highgui.hpp>
#include <vector> 
#include <iostream>
#include "individuo.h"

using namespace cv;
using namespace std;

class Genetico{
	public:
		void init(string,int,int);
		void seleccion();
		void reproduccion();
		void mostrar();
		int gen;
	private:
		void poblacionInit(int);
		Mat imagenRef;
		vector<Individuo> poblacion;
		vector<Individuo> poblacionM;
		vector<int> revolver(vector<int>);
		Mat cruce(Mat, Mat);
		int filas;
		int columnas;
		vector<Mat> separar(Mat);
		Mat construir(vector<Mat>);
		bool igualdad(Mat,Mat);
		int fitness(Mat);
};

#endif // GENETICO_H