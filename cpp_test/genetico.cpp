#include <iostream>
#include <opencv2/highgui.hpp>
#include <vector>
#include "genetico.h"
#include "individuo.cpp"
#include "individuo.h"

using namespace cv;
using namespace std;

void Genetico::init(string url, int filas_, int columnas_){
	imagenRef = imread(url);
	filas = filas_;
	columnas = columnas_;
	poblacionInit(3);
	gen = 0;
}
void Genetico::poblacionInit(int cant){
	for (int i = 0; i < cant; i++){
		Individuo individuo;
		individuo.agregar(imagenRef, filas, columnas,filas*columnas);
		poblacion.push_back(individuo);
	}
	poblacionM = poblacion;
}
void Genetico::reproduccion(){
	Mat uno = cruce(poblacionM.at(0).get_image(),poblacionM.at(1).get_image());
	Mat dos = cruce(poblacionM.at(0).get_image(),poblacionM.at(2).get_image());
	Mat tres = cruce(poblacionM.at(1).get_image(),poblacionM.at(2).get_image());
	
	Individuo individuo1;
	Individuo individuo2;
	Individuo individuo3;

	individuo1.agregar(uno, filas, columnas,0);
	poblacion.push_back(individuo1);

	individuo2.agregar(dos, filas, columnas,0);
	poblacion.push_back(individuo2);

	individuo3.agregar(tres, filas, columnas,0);
	poblacion.push_back(individuo3);

}
Mat Genetico::cruce(Mat A, Mat B){
	vector<Mat> REF = separar(imagenRef);
	vector<Mat> AA = separar(A);
	vector<Mat> BB = separar(B);
	vector<Mat> CC;
	vector<int> ran;
	vector<int> ran1;
	int x = 0;
	int y = 0;
	int cant = filas*columnas;
	
	for (int i = 0; i < cant; i++)
	{
		if(igualdad(AA.at(i),REF.at(i)) || igualdad(BB.at(i),REF.at(i))){
			ran.push_back(i);
		}else{
			ran1.push_back(i);
		}
	}
	for (int i = 0; i < 2*ran1.size(); i++){
    	int y = rand()%ran1.size();
		int z = rand()%ran1.size();
    	swap(ran1[y],ran1[z]);
    }
    for (int i = 0; i < cant; i++)
    {
    	if(ran.at(x) == i){
    		int indice = ran.at(x);
    		CC.push_back(REF.at(indice));
    		if(x < ran.size()-1){
    			x+=1;
    		}
    	}else{
    		int indice = ran1.at(y);
    		CC.push_back(REF.at(indice));
    		if(y < ran1.size()-1){
    			y+=1;
    		};
    	}
    }
	int w = rand()%10;
	if(w == 6){
		//cout << "MUTACION" << endl;
		int y = rand()%cant;
		int z = rand()%cant;
		swap(CC[y],CC[z]);
	}
	Mat nueva = construir(CC);
	return nueva;
}
vector<int> Genetico::revolver(vector<int> A){
	for (int i = 0; i < A.size(); i++){
    	int y = rand()%A.size();
		int z = rand()%A.size();
    	swap(A[y],A[z]);
    }
}
vector<Mat> Genetico::separar(Mat A){
	Size s = A.size();
	int rows = s.height;
	int cols = s.width;
	vector<Mat> imagen1;
	int xx = cols/columnas;
	int yy = rows/filas;
	for(int j = 0; j < filas; j++){
	  for(int i = 0; i < columnas; i++){
	    Rect myROI(xx*i,yy*j,xx,yy);
	    Mat fragmento = A(myROI);
	    imagen1.push_back(fragmento);
	  }  
	}
	return imagen1;
}
bool Genetico::igualdad(Mat A, Mat B) {
	if ( A.rows > 0 && A.rows == B.rows && A.cols > 0 && A.cols == B.cols ) {
    // Calculate the L2 relative error between images.
    double errorL2 = norm( A, B, CV_L2 );
    // Convert to a reasonable scale, since L2 error is summed across all pixels of the image.
    double similarity = errorL2 / (double)( A.rows * A.cols );
    if(similarity > 0){
    	return false;
    }else{
    	return true;
    }

}
else {
    //Images have a different size
    return false;  // Return a bad value
}
}
Mat Genetico::construir(vector<Mat> imagenP){
	vector<Mat> imagen1;
  	for(int j = 0; j < filas; j++){
    	Mat buena = imagenP.at(j*columnas);
	    for(int i = 1; i < columnas; i++){
	    	hconcat(buena,imagenP.at((j*columnas)+i),buena);
	   	}
	    imagen1.push_back(buena);
	  	}
  	Mat picture = imagen1.at(0);
  	for(int i = 0; i < imagen1.size()-1; i++){
    vconcat(picture,imagen1.at(i+1),picture);
  	}
  	return picture;
}
void Genetico::mostrar(){
	Mat uno = poblacionM.at(0).get_image();
	Mat dos = poblacionM.at(1).get_image();
	Mat tres = poblacionM.at(2).get_image();
	Mat mat(uno.rows, 10, CV_8UC3, Scalar(255,255,0));
	//hconcat(uno,mat,uno);
	//hconcat(uno,dos,uno);
	//hconcat(uno,mat,uno);
	//hconcat(uno,tres,uno);
	cout << "Poblacion: " << poblacion.size() << endl;
	cout << "Generacion: " << gen << endl;
	//cout << fitness(uno) << endl;
	//cout << fitness(dos) << endl;
	//cout << fitness(tres) << endl;
	//cout << "---" << endl;
	gen += 1;
	imshow("Mejores", uno);
	if(fitness(uno) == 100 || fitness(dos) == 100 || fitness(tres) == 100){
		cout << "COMPLETADO" << endl;
		gen = -1;
		waitKey(0);
	}else{
		waitKey(100);
	}
}
void Genetico::seleccion(){
	vector<Individuo> pobla = poblacion;
	for (int i = 0; i < pobla.size(); ++i)
	{
		if(fitness(pobla.at(i).get_image()) > fitness(poblacionM.at(0).get_image())){
			
				poblacionM.erase(poblacionM.begin());
				poblacionM.push_back(pobla.at(i));
			
			
		}else{
			if(fitness(pobla.at(i).get_image()) > fitness(poblacionM.at(1).get_image())){
				
					poblacionM.erase(poblacionM.begin()+1);
					poblacionM.push_back(pobla.at(i));
				
			}else{
				if(fitness(pobla.at(i).get_image()) > fitness(poblacionM.at(2).get_image())){
			
					poblacionM.erase(poblacionM.begin()+2);
					poblacionM.push_back(pobla.at(i));
					
				}
			}
		}
	}
}
int Genetico::fitness(Mat A){
	vector<Mat> REF = separar(imagenRef);
	vector<Mat> AA = separar(A);

	int x = 0;
	for (int i = 0; i < AA.size(); i++){
		if(igualdad(AA.at(i),REF.at(i))){
			x+=1;
		}
	}
	int y = (int)((x*100)/AA.size());
	return y;
}