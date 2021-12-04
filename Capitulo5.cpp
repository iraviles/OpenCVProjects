#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;

//Doblando

float w = 250, h = 350;
Mat matrix, imgWarp;
void main() {

	string path = "Resources/cards.jpg";
	Mat img = imread(path);
	
	//La funci�n que se usa requiere puntos flotantes Point2f
	Point2f src[4] = { {529,142},{771,190},{405,395},{674,457} };
	//Destination points (�a qu� puntos corresponden las coordenadas en el "rect�ngulo"?):
	Point2f dst[4] = { {0.0f,0.0f},{w,0.0f},{0.0f,h},{w,h} }; //w:width, h:height --> Tama�o de la carta

	//C�rculos en las esquinas (para que aparezcan en la transformaci�n)
	for (int i = 0; i < 4; i++) {
		circle(img, src[i], 10, Scalar(0, 0, 255), FILLED);
	}

	//Para transformar los puntos se necesita una matriz:
	matrix = getPerspectiveTransform(src, dst);		//Realiza en mapeo de los puntos de entrada a los de salida
	warpPerspective(img, imgWarp, matrix, Point(w, h));

	
	imshow("Image", img);
	imshow("Image Warp", imgWarp);



	waitKey(0);
}

