#ifndef KALMANFILTERTRACKER_H
#define KALMANFILTERTRACKER_H

#include <iostream>
#include <opencv.hpp>

using namespace cv;
using namespace std;

class KalmanFilterTracker
{
	KalmanFilter KF;
	Mat state;
	Mat precessNoise;
	Mat measurement;
	bool init;
public:
	vector<Rect>predict_vector;
	KalmanFilterTracker();
	virtual ~KalmanFilterTracker();
	void track(Rect rec);
	void initilizeKF(Rect rec);
	void draw(Mat img);
};

#endif // KALMANFILTERTRACKER_H
