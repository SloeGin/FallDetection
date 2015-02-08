#include "KalmanFilterTracker.hpp"


KalmanFilterTracker::KalmanFilterTracker()
{
    KF = KalmanFilter(8, 4, 0);
    state = Mat(8, 1, CV_32F);
    precessNoise = Mat(8, 1, CV_32F);
    measurement = Mat(4, 1, CV_32F);
    measurement.setTo(Scalar(0));
    init = true;
}

KalmanFilterTracker::~KalmanFilterTracker() {}

void KalmanFilterTracker::initilizeKF(Rect rec)
{
	KF.statePre.at<float>(0) = rec.x;
	KF.statePre.at<float>(1) = rec.y;
	KF.statePre.at<float>(2) = rec.width;
	KF.statePre.at<float>(3) = rec.height;
	KF.statePre.at<float>(4) = 0;
    KF.statePre.at<float>(5) = 0;
    KF.statePre.at<float>(6) = 0;
    KF.statePre.at<float>(7) = 0;
    KF.transitionMatrix = *(Mat_<float>(8, 8) <<	1,0,0,0,0,0,0,0,
													0,1,0,0,0,0,0,0,
													0,0,1,0,0,0,0,0,
													0,0,0,1,0,0,0,0,
													0,0,0,0,1,0,0,0,
													0,0,0,0,0,1,0,0,
													0,0,0,0,0,0,1,0,
													0,0,0,0,0,0,0,1
    );

    setIdentity(KF.measurementMatrix);
    setIdentity(KF.processNoiseCov, Scalar::all(1e-4));
    setIdentity(KF.measurementNoiseCov, Scalar::all(1e-1));
    setIdentity(KF.errorCovPost, Scalar::all(.1));

	predict_vector.clear();
    init = false;
}

void KalmanFilterTracker::track(Rect rec)
{
    if ( init )
        initilizeKF(rec);

	measurement.at<float>(0) = rec.x;
    measurement.at<float>(1) = rec.y;
	measurement.at<float>(2) = rec.width;
	measurement.at<float>(3) = rec.height;

    Mat estimated = KF.correct(measurement);
    Mat prediction = KF.predict();

    Rect predictPt(prediction.at<float>(0), prediction.at<float>(1),prediction.at<float>(2),prediction.at<float>(3));
	predict_vector.push_back(predictPt);

	vector<Rect>::iterator itl = predict_vector.begin();
	if (predict_vector.end()-predict_vector.begin() > 20)
	{
		predict_vector.erase(itl);
	}
}

void KalmanFilterTracker::draw(Mat img)
{
    for (size_t i=0; i<predict_vector.size()-1; i++)
	{
		line(img, Point(predict_vector[i].x,predict_vector[i].y),  Point(predict_vector[i+1].x,predict_vector[i+1].y), Scalar(0,255,0), 1);
    }
}
