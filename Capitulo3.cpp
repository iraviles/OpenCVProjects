#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;

//Redimensionar y recortar
void main() {

	string path = "Resources/test.png";
	Mat img = imread(path);	
	Mat imgResized, imgCropped;

	cout << img.size() << endl;
	//resize(img, imgResized, Size(640, 480));	//Redimensiona la imagen al tamaño deseado
	resize(img, imgResized, Size(), 0.5, 0.5);	//Reescala la imagen a los factores especificados

	Rect roi(100, 100, 300, 250);				//Rectángulo (coordenadas, ancho, alto)
	imgCropped = img(roi);						//Recorta la imagen en l aregión especificada

	imshow("Image", img);		
	imshow("Image Resized", imgResized);		
	imshow("Image Cropped", imgCropped);		
	


	waitKey(0);					
}

