#include <vector>

#include "opencv2\opencv.hpp"
#include <stdio.h>

using namespace std;

//Release[hΜκ
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

	//------------------------------------------------------------------------------------------------------------------------
	// ζΗέέ` Α₯_vZάΕ
	cv::Mat imgA = cv::imread(filenameA);
	cv::Mat imgB = cv::imread(filenameB);

	// ORB
	cv::OrbFeatureDetector detector;
	cv::OrbDescriptorExtractor extractor;

	// Α₯Κo
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

	// }b`O
	std::vector<cv::DMatch> matches;
	cv::BFMatcher matcher(cv::NORM_L1, true);
	matcher.match(descriptorsA, descriptorsB, matches);

	// Ε¬£
	double min_dist = DBL_MAX;
	for (int i = 0; i < (int)matches.size(); i++){
		double dist = matches[i].distance;
		if (dist < min_dist) min_dist = dist;
	}
	if (min_dist < 1.0) min_dist = 1.0;

	// Η’yAΜέc·
	const double threshold = ORB_LOOSE_THRESHOLD * min_dist;
	std::vector<cv::DMatch> matches_good;
	std::vector<int> matches_ix;

	// άΈΝ΅IΕ`W
	for (int i = 0; i < (int)matches.size(); i++) {
		if (matches[i].distance < threshold) {
			matches_good.push_back(matches[i]);

			matches_ix.push_back(i);

	//		cout << keypointsA[i].pt.x << "," << keypointsA[i].pt.y << " - " << keypointsB[i].pt.x << "," << keypointsB[i].pt.y << endl;
		}
	}
	// std::cout << matches_good.size() << std::endl;

	// Β«θΘ©Α½ηΏεΑΖΙίι
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

	// άΎ«θΘ©Α½η³ηΙΙίι
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

	// άΎ«θΘ©Α½η³ηΙΙίι
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


	// άΎ«θΘ©Α½η³ηΙΙίι
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

	// άΎ«θΘ©Α½η³ηΙΙίι
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

	// άΎ«θΘ©Α½η³ηΙΙίι
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

	// άΎ«θΘ©Α½η³ηΙΙίι
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

	// άΎ«θΘ©Α½η³ηΙΙίι
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

	// άΎ«θΘ©Α½η³ηΙΙίι
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
	// \¦
	cv::Mat matchImage;
	cv::drawMatches(imgA, keypointsA, imgB, keypointsB, matches_good, matchImage, cv::Scalar::all(-1), cv::Scalar::all(-1), std::vector<char>(), cv::DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS);
	cv::imshow("δr", matchImage);
	cv::waitKey(0);
	*/

	// std::cout << matches_good.size() << std::endl;
	if (matches_good.size() <= 3) {
		return false;
	}

	//------------------------------------------------------------------------------------------------------------------------
	// ΆEζΜ»κΌκΙΒ’ΔAζΜΑ₯_ΜXΜΕ¬AYΜΕ¬AyΡAXΜΕεAYΜΕεπίι
	std::vector<cv::Point2f>ptsA, ptsB;

	// ΕεΖΕ¬

	// ΆΜζΜSΜΜΆγΜ_ΖAEΊΜ_
	cv::Point2f bgnPtsA = {     0,     0 };
	cv::Point2f endPtsA = { TMPL_W, TMPL_H };

	// ΆΜζΜΑ₯_ΜΕ¬XΖΕ¬Y
	cv::Point2f minPtsA = { 10000, 10000 };

	// ΆΜζΜΑ₯_ΜΕεXΖΕεY
	cv::Point2f maxPtsA = {     0,     0 };

	// EΜζΜΑ₯_ΜΕ¬XΖΕ¬Y
	cv::Point2f minPtsB = { 10000, 10000 };

	// EΜζΜΑ₯_ΜΕεXΖΕεY
	cv::Point2f maxPtsB = { 0, 0 };
	
	// EΜζΜuΆΜζΜuTopLeftvΖuRightBottomvΙΞ·ιΌzΜ_
	cv::Point2f bgnPtsB = {     0,     0 };
	cv::Point2f endPtsB = {     0,     0 };

	for (int j = 0; j < (int)matches_good.size(); j++) {
		// ΆΜζΜΕ¬xΖΕ¬y, ΕεxΖΕεy
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

		// EΜζΜΕ¬xΖΕ¬y, ΕεxΖΕεy
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
	// γΕί½ΰΜζθAΆΜζΜLeftTop(0,0)ΖRightBottom(320,400)ΙΞ·ιΕ λ€AEζΜLeftTopΖRightBottomπo·
	double wA = maxPtsA.x - minPtsA.x;
	double hA = maxPtsA.y - minPtsA.y;

	// EΜζΜAΑ₯_ͺ ιΝΝΜE³
	double wB = maxPtsB.x - minPtsB.x;
	double hB = maxPtsB.y - minPtsB.y;

	// Α₯_ΜΕ¬ΖΕεπδr΅ΔέΔAc‘Μδ¦ͺ ιφxΙϋάΑΔ’ι±ΖπmF·ιB
	// iΑ₯_Ζ΅Δκv΅Δ’ιB±κΎ―ΜπΕΰ©Θθ³mΙuEΜζΜκͺΆΜζigk θjvΕ ιΒ\«ͺ’
	// printf("coef %f,aaa", wA / hA);
	// printf("coef %f,aaa", wB / hB);
	double corfW = wB / wA; // ‘Μk¬¦
	double corfH = hB / hA; // cΜk¬¦


	{
		double tmpW = minPtsA.x * corfW; // AΜXΐWΙAΙΞ·ιBΜ¬³³¦π©―½ΰΜπc
		double bgnBX = minPtsB.x - tmpW; // BΜXΐW©ηAγLπψ­±ΖΕAAΚΜΆγ(0,0)ΙΞ·ιΕ λ€ABΜXͺ_ͺoΔ­ι

		double tmpH = minPtsA.y * corfH; // AΜXΐWΙAΙΞ·ιBΜ¬³³¦π©―½ΰΜπc
		double bgnBY = minPtsB.y - tmpH; // BΜYΐW©ηAγLπψ­±ΖΕAAΚΜΆγ(0,0)ΙΞ·ιΕ λ€ABΜYͺ_ͺoΔ­ι

		if (bgnBX < 1) { bgnBX = 0; }
		if (bgnBY >= TMPL_W) { bgnBX = TMPL_W - 1; }
		if (bgnBY < 1) { bgnBY = 0; }
		if (bgnBY >= TMPL_H) { bgnBY = TMPL_H - 1; }

		// ΆγΜΐW_
		bgnPtsB.x = (float)bgnBX;
		bgnPtsB.y = (float)bgnBY;

		// EΊΜΐW_
		double endBX = bgnBX + endPtsA.x * corfW;
		double endBY = bgnBY + endPtsA.y * corfH;

		if (endBX < 1) { endBX = 1; }
		if (endBX >= TMPL_W) { endBX = TMPL_W; }
		if (endBY < 1) { endBY = 1; }
		if (endBY >= TMPL_H) { endBY = TMPL_H; }

		// EΊΜΐW_
		endPtsB.x = (float)endBX;
		endPtsB.y = (float)endBY;

	}

	// std::cout << bgnPtsB.x << "," << bgnPtsB.y << endl;
	// std::cout << endPtsB.x << "," << endPtsB.y << endl;


	//------------------------------------------------------------------------------------------------------------------------
	// SΔΜΑ₯_ΙΒ’ΔAΚuΦWͺκθζθΈκΔΘ’©Η€©π`FbN·ιB
	// ―Άζ€ΘζΕ ΑΔΰA½ά`ΙAΛςΘΑ₯_ΙΘι±Ζͺ ιΜΕAuΑ₯_ΜΒ/5 + 1vάΕΜCM[f[^Ν·

	// Α₯_ΜΚu}bvͺAΆEEΜ}ΕAH’α€©Η€©π©ιB
	// SΜΜΑ₯_ΜΕAζͺκv΅Δ½Ζ΅ΔΰA½άΙH’α€±Ζͺ ιΜΕA ιφxΝΓ¦·ι
	// ³XΜζͺH’α€ΝAv’Α«θH’α€ΜΕe­±Ζͺoι
	printf("Α₯_Μe_Μκv«:\n");
	int iDamecntRest = 1;

	bool isAllSuperCorrect = true;
	bool isAllFollowCorrect = true;
	if (ptsA.size() < 5) {
		isAllSuperCorrect = false;
		isAllFollowCorrect = false;
	}

	// ----------------- SͺΗ©Α½Ζ΅ΔΰA»ΜΕεΖΕ¬ͺ άθΙ¬³’ΝΝΎΖAΰΎΝͺΘ’
	// ΆΜζΜΑ₯_ΜΕ¬XΖΕ¬Y
	cv::Point2f goodMinPtsA = { 10000, 10000 };

	// ΆΜζΜΑ₯_ΜΕεXΖΕεY
	cv::Point2f goodMaxPtsA = { 0, 0 };

	for (int i = 0; i < ptsA.size(); i++) {
		float coefAX = ptsA[i].x / TMPL_W; // A_ΜXΐWΜΙΞ·ιδ¦
		float coefAY = ptsA[i].y / TMPL_H; // A_ΜYΐWΜΙΞ·ιδ¦

		float coefBX = (ptsB[i].x - bgnPtsB.x) / (endPtsB.x - bgnPtsB.x); // A_ΜXΐWΜΙΞ·ιδ¦
		float coefBY = (ptsB[i].y - bgnPtsB.y) / (endPtsB.y - bgnPtsB.y); // A_ΜYΐWΜΙΞ·ιδ¦

		// ?SΙ³mΕΝΘ’B
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
			printf("OK! %f, %f\n", (coefAX / coefBX), (coefAY / coefBY));

			//  ιφxζ©Α½ΐWΜΕ¬ΖΕεπΫ΅Δ¨­
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
			printf("NG! %f, %f\n", (coefAX / coefBX), (coefAY / coefBY));
			iDamecntRest--;
			if (iDamecntRest < 0) {
				printf("Α₯_ΜΚuH’α’ͺ½·¬ι");
				return 0;
			}
		}
	}

	remove("_tmpA.png");
	remove("_tmpB.png");

	//------------------------------------------------------------------------------------------------------------------------
	// t@CΜ«o΅B
	{
		// E€ΜζΜκvͺΎ―πg~O΅ΔζΖ΅Δo·
		cv::Mat imgNewB = cv::imread(filenameB);
		cv::Mat hsv, lab, ycr;

		// ζBΜκg~Oπ»ΜάάoΝ
		int x = (int)round(bgnPtsB.x);
		int y = (int)round(bgnPtsB.y);
		int w = (int)round(endPtsB.x - bgnPtsB.x);
		int h = (int)round(endPtsB.y - bgnPtsB.y);
		cv::Mat roi(imgNewB, cv::Rect(x, y, w, h));	/*g~O */
		// φ΅’OrgπO©ηQΖΕ«ιζ€Ι
		DoubtfulB = roi;
		// cv::imwrite("_tmpB.png", roi);


		// ζBΕγqΕo΅½ζfΙνΉΔAζAπo·
		cv::Mat imgNewA = cv::imread(filenameA);
		cv::Mat dst;
		// ζBΜκg~Oπ»ΜάάoΝ
		cv::resize(imgNewA, dst, cv::Size(w, h), 0, 0);
		
		// φ΅’DstπO©ηQΖΕ«ιζ€Ι
		DoubtfulA = dst;
		// cv::imwrite("_tmpA.png", dst);
	}

	// TΒΘγΕASΔͺ?SΙ³m
	if (isAllSuperCorrect) {
		return 3;
	}

	// TΒΘγΕASΔͺΩΖρΗ³m
	if (isAllFollowCorrect) {
		return 2;
	}

	// ±±άΕΕi΅Δ’»€Ι©¦ΔΰAΕι`ͺ··¬ικ
	float imgAGoodXSub = goodMaxPtsA.x - goodMinPtsA.x;
	float imgAGoodYSub = goodMaxPtsA.y - goodMinPtsA.y;
	printf("Ει` %f, %f\n", imgAGoodXSub, imgAGoodYSub);
	if (imgAGoodXSub + imgAGoodYSub < 120) {
		printf("Ει`ͺ··¬ι\n");
		return 0;
	}


	return true;
}


extern int KaoHistgramMatcing(char *filenameA, char *filenameB);

int main(int argc, char **argv)
{
	if (argc < 3) {
		return -1;
	}

	int isORBValid = doORB(argv[1], argv[2]);

	// ORB?SΘικvBqXgO·ιKvΘ΅
	if (isORBValid >= 2) {
		printf("κvFΙίΔ’m¦ΕAψ1 Ν ψ2 ΜζΜκπgk΅½f[^Ε·B\n", argv[1], argv[2]);
	}
	// ORB}b`ΕNA΅½BiORB}b`ΕNAoΔι_ΕA}b`m¦ͺ’)
	else if (isORBValid) {
		// 1Θη}b`A0Θη~X}b`A-1ΘηG[
		int result = KaoHistgramMatcing("_tmpA.png", "_tmpB.png");
		if (result == 2) {
			printf("κvFΙίΔ’m¦ΕAψ1 Ν ψ2 ΜζΜκπgk΅½f[^Ε·B\n", argv[1], argv[2]);
		}
		else if (result == 1) {
			printf("κvF’m¦ΕAψ1 Ν ψ2 ΜζΜκπgk΅½f[^Ε·B\n", argv[1], argv[2]);
		}
		return result;
	}

	return 0;
}
