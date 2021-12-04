#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/objdetect.hpp>
#include <iostream>

using namespace cv;
using namespace std;

/*DETECCIÓN DE PLACAS DE COCHES.*/

void main() {
	VideoCapture cap(2);
	Mat img;

	CascadeClassifier plateCascade;
	plateCascade.load("Resources/haarcascade_russian_plate_number.xml");

	//Verificando que se ha cargado faceCascade
	if (plateCascade.empty()) { cout << "Archivo XML no cargado" << endl; }

	//Detección y almacenamiento de rostros
	vector<Rect> plates;

	while (true) {
		cap.read(img);
		plateCascade.detectMultiScale(img, plates, 1.1, 10);

		//Iterando sobre los rostros detectados
		for (int i = 0; i < plates.size(); i++) {
			Mat imgCrop = img(plates[i]);
			imshow(to_string(i), imgCrop);
			rectangle(img, plates[i].tl(), plates[i].br(), Scalar(255, 0, 255), 2);
		}

		imshow("Image", img);
		waitKey(1);
	}
}
