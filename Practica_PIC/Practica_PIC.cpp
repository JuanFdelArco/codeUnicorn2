

#include "stdafx.h"
#include "opencv2/imgproc/imgproc.hpp"
#include <opencv2/highgui/highgui.hpp>
#include <iostream>


using namespace cv;
using namespace std;

bool cwComp(Point p1, Point p2) {
	return p1.x < p2.x;
}

void displayGesture(Mat frame, int feature[]) {
	char result[2] = "?";
	int b0 = feature[0];
	int b1 = feature[1];
	int b2 = feature[2];
	int b3 = feature[3];
	int b4 = feature[4];
	if (b0 == 0 && b1 == 0 && b2 == 0 && b3 == 1 && b4 == 0)
		result[0] = 'A';
	else if (b0 == 0 && b1 == 0 && b2 == 1 && b3 == 0 && b4 == 0)
		result[0] = 'B';
	else if (b0 == 0 && b1 == 0 && b2 == 1 && b3 == 1 && b4 == 0)
		result[0] = 'C';
	else if (b0 == 1 && b1 == 0 && b2 == 0 && b3 == 1 && b4 == 0)
		result[0] = 'D';
	else if (b0 == 1 && b1 == 0 && b2 == 0 && b3 == 1 && b4 == 1)
		result[0] = 'E';
	else if (b0 == 0 && b1 == 1 && b2 == 1 && b3 == 0 && b4 == 0)
		result[0] = 'F';
	else if (b0 == 0 && b1 == 1 && b2 == 0 && b3 == 1 && b4 == 0)
		result[0] = 'G';
	else if (b0 == 1 && b1 == 0 && b2 == 1 && b3 == 0 && b4 == 0)
		result[0] = 'H';
	else if (b0 == 1 && b1 == 1 && b2 == 0 && b3 == 0 && b4 == 0)
		result[0] = 'I';
	else if (b0 == 0 && b1 == 1 && b2 == 1 && b3 == 1 && b4 == 0)
		result[0] = 'J';
	else if (b0 == 1 && b1 == 1 && b2 == 1 && b3 == 0 && b4 == 0)
		result[0] = 'K';
	else if (b0 == 1 && b1 == 1 && b2 == 0 && b3 == 1 && b4 == 0)
		result[0] = 'L';
	else if (b0 == 1 && b1 == 0 && b2 == 1 && b3 == 1 && b4 == 0)
		result[0] = 'M';
	else if (b0 == 1 && b1 == 1 && b2 == 1 && b3 == 1 && b4 == 0)
		result[0] = 'N';
	else if (b0 == 0 && b1 == 0 && b2 == 0 && b3 == 1 && b4 == 1)
		result[0] = 'O';
	else if (b0 == 0 && b1 == 0 && b2 == 1 && b3 == 1 && b4 == 1)
		result[0] = 'P';
	else if (b0 == 0 && b1 == 1 && b2 == 1 && b3 == 1 && b4 == 1)
		result[0] = 'Q';
	else if (b0 == 1 && b1 == 1 && b2 == 1 && b3 == 1 && b4 == 1)
		result[0] = 'R';
	else if (b0 == 1 && b1 == 1 && b2 == 0 && b3 == 1 && b4 == 1)
		result[0] = 'S';
	else if (b0 == 1 && b1 == 0 && b2 == 1 && b3 == 1 && b4 == 1)
		result[0] = 'T';
	else if (b0 == 1 && b1 == 1 && b2 == 1 && b3 == 0 && b4 == 1)
		result[0] = 'U';
	else if (b0 == 1 && b1 == 1 && b2 == 0 && b3 == 0 && b4 == 1)
		result[0] = 'V';
	else if (b0 == 1 && b1 == 0 && b2 == 1 && b3 == 0 && b4 == 1)
		result[0] = 'W';
	else if (b0 == 0 && b1 == 0 && b2 == 1 && b3 == 0 && b4 == 1)
		result[0] = 'X';
	//TO DO: similarly for other results...

	putText(frame, result, Point(frame.cols - 100, 80), FONT_HERSHEY_SIMPLEX, 1, Scalar(255, 0, 0), 4);
}


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
		Rect roi(340, 100, 200, 200);

		rectangle(img, roi, 2, 10, 8);

		imshow("Original_image", img);

		img_roi = img(roi);



		if (waitKey(30) == 27) {
			capturada = img_roi.clone();
			cvtColor(capturada, img_gray, CV_RGB2GRAY);
			GaussianBlur(img_gray, img_gray, Size(19, 19), 0.0, 0);

			//Canny(img_gray, img_threshold, 50, 150, 3);
			threshold(img_gray, img_threshold, 127, 255, THRESH_BINARY_INV + THRESH_OTSU);
			//imshow("Thresholded_image", img_threshold);

			//Mat se = getStructuringElement(MORPH_ELLIPSE, Size(3, 3));
			//dilate(img_threshold, img_threshold, se);
			//imshow("Canny_image", img_threshold);

			int orientation = 0;
			for (int i = 0; i < img_threshold.cols; i++) {
				if (img_threshold.at<uchar>(img_threshold.rows - 1, i) > 0) {
					orientation = 0;
					break;
				}
				else if (img_threshold.at<uchar>(i, img_threshold.cols - 1) > 0) {
					orientation = 1;
					break;
				}
			}

			float cx = 0.0, cy = 0.0;
			float sumi = 1.0;
			for (int i = 0; i < img_threshold.rows; i++) {
				for (int j = 0; j < img_threshold.cols; j++) {
					cy += img_threshold.at<uchar>(i, j) * i;
					cx += img_threshold.at<uchar>(i, j) * j;
					sumi += img_threshold.at<uchar>(i, j);
				}
			}
			cx /= sumi;
			cy /= sumi;

			vector<vector<Point> >contours;
			vector<Vec4i>hierarchy;
			Mat temp = img_threshold.clone();
			findContours(temp, contours, hierarchy, RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point());
			int c_size = 0, c_idx = 0;
			for (int i = 0; i < contours.size(); i++) {
				if (contours.size() > c_size) {
					c_idx = i;
					c_size = contours.size();
				}
			}

			vector<Point> boundary0;
			vector<Point> peaks_;
			if (!contours.empty()) {
				boundary0 = contours[c_idx];
			}

			vector<Point> boundary;
			if (!boundary0.empty()) {
				approxPolyDP(boundary0, boundary, 2, false);

				for (int i = 0; i < boundary.size(); i++) {
					circle(capturada, boundary[i] + Point(roi.x, roi.y), 5, Scalar(100, 200, 100));
				}
			}

			//imshow("Contours_image", img_threshold);
			//imshow("Gray_image", img_gray);
			//imshow("ROI", capturada);

			vector<Point> peaks0;
			for (int i = 0; i < peaks_.size(); i++) {
				int nexti = (i + 1) % peaks_.size();
				if (abs(peaks_[i].y - peaks_[nexti].y) < 15 && abs(peaks_[i].x - peaks_[nexti].x) < 15) {
					continue;
				}
				peaks0.push_back(peaks_[i]);
			}

			if (orientation == 0) {
				for (int i = 0; (i + 1) < boundary.size(); i++) {
					Point p = boundary[i];
					if (cy > p.y) {
						bool isPeak = true;
						int indxl = (i - 1) % boundary.size();
						int indxr = (i + 1) % boundary.size();
						if (boundary[indxl].y < p.y || boundary[indxr].y < p.y) {
							isPeak = false;
						}
						if (isPeak) {
							peaks_.push_back(p);
							//circle(frame, p+Point(roi_.x, roi_.y), 20, Scalar(255, 0, 0));
						}
					}
				}


				vector<Point> peaks0;
				for (int i = 0; i < peaks_.size(); i++) {
					int nexti = (i + 1) % peaks_.size();
					if (abs(peaks_[i].y - peaks_[nexti].y) < 15 && abs(peaks_[i].x - peaks_[nexti].x) < 15) {
						continue;
					}
					peaks0.push_back(peaks_[i]);
					circle(capturada, peaks_[i] + Point(roi.x, roi.y), 20, Scalar(0, 0, 255));
				}

				int feature[5];
				bool detected = false;

				//convert peaks into feature vector of raised and folded fingers
				sort(peaks0.begin(), peaks0.end(), cwComp); //arrange peaks in clockwise manner;
				if (peaks0.size() == 4) {
					//detect thumb by measuring the compactness of the thumb portion of the palm
					Rect thumbRect(0, cy, roi.width, roi.height - cy);
					Mat thumbRoi = img_threshold(thumbRect);
					vector<Vec4i> tHeirachy;
					vector< vector<Point> > thumbContours;
					temp = thumbRoi.clone();
					findContours(temp, thumbContours, tHeirachy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE);
					int tc_size = 0, tc_idx = 0;
					for (int i = 0; i < thumbContours.size(); i++) {
						if (thumbContours.size() > tc_size) {
							tc_idx = i;
							tc_size = thumbContours.size();
						}
					}

					vector<Point> tboundary0;
					if (!thumbContours.empty()) {
						tboundary0 = thumbContours[tc_idx];
					}
					double perimeter = arcLength(tboundary0, true);
					double area = contourArea(tboundary0);
					double compactness = perimeter*perimeter / (4 * 3.14*area);
					double distArray[4];
					//cout<<"[ ";
					for (int i = 0; i < peaks0.size(); i++) {
						//	cout<<peaks0[i].y<<" ";
						distArray[i] = sqrt((cy - peaks0[i].y)*(cy - peaks0[i].y) + (cx - peaks0[i].x)*(cx - peaks0[i].x));
					}

					double max = 0.0;
					for (int i = 0; i < 4; i++) {
						if (distArray[i] > max)
							max = distArray[i];
					}
					feature[4] = compactness > 1.8 ? 1 : 0;
					for (int i = 0; i < 4; i++) {
						if (distArray[i] > 0.75*max)
							feature[i] = 1;
						else
							feature[i] = 0;
					}
					for (int i = 0; i < 5; i++) {
						//	cout<<feature[i]<<" ";
					}
					//cout<<"]\n";
					detected = true;


				}

				if (detected) {
					displayGesture(capturada, feature);
				}
				else {
					putText(capturada, "Waiting for sign...", Point(capturada.cols - 200, 80), FONT_HERSHEY_SIMPLEX, 0.5, Scalar(0, 0, 255));
				}

				line(capturada, Point(roi.x, cy + roi.y), Point(roi.x + roi.width, cy + roi.y), Scalar(0, 255, 0), 2);
			}




			line(img, Point(cx + roi.x, cy + roi.y), Point(cx + roi.x, cy + roi.y), Scalar(0, 0, 255), 5); //centroid
			rectangle(img, roi, Scalar(255, 0, 0), 2); //roi of the palm
			imshow("Threshold", img_threshold);
			imshow("Resultado", capturada);
			//imshow("roi", roi);






		}

	}
	return 0;

}
