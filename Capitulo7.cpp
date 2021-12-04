#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;

Mat imgGray, imgBlur, imgCanny, imgDil, imgErode;

void getContours(Mat imgDil,Mat img) { //Imagen donde queremos entontrar el contorno, imagen donde queremos dibujar el contorno

	vector<vector<Point>> contours;		//Vector de vectores de puntos donde cada vector es un contorno
	vector<Vec4i> hierarchy;			//Vec4i es un tipo de dato de opencv para un vector de 4 enteros
	
										//Argumentos: Imagen de entrada, contornos, jerarquía, método, chain approximation
	findContours(imgDil, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
	//drawContours(img, contours, -1, Scalar(255, 0, 255), 2);	//Imagen donde se dibujará, contornos a dibujar, número de contorno a dibujar
																// (-1 para todos los contornos), color, thickness
	vector<vector<Point>>conPoly(contours.size());
	vector<Rect> boundRect(contours.size());						//Vector de rectángulos donde se almacenan los resultados de la función boundingbox
	string objectType;

	//Se creará un filtro para no detectar contornos "ruido"
	for (int i = 0; i < contours.size(); i++) {
		
		int area = contourArea(contours[i]); //Mismo tamaño que contours. No guarda puntos, sino número de esquinas
		cout << area << endl;

		if (area > 1000) {
			float peri = arcLength(contours[i], true);		// curva, objeto cerrado o no
			approxPolyDP(contours[i], conPoly[i], 0.02 * peri, true);	//Encontrar número de esquinas que tiene el polígono (aproximación de las curvas)
																		//conPoly será un arreglo a donde se envían los valores encontrados
																		//epsilon? Revisar. Se usó un número random, cerrado?
			drawContours(img, conPoly, i, Scalar(255, 0, 255), 2);
			cout << conPoly[i].size() << endl;

			//Bounding box
			boundRect[i] = boundingRect(conPoly[i]);
			rectangle(img, boundRect[i].tl(), boundRect[i].br(), Scalar(0, 255, 0), 2); // tl:top left point, br: bottom right point

			//Clasificar la figura
			int objCor = conPoly[i].size();		//Guarda el número de puntos de cada vector de conPoly
			if (objCor == 3) { objectType = "Triangulo"; }
			else if (objCor == 4) {
				float aspRatio = (float)boundRect[i].width / (float)boundRect[i].height;	//La figura es un cuadrado si 0.95<aspRatio<1.05
				cout << aspRatio << endl;
				if (aspRatio > 0.95 && aspRatio < 1.05) { objectType = "Cuadrado"; }
				else { objectType = "Rectangulo"; }
			}
			else if (objCor > 4) { objectType = "Circulo"; }
			putText(img, objectType, {boundRect[i].x, boundRect[i].y-5}, FONT_HERSHEY_PLAIN, 0.65, Scalar(0, 69, 255), 2);
		}
	}
}


//Detección de formas/contornos
//Se hace un preprocesamiento de la imagen con el detector de bordes de Canny 
void main() {

	string path = "Resources/shapes.png";
	Mat img = imread(path);	
	Mat imgGray, imgBlur, imgCanny, imgDil;
	
	//Preprocesamiento
	cvtColor(img, imgGray, COLOR_BGR2GRAY);			
	GaussianBlur(img, imgBlur, Size(7, 7), 5, 0);	
	Canny(imgBlur, imgCanny, 50, 150);

	Mat kernel = getStructuringElement(MORPH_RECT, Size(3, 3));		//Construcción del kernel para dilate y erode.
	dilate(imgCanny, imgDil, kernel);								//Los contornos quedan mejor definidos con dilation

	getContours(imgDil, img);
								
	imshow("Image", img);		
	/*imshow("Image Gray", imgGray);		
	imshow("Image Blur", imgBlur);		
	imshow("Image Canny", imgCanny);		
	imshow("Image Dil", imgDil);		*/

	waitKey(0);					
}
