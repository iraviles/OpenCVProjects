#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;

//Importando im�genes
/*void main() {

	string path = "Resources/test.png";
	Mat img = imread(path);		//Mat es un tipo de dato matriz de opencv para manejar las im�genes.
								//Al hablar de im�genes, se usar� este tpo de dato.
	imshow("Image", img);		//muestra la imagen img y le da el nombre "Image"
	waitKey(0);					// Delay 0 para infinito
}*/	

//Impotando videos
//Los videos son una serie de im�genes. 
//Es necesario un ciclo para iterar sobre todas las im�genes o frames, capturar y desplegar una por una.
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
//} //Env�a error dado que el ciclo no termina.

//Webcam
void main() {

	VideoCapture cap(0); //S�lo hay una c�mara: id=(0), en caso de que haya otra: id=(1)
	Mat img;
	while (true) {
		cap.read(img);
		imshow("Image", img);
		waitKey(1);
	}
}

