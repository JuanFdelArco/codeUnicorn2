#include "stdafx.h"
#include "opencv2/imgproc/imgproc.hpp"
#include <opencv2/highgui/highgui.hpp>
#include <iostream>


using namespace cv;
using namespace std;

double comparar(Mat alfabeto, Mat img_tratada)
{

	cout << "vuelvo a entrar" << endl;
	double matchresult = 100;
	double mincontour = 200;
	int CVCONTOUR_APPROX_LEVEL = 9;
	Mat drawing = alfabeto.clone();
	
	bool nuevo1, nuevo2;

	Mat bordes_alfabeto(alfabeto.size().width, alfabeto.size().height, CV_8UC1);
	Mat bordes_tratada(img_tratada.size().width, img_tratada.size().height, CV_8UC1);

	threshold(alfabeto, bordes_alfabeto, 127, 255, THRESH_BINARY);
	imshow("prueba", bordes_alfabeto);
	threshold(img_tratada,bordes_tratada, 127, 255, THRESH_BINARY);
	cout << "mmm1:  " << matchresult << endl;

	vector<vector<Point> >contours_alfabeto;
	vector<vector<Point> >contours_tratada;
	
	vector<Vec4i>hierarchy_alfabeto;
	vector<Vec4i>hierarchy_tratada;

	vector<Point>nueva_secuencia_1;
	vector<Point>nueva_secuencia_2;
	vector<Point> boundary;
	vector<Point> boundary2;
	int c_size = 0, c_idx = 0;

	findContours(bordes_alfabeto, contours_alfabeto, hierarchy_alfabeto, RETR_LIST, CHAIN_APPROX_SIMPLE);
	//drawContours(drawing, contours_alfabeto, 1, (0, 0, 255), 2, 8, hierarchy_alfabeto, 0, Point());
	//imshow("Contorno", drawing);

	findContours(bordes_tratada, contours_tratada, hierarchy_tratada, RETR_LIST, CHAIN_APPROX_SIMPLE);
	cout << "mmmm2: " << matchresult << endl;
	//cout << "El tama駉 es" << contours_alfabeto.size() << endl;
	//cout << "El tama駉 2 es" << contours_tratada.size() << endl;

	

		for (unsigned i = 0; i < contours_alfabeto.size(); i++)
		{
			boundary = contours_alfabeto[i];
			cout << "bound" << boundary << endl;
			nuevo1 = false;
			if (arcLength(boundary, true) > mincontour)
			{
				approxPolyDP(boundary, nueva_secuencia_1, 2, true);
				nuevo1 = true;
			}
			

	}



		for (int i = 0; i < contours_tratada.size(); i++)
		{
			boundary2 = contours_tratada[i];
			//cout << "" << boundary2 << endl;
			cout << " Perimetro: " << arcLength(boundary2, true) << endl;
			nuevo2 = false;
			if (arcLength(boundary2, true) > mincontour)
			{
				cout << "Estoy dentro sin problemas" << endl;
				approxPolyDP(boundary2, nueva_secuencia_2, 2, true);
				nuevo2 = true;

			}

		}

		

		//cout << "Nueva secuencia 1: " << nueva_secuencia_1 << endl;
		//cout << "Nueva secuencia 2: " << nueva_secuencia_2 << endl;

		cout << "antes del if" <<matchresult<< endl;
		if (nuevo1 == true && nuevo2 == true)
		{
			cout << "nueva secuencia2:  " << nueva_secuencia_2 << endl;
			cout << "nueva secuencia 1" << nueva_secuencia_1 << endl;

			
			matchresult = matchShapes(nueva_secuencia_2, nueva_secuencia_1, 2, 0);
			//cout << "mmmm3: " << matchresult << endl;
		}
		cout << "Match:" << matchresult << endl;
		bordes_alfabeto.release();
		bordes_tratada.release();
		contours_alfabeto.clear();
		contours_tratada.clear();
		
	    
		return matchresult;


		


	






}


int main(int argc, const char** argv)
{
	vector<Mat> letras;
	vector<Mat> resultados;
	Mat letra_A,letra_B;
	Mat res_A;
	letra_A= imread("A.JPG", CV_LOAD_IMAGE_GRAYSCALE);
	letras.push_back(letra_A);
	//letra_B= imread("B.JPG", CV_LOAD_IMAGE_GRAYSCALE);
	//letras.push_back(letra_B);
	res_A = imread("resultado_A.jpg", CV_LOAD_IMAGE_COLOR);
	resultados.push_back(res_A);

	

	
	
	
	

	
	VideoCapture cam(0);
	
	if (!cam.isOpened()) {
		cout << "ERROR not opened " << endl;
		return -1;
	}
	
	Mat img;
	Mat img_threshold;
	Mat img_gray;
	Mat img_roi;
	Mat capturada;

	double coincidencia; 

	namedWindow("Original_image", CV_WINDOW_AUTOSIZE);
	namedWindow("Gray_image", CV_WINDOW_AUTOSIZE);
	namedWindow("Thresholded_image", CV_WINDOW_AUTOSIZE);
	namedWindow("ROI", CV_WINDOW_AUTOSIZE);
	

	//char a[40];
	int count = 0;
	CvPoint pt1, pt2;
	//lImage * tableauxImage[6];
	


	while (1) {
		bool b = cam.read(img);
		if (!b) {
			cout << "ERROR : cannot read" << endl;
			return -1;
		}
		Rect roi(340, 100, 270, 270);
		rectangle(img, roi, 2, 10, 8);

		imshow("Original_image", img);

		img_roi = img(roi);
		if (waitKey(30) == 27) {
			capturada = img_roi.clone();
			cvtColor(capturada, img_gray, CV_RGB2GRAY);
			GaussianBlur(img_gray, img_gray, Size(19, 19), 0.0, 0);
			threshold(img_gray, img_threshold, 127, 255, THRESH_BINARY);
			imshow("Threshold", img_threshold);

			for (int i = 0; i<letras.size(); i++)
			{
				coincidencia = comparar(letras[i],img_threshold);
				if (coincidencia < 2.1)
				{
					
					imshow("Resultado", resultados[i]);
				}
			}

			imshow("Original_image", capturada);
			imshow("Threshold", img_threshold);

		}
	}
				return 0;
		}


