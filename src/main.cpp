#include <cv.h>
#include <core/core.hpp>
#include <imgproc/imgproc.hpp>
#include <highgui/highgui.hpp>
#include <video/background_segm.hpp>

#include "RectReg.hpp"
#include "MixtureOfGaussianV2BGS.hpp"
#include "KalmanFilterTracker.hpp"
#include "Threat.hpp"

using namespace std;
using namespace cv;

int main () {
	VideoCapture cap (0); // open the default camera
	if (! cap.isOpened ()) // check if we succeeded
		return -1;

	Mat frame_aux;

	cap >> frame_aux; // get a new frame from camera
	if(frame_aux.empty())
		return -1;

	MixtureOfGaussianV2BGS bgs;   //Background Segmentation Method
	KalmanFilterTracker kft;   //Kalman Filter Tracker
	Threat threat(Size (frame_aux.cols, frame_aux.rows));   //Behavior check

	bool firstFrame = true;

	for (;;)
	{
		Mat img_input(frame_aux);
		Mat img_mask;
		Mat img_bkgmodel;

		bgs.process(img_input, img_mask, img_bkgmodel);
		//Motion detection

		medianBlur(img_mask, img_mask, 5);
		RectReg regr(img_mask.size());
		Rect theone = regr.process(img_mask);
		//Rectangle Regress

		if (firstFrame)
		{
			firstFrame = false;
			kft.track(theone);
		}
		if (theone.width < img_input.cols/1.5 && theone.height < img_input.rows && theone.height > img_input.rows/5)
			for (int i=0;i<10;i++)
				kft.track(theone);
		theone = kft.predict_vector.back();
		//track the person

		threat.check(theone);
		//check the threaten level

		if (threat.caution() && !threat.alert())
		{
			rectangle( img_input, theone, Scalar( 0,255,255 ), 2, 8, 0 );
			//caution condition
		}
		else if (threat.caution() && threat.alert())
		{
			rectangle( img_input, theone, Scalar( 0,0,255 ), 2, 8, 0 );
			//alert condition
		}
		else
		{
			rectangle( img_input, theone, Scalar( 255,255,0 ), 2, 8, 0 );
			//normal condition
		}

		imshow("input", img_input);

		cap >> frame_aux;
		if(frame_aux.empty()) break;

		if (waitKey(30) == 27)
			break;
	}
	return 0;
}
