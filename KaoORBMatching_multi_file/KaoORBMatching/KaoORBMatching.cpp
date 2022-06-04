#include <vector>

#include "opencv2\opencv.hpp"
#include <stdio.h>
#include "shlwapi.h"
#include <iostream>

using namespace std;

// PathFileExists
#pragma comment(lib, "shlwapi.lib")

//Release���[�h�̏ꍇ
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
#define TMPL_W 320
#define TMPL_H 400

#define ORB_LOOSE_THRESHOLD 2

cv::Mat DoubtfulA;
cv::Mat DoubtfulB;

int doORB(char *filenameA, char *filenameB) {
	// �N���A����
	cv::Mat dummyA;
	cv::Mat dummyB;
	DoubtfulA = dummyA.clone();
	DoubtfulB = dummyB.clone();

	//------------------------------------------------------------------------------------------------------------------------
	// �摜�ǂݍ��݁` �����_�v�Z�܂�
	cv::Mat imgA = cv::imread(filenameA);
	cv::Mat imgB = cv::imread(filenameB);

	// ORB
	cv::OrbFeatureDetector detector;
	cv::OrbDescriptorExtractor extractor;

	// �����ʒ��o
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

	// �}�b�`���O
	std::vector<cv::DMatch> matches;
	cv::BFMatcher matcher(cv::NORM_L1, true);
	matcher.match(descriptorsA, descriptorsB, matches);

	// �ŏ�����
	double min_dist = DBL_MAX;
	for (int i = 0; i < (int)matches.size(); i++){
		double dist = matches[i].distance;
		if (dist < min_dist) min_dist = dist;
	}
	if (min_dist < 1.0) min_dist = 1.0;

	// �ǂ��y�A�̂ݎc��
	const double threshold = ORB_LOOSE_THRESHOLD * min_dist;
	std::vector<cv::DMatch> matches_good;
	std::vector<int> matches_ix;

	// �܂��͌��I�Ń`�������W
	for (int i = 0; i < (int)matches.size(); i++) {
		if (matches[i].distance < threshold) {
			matches_good.push_back(matches[i]);

			matches_ix.push_back(i);

	//		cout << keypointsA[i].pt.x << "," << keypointsA[i].pt.y << " - " << keypointsB[i].pt.x << "," << keypointsB[i].pt.y << endl;
		}
	}
	// std::cout << matches_good.size() << std::endl;

	// ������Ȃ������炿����Ɗɂ߂�
	if (matches_good.size() <= 5) {

		matches_good.clear();
		matches_ix.clear();

		for (int i = 0; i < (int)matches.size(); i++) {
			if (matches[i].distance < threshold * 1.5) {
				matches_good.push_back(matches[i]);

				matches_ix.push_back(i);

				//		cout << keypointsA[i].pt.x << "," << keypointsA[i].pt.y << " - " << keypointsB[i].pt.x << "," << keypointsB[i].pt.y << endl;
			}
		}
	}

	// �܂�����Ȃ������炳��Ɋɂ߂�
	if (matches_good.size() <= 5) {

		matches_good.clear();
		matches_ix.clear();

		for (int i = 0; i < (int)matches.size(); i++) {
			if (matches[i].distance < threshold * 2) {
				matches_good.push_back(matches[i]);

				matches_ix.push_back(i);

				//		cout << keypointsA[i].pt.x << "," << keypointsA[i].pt.y << " - " << keypointsB[i].pt.x << "," << keypointsB[i].pt.y << endl;
			}
		}
	}

	// �܂�����Ȃ������炳��Ɋɂ߂�
	if (matches_good.size() <= 5) {

		matches_good.clear();
		matches_ix.clear();

		for (int i = 0; i < (int)matches.size(); i++) {
			if (matches[i].distance < threshold * 2.5) {
				matches_good.push_back(matches[i]);

				matches_ix.push_back(i);

				//		cout << keypointsA[i].pt.x << "," << keypointsA[i].pt.y << " - " << keypointsB[i].pt.x << "," << keypointsB[i].pt.y << endl;
			}
		}
	}


	// �܂�����Ȃ������炳��Ɋɂ߂�
	if (matches_good.size() <= 5) {

		matches_good.clear();
		matches_ix.clear();

		for (int i = 0; i < (int)matches.size(); i++) {
			if (matches[i].distance < threshold * 3) {
				matches_good.push_back(matches[i]);

				matches_ix.push_back(i);

				//		cout << keypointsA[i].pt.x << "," << keypointsA[i].pt.y << " - " << keypointsB[i].pt.x << "," << keypointsB[i].pt.y << endl;
			}
		}
	}

	// �܂�����Ȃ������炳��Ɋɂ߂�
	if (matches_good.size() <= 5) {

		matches_good.clear();
		matches_ix.clear();

		for (int i = 0; i < (int)matches.size(); i++) {
			if (matches[i].distance < threshold * 5) {
				matches_good.push_back(matches[i]);

				matches_ix.push_back(i);

				//		cout << keypointsA[i].pt.x << "," << keypointsA[i].pt.y << " - " << keypointsB[i].pt.x << "," << keypointsB[i].pt.y << endl;
			}
		}
	}

	// �܂�����Ȃ������炳��Ɋɂ߂�
	if (matches_good.size() <= 5) {

		matches_good.clear();
		matches_ix.clear();

		for (int i = 0; i < (int)matches.size(); i++) {
			if (matches[i].distance < threshold * 10) {
				matches_good.push_back(matches[i]);

				matches_ix.push_back(i);

				//		cout << keypointsA[i].pt.x << "," << keypointsA[i].pt.y << " - " << keypointsB[i].pt.x << "," << keypointsB[i].pt.y << endl;
			}
		}
	}

	// �܂�����Ȃ������炳��Ɋɂ߂�
	if (matches_good.size() <= 5) {

		matches_good.clear();
		matches_ix.clear();

		for (int i = 0; i < (int)matches.size(); i++) {
			if (matches[i].distance < threshold * 20) {
				matches_good.push_back(matches[i]);

				matches_ix.push_back(i);

				//		cout << keypointsA[i].pt.x << "," << keypointsA[i].pt.y << " - " << keypointsB[i].pt.x << "," << keypointsB[i].pt.y << endl;
			}
		}
	}

	// �܂�����Ȃ������炳��Ɋɂ߂�
	if (matches_good.size() <= 5) {

		matches_good.clear();
		matches_ix.clear();

		for (int i = 0; i < (int)matches.size(); i++) {
			if (matches[i].distance < threshold * 40) {
				matches_good.push_back(matches[i]);

				matches_ix.push_back(i);

				//		cout << keypointsA[i].pt.x << "," << keypointsA[i].pt.y << " - " << keypointsB[i].pt.x << "," << keypointsB[i].pt.y << endl;
			}
		}
	}

	// �܂�����Ȃ������炳��Ɋɂ߂�
	if (matches_good.size() <= 5) {

		matches_good.clear();
		matches_ix.clear();

		for (int i = 0; i < (int)matches.size(); i++) {
			if (matches[i].distance < threshold * 80) {
				matches_good.push_back(matches[i]);

				matches_ix.push_back(i);

				//		cout << keypointsA[i].pt.x << "," << keypointsA[i].pt.y << " - " << keypointsB[i].pt.x << "," << keypointsB[i].pt.y << endl;
			}
		}
	}

	/*
	// �\��
	cv::Mat matchImage;
	cv::drawMatches(imgA, keypointsA, imgB, keypointsB, matches_good, matchImage, cv::Scalar::all(-1), cv::Scalar::all(-1), std::vector<char>(), cv::DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS);
	cv::imshow("��r", matchImage);
	cv::waitKey(0);
	*/

	// std::cout << matches_good.size() << std::endl;
	if (matches_good.size() <= 3) {
		return false;
	}

	//------------------------------------------------------------------------------------------------------------------------
	// ���E�摜�̂��ꂼ��ɂ��āA�摜�̓����_��X�̍ŏ��AY�̍ŏ��A�y�сAX�̍ő�AY�̍ő�����߂�
	std::vector<cv::Point2f>ptsA, ptsB;

	// �ő�ƍŏ�

	// ���̉摜�̑S�̂̍���̓_�ƁA�E���̓_
	cv::Point2f bgnPtsA = {     0,     0 };
	cv::Point2f endPtsA = { TMPL_W, TMPL_H };

	// ���̉摜�̓����_�̍ŏ�X�ƍŏ�Y
	cv::Point2f minPtsA = { 10000, 10000 };

	// ���̉摜�̓����_�̍ő�X�ƍő�Y
	cv::Point2f maxPtsA = {     0,     0 };

	// �E�̉摜�̓����_�̍ŏ�X�ƍŏ�Y
	cv::Point2f minPtsB = { 10000, 10000 };

	// �E�̉摜�̓����_�̍ő�X�ƍő�Y
	cv::Point2f maxPtsB = { 0, 0 };
	
	// �E�̉摜�́u���̉摜�́uTopLeft�v�ƁuRightBottom�v�ɑΉ����鉼�z�̓_
	cv::Point2f bgnPtsB = {     0,     0 };
	cv::Point2f endPtsB = {     0,     0 };

	for (int j = 0; j < (int)matches_good.size(); j++) {
		// ���̉摜�̍ŏ�x�ƍŏ�y, �ő�x�ƍő�y
		auto &kA = keypointsA[matches_good[j].queryIdx].pt;
		ptsA.push_back(kA);
		if (kA.x < minPtsA.x) {
			minPtsA.x = kA.x;
		}
		if (kA.y < minPtsA.y) {
			minPtsA.y = kA.y;
		}
		if (kA.x > maxPtsA.x) {
			maxPtsA.x = kA.x;
		}
		if (kA.y > maxPtsA.y) {
			maxPtsA.y = kA.y;
		}

		// �E�̉摜�̍ŏ�x�ƍŏ�y, �ő�x�ƍő�y
		auto &kB = keypointsB[matches_good[j].trainIdx].pt;
		ptsB.push_back(kB);
		if (kB.x < minPtsB.x) {
			minPtsB.x = kB.x;
		}
		if (kB.y < minPtsB.y) {
			minPtsB.y = kB.y;
		}
		if (kB.x > maxPtsB.x) {
			maxPtsB.x = kB.x;
		}
		if (kB.y > maxPtsB.y) {
			maxPtsB.y = kB.y;
		}

	}

	//------------------------------------------------------------------------------------------------------------------------
	// ��ŋ��߂����̂��A���̉摜��LeftTop(0,0)��RightBottom(320,400)�ɑΉ�����ł��낤�A�E�摜��LeftTop��RightBottom���o��
	double wA = maxPtsA.x - minPtsA.x;
	double hA = maxPtsA.y - minPtsA.y;

	// �E�̉摜�́A�����_������͈͂̕��E����
	double wB = maxPtsB.x - minPtsB.x;
	double hB = maxPtsB.y - minPtsB.y;

	// �����_�̍ŏ��ƍő���r���Ă݂āA�c���̔䗦��������x�Ɏ��܂��Ă��邱�Ƃ��m�F����B
	// �i�������_�Ƃ��Ĉ�v���Ă���B���ꂾ���̏����ł����Ȃ萳�m�Ɂu�E�̉摜�̈ꕔ�����̉摜�i�g�k����j�v�ł���\��������
	// printf("coef %f,aaa", wA / hA);
	// printf("coef %f,aaa", wB / hB);
	double corfW = wB / wA; // ���̏k����
	double corfH = hB / hA; // �c�̏k����


	{
		double tmpW = minPtsA.x * corfW; // A��X���W��A�ɑ΂���B�̏������������������̂��c
		double bgnBX = minPtsB.x - tmpW; // B��X���W����A��L���������ƂŁAA�ʂ̍���(0,0)�ɑΉ�����ł��낤�AB��X�����_���o�Ă���

		double tmpH = minPtsA.y * corfH; // A��X���W��A�ɑ΂���B�̏������������������̂��c
		double bgnBY = minPtsB.y - tmpH; // B��Y���W����A��L���������ƂŁAA�ʂ̍���(0,0)�ɑΉ�����ł��낤�AB��Y�����_���o�Ă���

		if (bgnBX < 1) { bgnBX = 0; }
		if (bgnBY >= TMPL_W) { bgnBX = TMPL_W - 1; }
		if (bgnBY < 1) { bgnBY = 0; }
		if (bgnBY >= TMPL_H) { bgnBY = TMPL_H - 1; }

		// ���㑊���̍��W�_
		bgnPtsB.x = (float)bgnBX;
		bgnPtsB.y = (float)bgnBY;

		// �E�������̍��W�_
		double endBX = bgnBX + endPtsA.x * corfW;
		double endBY = bgnBY + endPtsA.y * corfH;

		if (endBX < 1) { endBX = 1; }
		if (endBX >= TMPL_W) { endBX = TMPL_W; }
		if (endBY < 1) { endBY = 1; }
		if (endBY >= TMPL_H) { endBY = TMPL_H; }

		// �E�������̍��W�_
		endPtsB.x = (float)endBX;
		endPtsB.y = (float)endBY;

	}

	// std::cout << bgnPtsB.x << "," << bgnPtsB.y << endl;
	// std::cout << endPtsB.x << "," << endPtsB.y << endl;


	//------------------------------------------------------------------------------------------------------------------------
	// �S�Ă̓����_�ɂ��āA�ʒu�֌W������肸��ĂȂ����ǂ������`�F�b�N����B
	// �����悤�ȉ摜�ł����Ă��A���܁`�ɁA�˔�ȓ����_�ɂȂ邱�Ƃ�����̂ŁA�u�����_�̌�/5 + 1�v�܂ł̃C���M�����[�f�[�^�͋���

	// �����_�̈ʒu�}�b�v���A���E�E�̐}�ŁA�H���Ⴄ���ǂ���������B
	// �S�̂̓����_�̐��ŁA�摜����v���Ă��Ƃ��Ă��A���܂ɐH���Ⴄ���Ƃ�����̂ŁA������x�͑Ë�����
	// ���X�̉摜���H���Ⴄ���́A�v��������H���Ⴄ�̂Œe�����Ƃ��o����
	// printf("�����_�̊e�_�̈�v��:\n");
	int iDamecntRest = 1;

	bool isAllSuperCorrect = true;
	bool isAllFollowCorrect = true;
	if (ptsA.size() < 5) {
		isAllSuperCorrect = false;
		isAllFollowCorrect = false;
	}

	// ----------------- �S�����ǂ������Ƃ��Ă��A���̍ő�ƍŏ������܂�ɏ������͈͂��ƁA�����͂��Ȃ�
	// ���̉摜�̓����_�̍ŏ�X�ƍŏ�Y
	cv::Point2f goodMinPtsA = { 10000, 10000 };

	// ���̉摜�̓����_�̍ő�X�ƍő�Y
	cv::Point2f goodMaxPtsA = { 0, 0 };

	for (int i = 0; i < ptsA.size(); i++) {
		float coefAX = ptsA[i].x / TMPL_W; // A�_��X���W�̕��ɑ΂���䗦
		float coefAY = ptsA[i].y / TMPL_H; // A�_��Y���W�̕��ɑ΂���䗦

		float coefBX = (ptsB[i].x - bgnPtsB.x) / (endPtsB.x - bgnPtsB.x); // A�_��X���W�̕��ɑ΂���䗦
		float coefBY = (ptsB[i].y - bgnPtsB.y) / (endPtsB.y - bgnPtsB.y); // A�_��Y���W�̕��ɑ΂���䗦

		// ���S�ɐ��m�ł͂Ȃ��B
		if ((coefAX / coefBX) != 1.0f || (coefAY / coefBY) != 1.0f ) {
			isAllSuperCorrect = false;
		}

		if (0.97 <= (coefAX / coefBX) && (coefAX / coefBX) <= 1.03 &&
			0.97 <= (coefAY / coefBY) && (coefAY / coefBY) <= 1.03			) {
			
		}
		else {
			isAllFollowCorrect = false;
		}

		if ( 0.95<= (coefAX / coefBX) && (coefAX / coefBX) <= 1.05 &&
			 0.95<= (coefAY / coefBY) && (coefAY / coefBY) <= 1.05
			) {
			// printf("OK! %f, %f\n", (coefAX / coefBX), (coefAY / coefBY));

			// ������x�悩�������W�̍ŏ��ƍő���ێ����Ă���
			if (ptsA[i].x < goodMinPtsA.x) {
				goodMinPtsA.x = ptsA[i].x;
			}
			if (ptsA[i].y < goodMinPtsA.y) {
				goodMinPtsA.y = ptsA[i].y;
			}
			if (ptsA[i].x > goodMaxPtsA.x) {
				goodMaxPtsA.x = ptsA[i].x;
			}
			if (ptsA[i].y > goodMaxPtsA.y) {
				goodMaxPtsA.y = ptsA[i].y;
			}



		}
		else {
			// printf("NG! %f, %f\n", (coefAX / coefBX), (coefAY / coefBY));
			iDamecntRest--;
			if (iDamecntRest < 0) {
				// printf("�����_�̈ʒu�H���Ⴂ������������");
				return 0;
			}
		}
	}

	remove("_tmpA.png");
	remove("_tmpB.png");

	//------------------------------------------------------------------------------------------------------------------------
	// �t�@�C���̏����o���B
	{
		// �E���̉摜�̈�v�����������g���~���O���ĉ摜�Ƃ��ďo��
		cv::Mat imgNewB = cv::imread(filenameB);
		cv::Mat hsv, lab, ycr;

		// �摜B�̈ꕔ�g���~���O�����̂܂܏o��
		int x = (int)round(bgnPtsB.x);
		int y = (int)round(bgnPtsB.y);
		int w = (int)round(endPtsB.x - bgnPtsB.x);
		int h = (int)round(endPtsB.y - bgnPtsB.y);
		cv::Mat roi(imgNewB, cv::Rect(x, y, w, h));	/*�g���~���O */
		// ������Org���O����Q�Ƃł���悤��
		DoubtfulB = roi;
		// cv::imwrite("_tmpB.png", roi);


		// �摜B�ŏ�q�ŏo������f���ɍ��킹�āA�摜A���o��
		cv::Mat imgNewA = cv::imread(filenameA);
		cv::Mat dst;
		// �摜B�̈ꕔ�g���~���O�����̂܂܏o��
		cv::resize(imgNewA, dst, cv::Size(w, h), 0, 0);
		
		// ������Dst���O����Q�Ƃł���悤��
		DoubtfulA = dst;
		// cv::imwrite("_tmpA.png", dst);
	}

	// �T�ȏ�ŁA�S�Ă����S�ɐ��m
	if (isAllSuperCorrect) {
		return 3;
	}

	// �T�ȏ�ŁA�S�Ă��قƂ�ǐ��m
	if (isAllFollowCorrect) {
		return 2;
	}

	// �����܂łō��i���Ă������Ɍ����Ă��A�ō���`����������ꍇ
	float imgAGoodXSub = goodMaxPtsA.x - goodMinPtsA.x;
	float imgAGoodYSub = goodMaxPtsA.y - goodMinPtsA.y;
	// printf("�ō���` %f, %f\n", imgAGoodXSub, imgAGoodYSub);
	if (imgAGoodXSub + imgAGoodYSub < 120) {
		// printf("�ō���`����������\n");
		return 0;
	}


	return true;
}


