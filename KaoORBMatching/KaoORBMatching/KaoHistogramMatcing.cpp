#include <vector>

#include "opencv2\opencv.hpp"
#include <stdio.h>
#include <iostream>

extern cv::Mat DoubtfulA;
extern cv::Mat DoubtfulB;


int KaoHistgramMatcing(char *filenameA, char *filenameB) {
	IplImage *src1 = 0, *src2 = 0;
	IplImage *dst1[4] = { 0, 0, 0, 0 }, *dst2[4] = { 0, 0, 0, 0 };
	CvHistogram *hist1, *hist2;
	int sch1 = 0, sch2 = 0;
	int hist_size = 256;
	float range_0[] = { 0, 256 };
	float *ranges[] = { range_0 };

	IplImage dfA, dfB;
	dfA = DoubtfulA;
	dfB = DoubtfulB;
	src1 = &dfA; // cvLoadImage(filenameA, CV_LOAD_IMAGE_COLOR);
	src2 = &dfB; // cvLoadImage(filenameB, CV_LOAD_IMAGE_COLOR);
	if (src1 == 0 || src2 == 0){
		return -1;
	}

	sch1 = src1->nChannels;
	sch2 = src2->nChannels;
	if (sch1 != sch2){
		return -1;
	}

	for (int i = 0; i<sch1; i++) {
		dst1[i] = cvCreateImage(cvSize(src1->width, src1->height), src1->depth, 1);
		dst2[i] = cvCreateImage(cvSize(src2->width, src2->height), src2->depth, 1);
	}

	//ヒストグラム構造体を確保
	hist1 = cvCreateHist(1, &hist_size, CV_HIST_ARRAY, ranges, 1);
	hist2 = cvCreateHist(1, &hist_size, CV_HIST_ARRAY, ranges, 1);

	//入力画像がマルチチャンネルの場合，画像をチャンネル毎に分割
	if (sch1 == 1) {
		cvCopy(src1, dst1[0], NULL);
		cvCopy(src2, dst2[0], NULL);
	}
	else{
		cvSplit(src1, dst1[0], dst1[1], dst1[2], dst1[3]);
		cvSplit(src2, dst2[0], dst2[1], dst2[2], dst2[3]);
	}
	//ヒストグラムの計算
	for (int i = 0; i<sch1; i++){
		cvCalcHist(&dst1[i], hist1, 0, NULL);
		cvCalcHist(&dst2[i], hist2, 0, NULL);
		cvNormalizeHist(hist1, 1.0);
		cvNormalizeHist(hist2, 1.0);
	}
	printf("ヒストグラム:\n");
	// printf("Correlation : %f\n", cvCompareHist(hist1, hist2, CV_COMP_CORREL));
	// printf("Chi-square : %f\n", cvCompareHist(hist1, hist2, CV_COMP_CHISQR));
	printf("ヒストグラム交差 : %f\n", cvCompareHist(hist1, hist2, CV_COMP_INTERSECT));
	printf("バタチャリヤ距離 : %f\n", cvCompareHist(hist1, hist2, CV_COMP_BHATTACHARYYA));

	// マッチの基準
	if (cvCompareHist(hist1, hist2, CV_COMP_INTERSECT) > 0.8 &&
		cvCompareHist(hist1, hist2, CV_COMP_BHATTACHARYYA) < 0.2) {
		return 2;
	}
	else if (cvCompareHist(hist1, hist2, CV_COMP_INTERSECT) > 0.6 &&
		cvCompareHist(hist1, hist2, CV_COMP_BHATTACHARYYA) < 0.4) {
		return 1;
	}
	return 0;
	/*
	•Correlationを用いると
	結果が高いほうがよりマッチしている
	完璧なマッチだった場合は1
	完璧なミスマッチの場合は-1

	•Chi-squareを用いると
	結果が低いほうがよりマッチしている
	完璧なマッチだった場合は0
	完璧なミスマッチだった場合は際限のない値が得られる(ヒストグラムのサイズに依存する)

	•Intersectionを用いると
	結果が高いほうがよりマッチしている
	ヒストグラムが1にノーマライズされている場合
	完璧なマッチだった場合は1
	完璧なミスマッチだった場合は0


	•Bhattacharyya distanceを用いると ◦結果が低いほうがよりマッチしている
	完璧なマッチだった場合は0
	完璧なミスマッチだった場合は1
	*/

}