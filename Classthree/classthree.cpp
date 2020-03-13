#include <opencv2/opencv.hpp>
#include <iostream>
#include <stdio.h>

using namespace cv;
using namespace std;

Scalar fu_l = Scalar(0, 1, 50);		//肤色最小值
Scalar fu_h = Scalar(20, 255, 255);  //肤色最大值

string window_name = "result";

void img_threshold(int th,void* data)  //二值化回调函数
{
	Mat src = *(Mat*)(data);
	Mat result;
	threshold(src, result, th, 255, THRESH_BINARY);
	imshow(window_name, result);
	//waitKey(0);
}

void img_adaptiveThreshold(Mat src)		//自适应二值化
{
	Mat result2;
	adaptiveThreshold(src, result2, 255, ADAPTIVE_THRESH_GAUSSIAN_C, THRESH_BINARY_INV, 5, 10);
	imshow("result2", result2);
	waitKey(0);
}

int main()
{
	int lowTH = 30;
	int higTH = 255;
	Mat src = imread("IMG_6145.jpg");
	Mat gray;
	cvtColor(src, gray, COLOR_BGR2GRAY);
	resize(gray, gray, Size(500, 500));
	img_adaptiveThreshold(gray);
	imshow(window_name, gray);
	createTrackbar("threshlod", window_name, &lowTH, higTH, img_threshold, &gray);
	waitKey(0);

	VideoCapture capture(0);		
	while (1)
	{
		Mat frame;
		Mat frame_hsv;
		Mat dst;
		capture>>frame;
		cvtColor(frame, frame_hsv, COLOR_BGR2HSV);
		inRange(frame_hsv, fu_l, fu_h, dst);
		imshow("dst", dst);
		imshow("frame", frame);
		waitKey(30);
	}
	return 0;
}