extern int KaoHistgramMatcing(char *filenameA, char *filenameB);

int main(int argc, char **argv)
{
	if (argc <= 1) {
		return 0;
	}

	char* filenameA = argv[1];

	vector<string> prefix = { "nobu11pk", "nobu12pk", "nobu13pk", "nobu14pk", "nobu14pk", "nobu15pk", "nobu16pk", "nobu17pk", "nobu18pk" };

	for (string nobu : prefix) {
		for (int i = 0; i < 9999; i++) {
			char bufnum[10] = "";
			sprintf(bufnum, "%04d", i);
			string strnum = bufnum;
			string strFileNameB = nobu + "_" + strnum + ".png";
			char* filenameB = (char *)strFileNameB.c_str();
			BOOL existsA = PathFileExists(filenameA);
			BOOL existsB = PathFileExists(filenameB);
			if (string(filenameA) == string(filenameB)) {
				continue;
			}
			// nobu**pk_0001.png �����݂��Ȃ��悤�ł́A���̌n��͑S�đ��݂��Ȃ�
			if (i == 1 && !existsB) {
				i += 9000;
			}
			if (existsA && existsB) {

				int isORBValid = doORB(filenameA, filenameB);

				// ORB���S�Ȃ��v�B�q�X�g�O��������K�v�Ȃ�
				if (isORBValid >= 2) {
					// printf("��v�F�ɂ߂č����m���ŁA����1 �� ����2 �̉摜�̈ꕔ���g�k�����f�[�^�ł��B\n", filenameA, filenameB);
					cout << filenameA << "=>" << filenameB << endl;
					cout << filenameB << "=>" << filenameA << endl << flush;
				}
				// ORB�}�b�`�ŃN���A�����B�iORB�}�b�`�ŃN���A�o���Ă鎞�_�ŁA�����}�b�`�m��������)
				else if (isORBValid) {
					// 1�Ȃ�}�b�`�A0�Ȃ�~�X�}�b�`�A-1�Ȃ�G���[
					int result = KaoHistgramMatcing("_tmpA.png", "_tmpB.png");
					if (result == 2) {
						// printf("��v�F�ɂ߂č����m���ŁA����1 �� ����2 �̉摜�̈ꕔ���g�k�����f�[�^�ł��B\n", filenameA, filenameB);
						cout << filenameA << "=>" << filenameB << endl;
						cout << filenameB << "=>" << filenameA << endl << flush;
					}
					else if (result == 1) {
						// printf("��v�F�����m���ŁA����1 �� ����2 �̉摜�̈ꕔ���g�k�����f�[�^�ł��B\n", filenameA, filenameB);
						cout << filenameA << "=>" << filenameB << endl;
						cout << filenameB << "=>" << filenameA << endl << flush;
					}
					return result;
				}
			}
		}
	}

	return 1;
}
