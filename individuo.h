#ifndef INDIVIDUO_H
#define INDIVIDUO_H

#include <opencv2/highgui.hpp>
#include <vector> 
#include <iostream>

using namespace cv;
using namespace std;

class Individuo{
	public:
		void agregar(Mat, int, int);
		Mat get_image();
	private:
		int x;
		int y;
		vector<Mat> imagenP;
		vector<Mat> imagenR;
		Mat imagen;
		void revolver();
		Mat construir();
};

#endif // INDIVIDUO_H