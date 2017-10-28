#include <opencv2/highgui.hpp>
#include <vector> 
#include <iostream>
#include <string>
#include <sstream>
#include "genetico.cpp"
#include "genetico.h"

using namespace cv;
using namespace std;

cv::VideoCapture TheVideoCapturer;
cv::Mat bgrMap;

int main( int argc, const char** argv ){

  char key = 0;
 
  int numSnapshot = 0;
  string snapshotFilename = "0";
 
 cout << "Ingrese el numero de filas" << endl;
int filas;
cin >> filas;
 cout << "Ingrese el numero de columnas" << endl;
int columnas;
cin >> columnas;
  cout << "Press 's' to take snapshots" << endl;
  cout << "Press 'Esc' to exit" << endl;
 
  TheVideoCapturer.open(0);
 
  if (!TheVideoCapturer.isOpened()) {
    std::cerr<<"Could not open video"<<std::endl;
    return -1;
  }
 
  while (key!=27 && TheVideoCapturer.grab()) {
    TheVideoCapturer.retrieve(bgrMap);
 
    imshow("BGR image", bgrMap);

    if (key == 115) {
      cv::imwrite(snapshotFilename + ".png", bgrMap);
      numSnapshot++;
      snapshotFilename = static_cast<std::ostringstream*>(&(std::ostringstream() << numSnapshot))->str();
      break;
	}
  	key=cv::waitKey(20);
  }

  Genetico genetico;
  genetico.init("0.png",filas,columnas);
  genetico.mostrar();
  ///*
  while(0 <= genetico.gen){	
    	genetico.reproduccion();
  		genetico.mostrar();
  		genetico.seleccion();
  }
  //*/
  return 0;
}