#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;

//VIRTUAL PAINTER
/*1. Detectar colores usando hs3 space
* 2. Pasar los colores al método de contorno para ubicarlos 
* 3. Tomar las posiciones x e y, y crear un círculo en ese punto
 */

Mat img;
vector<vector<int>> newPoints;

/*Se creará un vector de tres vectores para los tres colores que se usarán*/
/*Se han elegido los valores mínimos y máximos con el script ColorPicker*/
vector<vector<int>> myColors{{69, 59, 0, 132, 156, 255},	//Azul marino
							 //{38, 29, 43, 113, 144, 255},	//Verde
							 {0, 0, 3, 255, 255, 119}};		//Negro

//Mostrar color cuando es detectado:
vector<Scalar> myColorValues { {255, 0, 0},
	 						 //{ 0,0,255 },
							 { 0,0,0 }};

//Encontrar los puntos para dibujar
Point getContours(Mat imgDil) { 

	vector<vector<Point>> contours;		
	vector<Vec4i> hierarchy;			

										//Argumentos: Imagen de entrada, contornos, jerarquía, método, chain approximation
	findContours(imgDil, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
	//drawContours(img, contours, -1, Scalar(255, 0, 255), 2);	//Imagen donde se dibujará, contornos a dibujar, número de contorno a dibujar
																// (-1 para todos los contornos), color, thickness
	vector<vector<Point>>conPoly(contours.size());
	vector<Rect> boundRect(contours.size());						//Vector de rectángulos donde se almacenan los resultados de la función boundingbox

	Point myPoint(0, 0);
	//Se creará un filtro para no detectar contornos "ruido"
	for (int i = 0; i < contours.size(); i++) {

		int area = contourArea(contours[i]); //Mismo tamaño que contours. No guarda puntos, sino número de esquinas
		cout << area << endl;

		if (area > 1000) {
			float peri = arcLength(contours[i], true);		// curva, objeto cerrado o no
			approxPolyDP(contours[i], conPoly[i], 0.02 * peri, true);	

			cout << conPoly[i].size() << endl;
			boundRect[i] = boundingRect(conPoly[i]);
			myPoint.x = boundRect[i].x + boundRect[i].width / 2;
			myPoint.y = boundRect[i].y;

			drawContours(img, conPoly, i, Scalar(255, 0, 255), 2);
			rectangle(img, boundRect[i].tl(), boundRect[i].br(), Scalar(0, 255, 0), 2);	
		}
	}

	return myPoint;
}


vector<vector<int>> findColor(Mat img){

	Mat imgHSV;
	/*Se guardarán los valores mínimo y máximo de los colores que se usarán
	   y se encontrará una imagen para cada uno, por lo que se tendrán múltiples 
	   máscaras (una para cada color)*/
	cvtColor(img, imgHSV, COLOR_BGR2HSV);

	for (int i = 0; i < myColors.size(); i++) {


		Scalar lower(myColors[i][0], myColors[i][1], myColors[i][2]);
		Scalar upper(myColors[i][3], myColors[i][4], myColors[i][5]);
		Mat mask;
		inRange(imgHSV, lower, upper, mask);
		//imshow(to_string(i), mask);
		Point myPoint = getContours(mask);

		if (myPoint.x != 0 && myPoint.y != 0) {
			newPoints.push_back({ myPoint.x, myPoint.y, i });
		}
	}
	return newPoints;
}

void drawOnCanvas(vector<vector<int>> newPoints, vector<Scalar> myColorValues) {
	for (int i = 0; i < newPoints.size(); i++) {
		circle(img, Point(newPoints[i][0], newPoints[i][1]), 10, myColorValues[newPoints[i][2]], FILLED);
	}
}

void main() {

	VideoCapture cap(2); 
	
	while (true) {
		cap.read(img);
		newPoints = findColor(img);
		drawOnCanvas(newPoints, myColorValues);
		imshow("Image", img);
		waitKey(1);
	}
}

