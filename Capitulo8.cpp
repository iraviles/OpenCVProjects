#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/objdetect.hpp>
#include <iostream>

using namespace cv;
using namespace std;

/*RECONOCIMIENTO DE ROSTROS.
Se usará el método Haar Cascade, un modelo preentrenado que usa archivos XML para cargar */
void main() {

	string path = "Resources/frontalface.png";
	Mat img = imread(path);		
	
	CascadeClassifier faceCascade;
	faceCascade.load("Resources/haarcascade_frontalface_default.xml");

	//Verificando que se ha cargado faceCascade
	if (faceCascade.empty()) { cout << "Archivo XML no cargado" << endl; }

	//Detección y almacenamiento de rostros
	vector<Rect> faces;
	faceCascade.detectMultiScale(img, faces, 1.1, 10);		//Imagen entrada, Lugar almacenamiento, Scale vector(revisar), minNeighbors(revisar) 

	//Iterando sobre los rostros detectados
	for (int i = 0; i < faces.size(); i++) {
		rectangle(img, faces[i].tl(), faces[i].br(), Scalar(255, 0, 255), 2);
	}

	imshow("Image", img);		
	waitKey(0);					
}
