#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;

//Importando imágenes
/*void main() {

	string path = "Resources/test.png";
	Mat img = imread(path);		//Mat es un tipo de dato matriz de opencv para manejar las imágenes.
								//Al hablar de imágenes, se usará este tpo de dato.
	imshow("Image", img);		//muestra la imagen img y le da el nombre "Image"
	waitKey(0);					// Delay 0 para infinito
}*/	

//Impotando videos
//Los videos son una serie de imágenes. 
//Es necesario un ciclo para iterar sobre todas las imágenes o frames, capturar y desplegar una por una.
//void main() {
//
//	string path = "Resources/test_video.mp4";
//	VideoCapture cap(path);
//	Mat img;
//	while (true) {
//		cap.read(img);
//		imshow("Image", img);		
//		waitKey(20);					
//	}
//} //Envía error dado que el ciclo no termina.

//Webcam
void main() {

	VideoCapture cap(0); //Sólo hay una cámara: id=(0), en caso de que haya otra: id=(1)
	Mat img;
	while (true) {
		cap.read(img);
		imshow("Image", img);
		waitKey(1);
	}
}

