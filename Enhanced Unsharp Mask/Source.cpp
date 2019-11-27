
#include "opencv2/highgui.hpp"
#include <iostream>
#include <opencv2/opencv.hpp>
#include <vector>

using namespace cv;
using namespace std;

int main(int argc, const char** argv)
{
	Mat img = imread("AlbertEinstein.jpg", CV_LOAD_IMAGE_UNCHANGED);
	//load image
	img.convertTo(img, CV_32FC1, 1.0 / 255.0);
	//convert img to floating point matrix
	cout << img.type() << endl;
	Mat bilateral;
	bilateralFilter(img, bilateral, 0, 0.3, 1);
	imshow(“bilateral”, bilateral);
	Mat gaussian_blur;
	gaussian_blur.convertTo(gaussian_blur, CV_32FC1);
	//convert gaussian blur to floating point matrix
	GaussianBlur(img, gaussian_blur, Size(5, 5), 0, 0);
	//set gaussian blur
	imshow("gaussian blur", gaussian_blur);
	//show gaussian blur image
	double scalar = 1;
	//set scalar to multiply detail by x
	Mat detail;
	detail.convertTo(detail, CV_32FC1);
	//change detail to floating point matrix to store negative values
	detail = scalar * (img - gaussian_blur);
	//subtract gaussian from original to obtain detail
	imshow("detail", detail);
	//show detail
	Mat unsharp = detail + gaussian_blur;
	//add detail to gaussian blur to obtain the unsharp mask
	imshow("unsharpMask", unsharp);
	//show unsharpmask

	gaussian_blur.convertTo(gaussian_blur, CV_8UC3, 255);
	imwrite("/Users/puppy/OneDrive/Pictures/STARS/Unsharp Mask/motherBlur.bmp", gaussian_blur);
	//save gaussian blur to drive
	detail.convertTo(detail, CV_8UC3, 255);
	imwrite("/Users/puppy/OneDrive/Pictures/STARS/Unsharp Mask/motherdetail.bmp", detail);
	//save detail to drive
	unsharp.convertTo(unsharp, CV_8UC3, 255);
	imwrite("/Users/puppy/OneDrive/Pictures/STARS/Unsharp Mask/motherunsharp.bmp", unsharp);
	//save unsharpmask to drive

	if (img.empty())
	{
		cout << "Error: Image cannot be loaded..!!" << endl;
		system("pause");
		return -1;
	}
	//failsafe allowing user to know if error results from inability to load image
	namedWindow("MyWindow", CV_WINDOW_AUTOSIZE);
	imshow("MyWindow", img);
	//show original image
	waitKey(0);
	//wait for key press to destroy window
	destroyWindow("MyWindow");
	return 0;
}
