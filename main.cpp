#include <opencv2/highgui.hpp>
#include <vector> 
#include <iostream>
#include "individuo.h"
#include "individuo.cpp"

using namespace cv;
using namespace std;

int main( int argc, const char** argv ){
  //CARGAR IMAGEN
  Mat im = imread("urgot.jpg");
  if(im.empty()){
    cout << "No se pudo subir la imagen" << endl;
  }

  Individuo uno;
  uno.agregar(im,2,2);

  imshow("Uno", uno.get_image());
  waitKey(0);

  return 0;
}