#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;

//Dibujar formas y texto
void main() {
	//Imagen en blanco
	Mat img(512, 512, CV_8UC3, Scalar(255,255,255));		//Nombre(largo, ancho, tipo(8U: 0 a 255 colores, C3: 3 canales)
														//Scalar(Valor de los colores BGR))
	//circle(img, Point(256, 256), 155, Scalar(0, 69, 255), 10); //(Imagen, (centro), radio, thickness )
	circle(img, Point(256, 256), 155, Scalar(0, 69, 255), FILLED); //(Imagen, (centro), radio, rellenado)
	rectangle(img, Point(130, 226), Point(382, 286), Scalar(255, 255, 255), FILLED); //Imagen, esquinas, color, thickness
	line(img, Point(130, 296), Point(382, 296), Scalar(255, 255, 255), 2); //Imagen, puntos inicial y final, color, thickness

	putText(img, "Taller OpenCV", Point(137, 262), FONT_HERSHEY_DUPLEX, 0.75, Scalar(0, 69, 255), 2);
	//Imagen, punto de inicio, fuente, escala, color, thickness
	
	imshow("Image", img);
	


	waitKey(0);
}

