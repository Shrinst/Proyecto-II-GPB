#include <opencv2/highgui.hpp>
#include <vector> 

#include <iostream>

using namespace cv;
using namespace std;

int main( int argc, const char** argv ){

  Mat im = imread("urgot.jpg");
  Mat img = imread("urgot1.jpg");
  if(im.empty()){
    cout << "No se pudo subir la imagen" << endl;
  }

  //Rect myROI(0,0,150,150);
  //Mat nueva;
  //hconcat(im,img,nueva);
  //Mat nueva1;
  //hconcat(img,im,nueva1);
  //Mat nueva2;
  //vconcat(nueva,nueva1,nueva2);
  //Mat croppedImage = im(myROI);

  //imshow("Cropped", croppedImage);

  //DIVIDIR LA IMAGEN
  Size s = im.size();
  int rows = s.height;
  int cols = s.width;

  vector<Mat> imagen;
  //imshow("Nueva", nueva2);
  int x_ = 3;//y
  int y_ = 4;//x
  int xx = cols/y_;
  int yy = rows/x_;
  for(int j = 0; j < x_; j++){
    for(int i = 0; i < y_; i++){
      Rect myROI(xx*i,yy*j,xx,yy);
      Mat fragmento = im(myROI);
      imagen.push_back(fragmento);
    }
  }
  //REVOLVER IMAGEN
  for (int i = 0; i < 10; ++i)
  { 
    int val = x_*y_;
    swap(imagen[rand()%val],imagen[rand()%val]);
  }
  //RECONSTRUIR LA IMAGEN
  vector<Mat> imagen1;
  for(int j = 0; j < x_; j++){
    Mat buena = imagen.at(j*y_);
    for(int i = 1; i < y_; i++){
      hconcat(buena,imagen.at((j*y_)+i),buena);
    }
    imagen1.push_back(buena);
  }
  Mat picture = imagen1.at(0);
  for(int i = 0; i < imagen1.size()-1; i++){
    vconcat(picture,imagen1.at(i+1),picture);
  }
  
  imshow("Image", picture);
  waitKey(0);

  return 0;
}