#include <vector>

#include "opencv2\opencv.hpp"
#include <stdio.h>
#include <iostream>

using namespace std;

//Releaseモードの場合
#pragma comment(lib, "zlib.lib")
#pragma comment(lib, "IlmImf.lib")
#pragma comment(lib, "libjasper.lib")
#pragma comment(lib, "libjpeg.lib")
#pragma comment(lib, "libpng.lib")
#pragma comment(lib, "libtiff.lib")


#pragma comment(lib, "opencv_calib3d2412.lib")
#pragma comment(lib, "opencv_contrib2412.lib")
#pragma comment(lib, "opencv_core2412.lib")
#pragma comment(lib, "opencv_features2d2412.lib")
#pragma comment(lib, "opencv_flann2412.lib")
#pragma comment(lib, "opencv_gpu2412.lib")
#pragma comment(lib, "opencv_highgui2412.lib")
#pragma comment(lib, "opencv_imgproc2412.lib")
#pragma comment(lib, "opencv_legacy2412.lib")
#pragma comment(lib, "opencv_ml2412.lib")
#pragma comment(lib, "opencv_nonfree2412.lib")
#pragma comment(lib, "opencv_objdetect2412.lib")
#pragma comment(lib, "opencv_ocl2412.lib")
#pragma comment(lib, "opencv_photo2412.lib")
#pragma comment(lib, "opencv_stitching2412.lib")
#pragma comment(lib, "opencv_superres2412.lib")
#pragma comment(lib, "opencv_ts2412.lib")
#pragma comment(lib, "opencv_video2412.lib")
#pragma comment(lib, "opencv_videostab2412.lib")
// --------------------------------------------------------------------------
// main(Number of arguments, Argument values)
// Description  : This is the entry point of the program.
// Return value : SUCCESS:0  ERROR:-1
// --------------------------------------------------------------------------
void doORB(char *filenameA, char *filenameB) {

	cv::Mat imgA = cv::imread(filenameA);
	cv::Mat imgB = cv::imread(filenameB);

	// ORB
	cv::OrbFeatureDetector detector;
	cv::OrbDescriptorExtractor extractor;

	// 特徴量抽出
	cv::Mat descriptorsA, descriptorsB;
	std::vector<cv::KeyPoint> keypointsA, keypointsB;
	int64 last = cv::getTickCount();
	detector.detect(imgA, keypointsA);
	detector.detect(imgB, keypointsB);
	// printf("detection = %f[s]\n", (cv::getTickCount() - last)/cv::getTickFrequency());
	last = cv::getTickCount();
	extractor.compute(imgA, keypointsA, descriptorsA);
	extractor.compute(imgB, keypointsB, descriptorsB);
	// printf("description = %f[s]\n", (cv::getTickCount() - last)/cv::getTickFrequency());

	// マッチング
	std::vector<cv::DMatch> matches;
	cv::BFMatcher matcher(cv::NORM_L1, true);
	matcher.match(descriptorsA, descriptorsB, matches);

	// 最小距離
	double min_dist = DBL_MAX;
	for (int i = 0; i < (int)matches.size(); i++){
		double dist = matches[i].distance;
		if (dist < min_dist) min_dist = dist;
	}
	if (min_dist < 1.0) min_dist = 1.0;

	// 良いペアのみ残す
	const double threshold = 3.0 * min_dist;
	std::vector<cv::DMatch> matches_good;
	std::vector<int> matches_ix;

	for (int i = 0; i < (int)matches.size(); i++) {
		if (matches[i].distance < threshold) {
			matches_good.push_back(matches[i]);

			matches_ix.push_back(i);
		}
	}
	std::cout << matches_good.size() << std::endl;

	cout << "keypointsA" << endl;
	for each(auto i in matches_ix) {
		cout << "x:" << keypointsA[i].pt.x << "," << "y:" << keypointsA[i].pt.y << endl;
	}
	for each(auto i in matches_ix) {
		cout << "x:" << keypointsB[i].pt.x << "," << "y:" << keypointsB[i].pt.y << endl;
	}



	// 表示
	cv::Mat matchImage;
	cv::drawMatches(imgA, keypointsA, imgB, keypointsB, matches_good, matchImage, cv::Scalar::all(-1), cv::Scalar::all(-1), std::vector<char>(), cv::DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS);
	cv::imshow("比較", matchImage);
	cv::waitKey(0);


}



int main(int argc, char **argv)
{
	if (argc < 3) {
		return -1;
	}

	doORB(argv[1], argv[2]);

	return 0;
}
