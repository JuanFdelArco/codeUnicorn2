

#include "stdafx.h"
#include "opencv2/imgproc/imgproc.hpp"
#include <opencv2/highgui/highgui.hpp>
#include <iostream>


using namespace cv;
using namespace std;

int main(int argc, const char** argv)
{


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

	namedWindow("Original_image", CV_WINDOW_AUTOSIZE);
	namedWindow("Gray_image", CV_WINDOW_AUTOSIZE);
	namedWindow("Thresholded_image", CV_WINDOW_AUTOSIZE);
	namedWindow("ROI", CV_WINDOW_AUTOSIZE);
	char a[40];
	int count = 0;
	CvPoint pt1, pt2;

	while (1) {
		bool b = cam.read(img);
		if (!b) {
			cout << "ERROR : cannot read" << endl;
			return -1;
		}
		Rect roi(340, 100, 270, 270);
	    
		rectangle(img, roi,2,10,8);
		
		imshow("Original_image", img);
		
		img_roi = img(roi);



		if (waitKey(30) == 27) {
			capturada = img_roi;
			cvtColor(capturada, img_gray, CV_RGB2GRAY);
			GaussianBlur(img_gray, img_gray, Size(19, 19), 0.0, 0);

			
			threshold(img_gray, img_threshold, 0, 255, THRESH_BINARY_INV + THRESH_OTSU);
			imshow("Thresholded_image", img_threshold);
			Canny(img_threshold, img_threshold, 50, 150,3);
			imshow("Canny_image", img_threshold);

			vector<vector<Point> >contours;
			vector<Vec4i>hierarchy;
			
			findContours(img_threshold, contours, hierarchy, RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point());
			imshow("Contours_image", img_threshold);
			imshow("Gray_image", img_gray);
			imshow("ROI", capturada);
			

		}

	}
	
	return 0;
}

