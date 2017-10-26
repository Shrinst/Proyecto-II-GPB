#include <iostream>
#include <opencv2/highgui.hpp>
#include <vector>
#include "individuo.h"

using namespace cv;
using namespace std;

void Individuo::revolver(){
	for (int i = 0; i < 100; ++i)
  { 
    int val = x*y;
    swap(imagenP[rand()%val],imagenP[rand()%val]);
  }
}
void Individuo::agregar(Mat im,int x_, int y_){
	
	Size s = im.size();
	int rows = s.height;
	int cols = s.width;
	vector<Mat> imagen1;
	int xx = cols/y_;
	int yy = rows/x_;
	for(int j = 0; j < x_; j++){
	  for(int i = 0; i < y_; i++){
	    Rect myROI(xx*i,yy*j,xx,yy);
	    Mat fragmento = im(myROI);
	    imagen1.push_back(fragmento);
	  }  
	}

	imagenP = imagen1;
	imagenR = imagen1;
	x = x_;
	y = y_;
	revolver();
	imagen = construir();
}
Mat Individuo::get_image(){
	return imagen;
}
Mat Individuo::construir(){
	vector<Mat> imagen1;
  	for(int j = 0; j < x; j++){
    	Mat buena = imagenP.at(j*y);
	    for(int i = 1; i < y; i++){
	    	hconcat(buena,imagenP.at((j*y)+i),buena);
	   	}
	    imagen1.push_back(buena);
	  	}
  	Mat picture = imagen1.at(0);
  	for(int i = 0; i < imagen1.size()-1; i++){
    vconcat(picture,imagen1.at(i+1),picture);
  	}
  	return picture;
}
