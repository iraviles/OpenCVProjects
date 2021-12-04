#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;

//Funciones básicas
void main() {

	string path = "Resources/test.png";
	Mat img = imread(path);		//Mat es un tipo de dato matriz de opencv para manejar las imágenes.
								//Al hablar de imágenes, se usará este tpo de dato.
	Mat imgGray, imgBlur, imgCanny, imgDil, imgErode;
	
	cvtColor(img, imgGray, COLOR_BGR2GRAY);			//Opencv tiene la convención BGR en lugar de RGB
	GaussianBlur(img, imgBlur, Size(7, 7), 5, 0);	// Blur Gaussiano
	Canny(imgBlur, imgCanny, 50, 150);				//Detector de bordes

	Mat kernel = getStructuringElement(MORPH_RECT, Size(3, 3));		//Construcción del kernel para dilate y erode.
	dilate(imgCanny, imgDil, kernel);						//Aumentar "thickness" de los bordes
	erode(imgDil, imgErode, kernel);

	imshow("Image", img);		//Muestra la imagen img y le da el nombre "Image"
	imshow("Image Gray", imgGray);		
	imshow("Image Blur", imgBlur);	
	imshow("Image Canny", imgCanny);	
	imshow("Image Dilation", imgDil);	
	imshow("Image Erode", imgErode);	


	waitKey(0);					// Delay 0 para infinito
}

