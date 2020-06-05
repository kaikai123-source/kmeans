
#include<opencv2\opencv.hpp>
#include<opencv2\core.hpp>
#include<iostream>

using namespace cv;
using namespace std;
int createMaskByKmeans(Mat src, Mat mask) {
	int width = src.cols;
	int height = src.rows;
	int pixNum = width*height;
	int clusterCount = 2;
	Mat  labels;
	Mat centers;

	Mat sampleData = src.reshape(3, pixNum);
	Mat km_data;
	sampleData.convertTo(km_data, CV_32F);
	TermCriteria criteria = TermCriteria(TermCriteria::EPS + TermCriteria::COUNT, 10, 0.1);
	kmeans(km_data, clusterCount, labels, criteria, clusterCount, KMEANS_PP_CENTERS, centers);
	uchar fg[2] = { 0,255 };
	for (int row = 0; row < height; row++) {
		for (int col = 0; col < width; col++) {
			mask.at<uchar>(row, col) = fg[labels.at<int>(row*width + col)];
		}
	}
	return 0;
}
void segColor() {
	Mat src = imread("D:\\movie.jpg");
	Mat mask(src.size(), CV_8UC1);
	for (int i = 0; i < src.rows; i++)
	{
		uchar *p = src.ptr<uchar>(i);
		for (int j = 0; j < src.cols; j++)
		{
			p[j] = 0;
		}
	}
	createMaskByKmeans(src, mask);
	imshow("src", src);
	imshow("dst", mask);
	waitKey(0);
}

int main() {
	segColor();
}
