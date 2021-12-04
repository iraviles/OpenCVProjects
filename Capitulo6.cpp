#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;

Mat imgHSV, mask;
int hmin = 0, smin = 0, vmin = 0;
int hmax = 179, smax = 255, vmax = 255;
//Para encontrar los valores del rango, se pueden usar track bars

//Detección de color
void main() {

	string path = "Resources/shapes.png";
	Mat img = imread(path);		
	
	cvtColor(img, imgHSV,COLOR_BGR2HSV);		//Convertir la imagen al formato HSV (por facilidad): Hue Saturation Value
										//Se especifica el rango del color buscado, Cada canal puede presentar diferentes tonos de un mismo color.
	//Creando el trackbar:
	namedWindow("Trackbars", (640, 200));		//Nombre, tamaño 
	createTrackbar("Hue Min", "Trackbars", &hmin, 179); // Nombre de barra, ventana , hmin, hmax
	createTrackbar("Hue Max", "Trackbars", &hmin, 179);
	createTrackbar("Sat Min", "Trackbars", &smin, 255);
	createTrackbar("Sat Max", "Trackbars", &smax, 255);
	createTrackbar("Val Min", "Trackbars", &vmin, 255);
	createTrackbar("Val Max", "Trackbars", &vmax, 255);


	while (true) {
		Scalar lower(hmin, smin, vmin);
		Scalar upper(hmax, smax, vmax);
		inRange(imgHSV, lower, upper, mask);

		imshow("Image", img);
		imshow("ImageHSV", imgHSV);
		imshow("Image Mask", mask);
		waitKey(1);
	}
}
