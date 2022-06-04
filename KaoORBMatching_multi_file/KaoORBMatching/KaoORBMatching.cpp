#include <vector>

#include "opencv2\opencv.hpp"
#include <stdio.h>

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
#define TMPL_W 320
#define TMPL_H 400

#define ORB_LOOSE_THRESHOLD 2

cv::Mat DoubtfulA;
cv::Mat DoubtfulB;

int doORB(char *filenameA, char *filenameB) {

	//------------------------------------------------------------------------------------------------------------------------
	// 画像読み込み～ 特徴点計算まで
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
	const double threshold = ORB_LOOSE_THRESHOLD * min_dist;
	std::vector<cv::DMatch> matches_good;
	std::vector<int> matches_ix;

	// まずは厳選でチャレンジ
	for (int i = 0; i < (int)matches.size(); i++) {
		if (matches[i].distance < threshold) {
			matches_good.push_back(matches[i]);

			matches_ix.push_back(i);

	//		cout << keypointsA[i].pt.x << "," << keypointsA[i].pt.y << " - " << keypointsB[i].pt.x << "," << keypointsB[i].pt.y << endl;
		}
	}
	// std::cout << matches_good.size() << std::endl;

	// 個数足りなかったらちょっと緩める
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

	// まだ足りなかったらさらに緩める
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

	// まだ足りなかったらさらに緩める
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


	// まだ足りなかったらさらに緩める
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

	// まだ足りなかったらさらに緩める
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

	// まだ足りなかったらさらに緩める
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

	// まだ足りなかったらさらに緩める
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

	// まだ足りなかったらさらに緩める
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

	// まだ足りなかったらさらに緩める
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
	// 表示
	cv::Mat matchImage;
	cv::drawMatches(imgA, keypointsA, imgB, keypointsB, matches_good, matchImage, cv::Scalar::all(-1), cv::Scalar::all(-1), std::vector<char>(), cv::DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS);
	cv::imshow("比較", matchImage);
	cv::waitKey(0);
	*/

	// std::cout << matches_good.size() << std::endl;
	if (matches_good.size() <= 3) {
		return false;
	}

	//------------------------------------------------------------------------------------------------------------------------
	// 左右画像のそれぞれについて、画像の特徴点のXの最小、Yの最小、及び、Xの最大、Yの最大を求める
	std::vector<cv::Point2f>ptsA, ptsB;

	// 最大と最小

	// 左の画像の全体の左上の点と、右下の点
	cv::Point2f bgnPtsA = {     0,     0 };
	cv::Point2f endPtsA = { TMPL_W, TMPL_H };

	// 左の画像の特徴点の最小Xと最小Y
	cv::Point2f minPtsA = { 10000, 10000 };

	// 左の画像の特徴点の最大Xと最大Y
	cv::Point2f maxPtsA = {     0,     0 };

	// 右の画像の特徴点の最小Xと最小Y
	cv::Point2f minPtsB = { 10000, 10000 };

	// 右の画像の特徴点の最大Xと最大Y
	cv::Point2f maxPtsB = { 0, 0 };
	
	// 右の画像の「左の画像の「TopLeft」と「RightBottom」に対応する仮想の点
	cv::Point2f bgnPtsB = {     0,     0 };
	cv::Point2f endPtsB = {     0,     0 };

	for (int j = 0; j < (int)matches_good.size(); j++) {
		// 左の画像の最小xと最小y, 最大xと最大y
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

		// 右の画像の最小xと最小y, 最大xと最大y
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
	// 上で求めたものより、左の画像のLeftTop(0,0)とRightBottom(320,400)に対応するであろう、右画像のLeftTopとRightBottomを出す
	double wA = maxPtsA.x - minPtsA.x;
	double hA = maxPtsA.y - minPtsA.y;

	// 右の画像の、特徴点がある範囲の幅・高さ
	double wB = maxPtsB.x - minPtsB.x;
	double hB = maxPtsB.y - minPtsB.y;

	// 特徴点の最小と最大を比較してみて、縦横の比率がある程度に収まっていることを確認する。
	// （＝特徴点として一致している。これだけの条件でもかなり正確に「右の画像の一部が左の画像（拡縮あり）」である可能性が高い
	// printf("coef %f,aaa", wA / hA);
	// printf("coef %f,aaa", wB / hB);
	double corfW = wB / wA; // 横の縮小率
	double corfH = hB / hA; // 縦の縮小率


	{
		double tmpW = minPtsA.x * corfW; // AのX座標にAに対するBの小ささ率をかけたものを…
		double bgnBX = minPtsB.x - tmpW; // BのX座標から、上記を引くことで、A面の左上(0,0)に対応するであろう、BのX推測点が出てくる

		double tmpH = minPtsA.y * corfH; // AのX座標にAに対するBの小ささ率をかけたものを…
		double bgnBY = minPtsB.y - tmpH; // BのY座標から、上記を引くことで、A面の左上(0,0)に対応するであろう、BのY推測点が出てくる

		if (bgnBX < 1) { bgnBX = 0; }
		if (bgnBY >= TMPL_W) { bgnBX = TMPL_W - 1; }
		if (bgnBY < 1) { bgnBY = 0; }
		if (bgnBY >= TMPL_H) { bgnBY = TMPL_H - 1; }

		// 左上相当の座標点
		bgnPtsB.x = (float)bgnBX;
		bgnPtsB.y = (float)bgnBY;

		// 右下相当の座標点
		double endBX = bgnBX + endPtsA.x * corfW;
		double endBY = bgnBY + endPtsA.y * corfH;

		if (endBX < 1) { endBX = 1; }
		if (endBX >= TMPL_W) { endBX = TMPL_W; }
		if (endBY < 1) { endBY = 1; }
		if (endBY >= TMPL_H) { endBY = TMPL_H; }

		// 右下相当の座標点
		endPtsB.x = (float)endBX;
		endPtsB.y = (float)endBY;

	}

	// std::cout << bgnPtsB.x << "," << bgnPtsB.y << endl;
	// std::cout << endPtsB.x << "," << endPtsB.y << endl;


	//------------------------------------------------------------------------------------------------------------------------
	// 全ての特徴点について、位置関係が一定よりずれてないかどうかをチェックする。
	// 同じような画像であっても、たま～に、突飛な特徴点になることがあるので、「特徴点の個数/5 + 1」までのイレギュラーデータは許す

	// 特徴点の位置マップが、左・右の図で、食い違うかどうかを見る。
	// 全体の特徴点の数で、画像が一致してたとしても、たまに食い違うことがあるので、ある程度は妥協する
	// 元々の画像が食い違う時は、思いっきり食い違うので弾くことが出来る
	printf("特徴点の各点の一致性:\n");
	int iDamecntRest = 1;

	bool isAllSuperCorrect = true;
	bool isAllFollowCorrect = true;
	if (ptsA.size() < 5) {
		isAllSuperCorrect = false;
		isAllFollowCorrect = false;
	}

	// ----------------- 全部が良かったとしても、その最大と最小があまりに小さい範囲だと、説得力がない
	// 左の画像の特徴点の最小Xと最小Y
	cv::Point2f goodMinPtsA = { 10000, 10000 };

	// 左の画像の特徴点の最大Xと最大Y
	cv::Point2f goodMaxPtsA = { 0, 0 };

	for (int i = 0; i < ptsA.size(); i++) {
		float coefAX = ptsA[i].x / TMPL_W; // A点のX座標の幅に対する比率
		float coefAY = ptsA[i].y / TMPL_H; // A点のY座標の幅に対する比率

		float coefBX = (ptsB[i].x - bgnPtsB.x) / (endPtsB.x - bgnPtsB.x); // A点のX座標の幅に対する比率
		float coefBY = (ptsB[i].y - bgnPtsB.y) / (endPtsB.y - bgnPtsB.y); // A点のY座標の幅に対する比率

		// 完全に正確ではない。
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

			// ある程度よかった座標の最小と最大を維持しておく
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
				printf("特徴点の位置食い違い数が多すぎる");
				return 0;
			}
		}
	}

	remove("_tmpA.png");
	remove("_tmpB.png");

	//------------------------------------------------------------------------------------------------------------------------
	// ファイルの書き出し。
	{
		// 右側の画像の一致部分だけをトリミングして画像として出す
		cv::Mat imgNewB = cv::imread(filenameB);
		cv::Mat hsv, lab, ycr;

		// 画像Bの一部トリミングをそのまま出力
		int x = (int)round(bgnPtsB.x);
		int y = (int)round(bgnPtsB.y);
		int w = (int)round(endPtsB.x - bgnPtsB.x);
		int h = (int)round(endPtsB.y - bgnPtsB.y);
		cv::Mat roi(imgNewB, cv::Rect(x, y, w, h));	/*トリミング */
		// 怪しいOrgを外から参照できるように
		DoubtfulB = roi;
		// cv::imwrite("_tmpB.png", roi);


		// 画像Bで上述で出した画素数に合わせて、画像Aを出す
		cv::Mat imgNewA = cv::imread(filenameA);
		cv::Mat dst;
		// 画像Bの一部トリミングをそのまま出力
		cv::resize(imgNewA, dst, cv::Size(w, h), 0, 0);
		
		// 怪しいDstを外から参照できるように
		DoubtfulA = dst;
		// cv::imwrite("_tmpA.png", dst);
	}

	// ５個以上で、全てが完全に正確
	if (isAllSuperCorrect) {
		return 3;
	}

	// ５個以上で、全てがほとんど正確
	if (isAllFollowCorrect) {
		return 2;
	}

	// ここまでで合格していそうに見えても、最高矩形が狭すぎる場合
	float imgAGoodXSub = goodMaxPtsA.x - goodMinPtsA.x;
	float imgAGoodYSub = goodMaxPtsA.y - goodMinPtsA.y;
	printf("最高矩形 %f, %f\n", imgAGoodXSub, imgAGoodYSub);
	if (imgAGoodXSub + imgAGoodYSub < 120) {
		printf("最高矩形が狭すぎる\n");
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

	// ORB完全なる一致。ヒストグラムする必要なし
	if (isORBValid >= 2) {
		printf("一致：極めて高い確率で、引数1 は 引数2 の画像の一部を拡縮したデータです。\n", argv[1], argv[2]);
	}
	// ORBマッチでクリアした。（ORBマッチでクリア出来てる時点で、相当マッチ確率が高い)
	else if (isORBValid) {
		// 1ならマッチ、0ならミスマッチ、-1ならエラー
		int result = KaoHistgramMatcing("_tmpA.png", "_tmpB.png");
		if (result == 2) {
			printf("一致：極めて高い確率で、引数1 は 引数2 の画像の一部を拡縮したデータです。\n", argv[1], argv[2]);
		}
		else if (result == 1) {
			printf("一致：高い確率で、引数1 は 引数2 の画像の一部を拡縮したデータです。\n", argv[1], argv[2]);
		}
		return result;
	}

	return 0;
}
