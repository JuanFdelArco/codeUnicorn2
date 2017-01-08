#include "stdafx.h"
#include "opencv2/imgproc/imgproc.hpp"
#include <opencv2/highgui/highgui.hpp>
#include <iostream>


using namespace cv;
using namespace std;

double comparar(Mat alfabeto, Mat img_tratada)
{

	//cout << "vuelvo a entrar" << endl;
	double matchresult = 100;
	double mincontour = 200;
	int CVCONTOUR_APPROX_LEVEL = 9;
	Mat drawing = alfabeto.clone();
	
	bool nuevo1, nuevo2;

	Mat bordes_alfabeto(alfabeto.size().width, alfabeto.size().height, CV_8UC1);
	Mat bordes_tratada(img_tratada.size().width, img_tratada.size().height, CV_8UC1);

	threshold(alfabeto, bordes_alfabeto, 127, 255, THRESH_BINARY);
	//imshow("prueba", bordes_alfabeto);
	threshold(img_tratada,bordes_tratada, 127, 255, THRESH_BINARY);
	//cout << "mmm1:  " << matchresult << endl;

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
	//cout << "mmmm2: " << matchresult << endl;
	//cout << "El tamaño es" << contours_alfabeto.size() << endl;
	//cout << "El tamaño 2 es" << contours_tratada.size() << endl;

		for (unsigned i = 0; i < contours_alfabeto.size(); i++)
		{
			boundary = contours_alfabeto[i];
			//cout << "bound" << boundary << endl;
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
			//cout << " Perimetro: " << arcLength(boundary2, true) << endl;
			nuevo2 = false;
			if (arcLength(boundary2, true) > mincontour)
			{
				//cout << "Estoy dentro sin problemas" << endl;
				approxPolyDP(boundary2, nueva_secuencia_2, 2, true);
				nuevo2 = true;
			}
		}

		//cout << "Nueva secuencia 1: " << nueva_secuencia_1 << endl;
		//cout << "Nueva secuencia 2: " << nueva_secuencia_2 << endl;

		cout << "antes del if" <<matchresult<< endl;
		if (nuevo1 == true && nuevo2 == true)
		{
			//cout << "nueva secuencia2:  " << nueva_secuencia_2 << endl;
			//cout << "nueva secuencia 1" << nueva_secuencia_1 << endl;

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
	//Vetor con las imagenes comparativas
	vector<Mat> letras;
	Mat letra_A,letra_B, letra_C, letra_D, letra_E, letra_F, letra_G, letra_H, letra_I, letra_J, letra_K, letra_L, letra_M, letra_N, letra_O, letra_P, letra_Q, letra_R, letra_S, letra_T, letra_U, letra_V, letra_W, letra_X, letra_Y, letra_Z;
	letra_A= imread("A.JPG", CV_LOAD_IMAGE_GRAYSCALE);
	letras.push_back(letra_A);
	letra_B= imread("B.JPG", CV_LOAD_IMAGE_GRAYSCALE);
	letras.push_back(letra_B);
	letra_C = imread("C.JPG", CV_LOAD_IMAGE_GRAYSCALE);
	letras.push_back(letra_C);
	letra_D = imread("D.JPG", CV_LOAD_IMAGE_GRAYSCALE);
	letras.push_back(letra_D);
	letra_E = imread("E.JPG", CV_LOAD_IMAGE_GRAYSCALE);
	letras.push_back(letra_E);
	letra_F = imread("F.JPG", CV_LOAD_IMAGE_GRAYSCALE);
	letras.push_back(letra_F);
	letra_G = imread("G.JPG", CV_LOAD_IMAGE_GRAYSCALE);
	letras.push_back(letra_G);
	letra_H = imread("H.JPG", CV_LOAD_IMAGE_GRAYSCALE);
	letras.push_back(letra_H);
	letra_I = imread("I.JPG", CV_LOAD_IMAGE_GRAYSCALE);
	letras.push_back(letra_I);
	letra_J = imread("J.JPG", CV_LOAD_IMAGE_GRAYSCALE);
	letras.push_back(letra_J);
	letra_K = imread("K.JPG", CV_LOAD_IMAGE_GRAYSCALE);
	letras.push_back(letra_K);
	letra_L = imread("L.JPG", CV_LOAD_IMAGE_GRAYSCALE);
	letras.push_back(letra_L);
	letra_M = imread("M.JPG", CV_LOAD_IMAGE_GRAYSCALE);
	letras.push_back(letra_M);
	letra_N = imread("N.JPG", CV_LOAD_IMAGE_GRAYSCALE);
	letras.push_back(letra_N);
	letra_O = imread("O.JPG", CV_LOAD_IMAGE_GRAYSCALE);
	letras.push_back(letra_O);
	letra_P = imread("P.JPG", CV_LOAD_IMAGE_GRAYSCALE);
	letras.push_back(letra_P);
	letra_Q = imread("Q.JPG", CV_LOAD_IMAGE_GRAYSCALE);
	letras.push_back(letra_Q);
	letra_R = imread("R.JPG", CV_LOAD_IMAGE_GRAYSCALE);
	letras.push_back(letra_R);
	letra_S = imread("S.JPG", CV_LOAD_IMAGE_GRAYSCALE);
	letras.push_back(letra_S);
	letra_T = imread("T.JPG", CV_LOAD_IMAGE_GRAYSCALE);
	letras.push_back(letra_T);
	letra_U = imread("U.JPG", CV_LOAD_IMAGE_GRAYSCALE);
	letras.push_back(letra_U);
	letra_V = imread("V.JPG", CV_LOAD_IMAGE_GRAYSCALE);
	letras.push_back(letra_V);
	letra_W = imread("W.JPG", CV_LOAD_IMAGE_GRAYSCALE);
	letras.push_back(letra_W);
	letra_X = imread("X.JPG", CV_LOAD_IMAGE_GRAYSCALE);
	letras.push_back(letra_X);
	letra_Y = imread("Y.JPG", CV_LOAD_IMAGE_GRAYSCALE);
	letras.push_back(letra_Y);
	letra_Z = imread("Z.JPG", CV_LOAD_IMAGE_GRAYSCALE);
	letras.push_back(letra_Z);

	//Vector con las imagenes de resultado
	vector<Mat> resultados;
	Mat res_A, res_B, res_C, res_D, res_E, res_F, res_G, res_H, res_I, res_J, res_K, res_L, res_M, res_N, res_O, res_P, res_Q, res_R, res_S, res_T, res_U, res_V, res_W, res_X, res_Y, res_Z;
	res_A = imread("resultado_A.jpg", CV_LOAD_IMAGE_COLOR);
	resultados.push_back(res_A);
	res_B = imread("resultado_B.jpg", CV_LOAD_IMAGE_COLOR);
	resultados.push_back(res_B);
	res_C = imread("resultado_C.jpg", CV_LOAD_IMAGE_COLOR);
	resultados.push_back(res_C);
	res_D = imread("resultado_D.jpg", CV_LOAD_IMAGE_COLOR);
	resultados.push_back(res_D);
	res_E = imread("resultado_E.jpg", CV_LOAD_IMAGE_COLOR);
	resultados.push_back(res_E);
	res_F = imread("resultado_F.jpg", CV_LOAD_IMAGE_COLOR);
	resultados.push_back(res_F);
	res_G = imread("resultado_G.jpg", CV_LOAD_IMAGE_COLOR);
	resultados.push_back(res_G);
	res_H = imread("resultado_H.jpg", CV_LOAD_IMAGE_COLOR);
	resultados.push_back(res_H);
	res_I = imread("resultado_I.jpg", CV_LOAD_IMAGE_COLOR);
	resultados.push_back(res_I);
	res_J = imread("resultado_J.jpg", CV_LOAD_IMAGE_COLOR);
	resultados.push_back(res_J);
	res_K = imread("resultado_K.jpg", CV_LOAD_IMAGE_COLOR);
	resultados.push_back(res_K);
	res_L = imread("resultado_L.jpg", CV_LOAD_IMAGE_COLOR);
	resultados.push_back(res_L);
	res_M = imread("resultado_M.jpg", CV_LOAD_IMAGE_COLOR);
	resultados.push_back(res_M);
	res_N = imread("resultado_N.jpg", CV_LOAD_IMAGE_COLOR);
	resultados.push_back(res_N);
	res_O = imread("resultado_O.jpg", CV_LOAD_IMAGE_COLOR);
	resultados.push_back(res_O);
	res_P = imread("resultado_P.jpg", CV_LOAD_IMAGE_COLOR);
	resultados.push_back(res_P);
	res_Q = imread("resultado_Q.jpg", CV_LOAD_IMAGE_COLOR);
	resultados.push_back(res_Q);
	res_R = imread("resultado_R.jpg", CV_LOAD_IMAGE_COLOR);
	resultados.push_back(res_R);
	res_S = imread("resultado_S.jpg", CV_LOAD_IMAGE_COLOR);
	resultados.push_back(res_S);
	res_T = imread("resultado_T.jpg", CV_LOAD_IMAGE_COLOR);
	resultados.push_back(res_T);
	res_U = imread("resultado_U.jpg", CV_LOAD_IMAGE_COLOR);
	resultados.push_back(res_U);
	res_V = imread("resultado_V.jpg", CV_LOAD_IMAGE_COLOR);
	resultados.push_back(res_V);
	res_W = imread("resultado_W.jpg", CV_LOAD_IMAGE_COLOR);
	resultados.push_back(res_W);
	res_X = imread("resultado_X.jpg", CV_LOAD_IMAGE_COLOR);
	resultados.push_back(res_X);
	res_Y = imread("resultado_Y.jpg", CV_LOAD_IMAGE_COLOR);
	resultados.push_back(res_Y);
	res_Z = imread("resultado_Z.jpg", CV_LOAD_IMAGE_COLOR);
	resultados.push_back(res_Z);
	
	//Comenzamos captura
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
	
	int count = 0;
	CvPoint pt1, pt2;

	while (1) {
		bool b = cam.read(img);
		if (!b) {
			cout << "ERROR : cannot read" << endl;
			return -1;
		}
		Rect roi(100, 100, 270, 270);
		rectangle(img, roi, 2, 10, 8);
		imshow("Original_image", img);
		img_roi = img(roi);

		//Capturamos la imagen del signo
		if (waitKey(30) == 27) {
			capturada = img_roi.clone();
			//Binarizamos y filtramos la imagen
			cvtColor(capturada, img_gray, CV_RGB2GRAY);
			GaussianBlur(img_gray, img_gray, Size(19, 19), 0.0, 0);
			threshold(img_gray, img_threshold, 127, 255, THRESH_BINARY);
			
			double menor_coincidencia = 1.8;
			int index;
			bool encontrado=false;
			//Comparamos la imagen con los signos acumlados
			for (int i = 0; i<letras.size(); i++)
			{
				//acumular coincidencia para comprobar cual es la mayor
				coincidencia = comparar(letras[i],img_threshold);
				
				if (coincidencia < menor_coincidencia)
				{
					menor_coincidencia = coincidencia;
					index = i;
					if ((menor_coincidencia < 1.8) && (menor_coincidencia != 0)) encontrado = true;
					else encontrado = false;
				}
			}

			if(encontrado)
			{
				imshow("Resultado", resultados[index]);
			} else cvDestroyWindow( "Resultado");
			imshow("Original_image", capturada);
			imshow("Threshold", img_threshold);

		}
	}
				return 0;
		}
