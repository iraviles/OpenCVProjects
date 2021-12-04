#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;

Mat imgHSV, mask, imgColor;
int hmin = 0, smin = 0, vmin = 0;
int hmax = 255, smax = 255, vmax = 255;

VideoCapture cap(2);
Mat img;

//Detección de color
void main() {

	string path = "Resources/shapes.png";
	Mat img = imread(path);
	
	//Creando el trackbar:
	namedWindow("Trackbars", (640,200));		//Nombre, tamaño 
	createTrackbar("Hue Min", "Trackbars", &hmin, 255); // Nombre de barra, ventana , hmin, hmax
	createTrackbar("Hue Max", "Trackbars", &hmax, 255);
	createTrackbar("Sat Min", "Trackbars", &smin, 255);
	createTrackbar("Sat Max", "Trackbars", &smax, 255);
	createTrackbar("Val Min", "Trackbars", &vmin, 255);
	createTrackbar("Val Max", "Trackbars", &vmax, 255);


	while (true) {
		cap.read(img);

		cvtColor(img, imgHSV, COLOR_BGR2HSV);

		Scalar lower(hmin, smin, vmin);
		Scalar upper(hmax, smax, vmax);
		inRange(imgHSV, lower, upper, mask);

		//Capturando los valores de los colores
		cout << hmin << "," << smin << "," << vmin << "," << hmax << "," << smax << "," << vmax << endl;

		imshow("Image", img);
		imshow("Image Mask", mask);
		waitKey(1);
	}
}
