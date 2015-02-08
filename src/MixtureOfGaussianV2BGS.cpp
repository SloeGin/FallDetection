#include "MixtureOfGaussianV2BGS.hpp"

//------------------------------------------------------------------
// BackgroundSubtractorMOG2
// http://opencv.itseez.com/modules/video/doc/motion_analysis_and_object_tracking.html#backgroundsubtractormog2
//
// Gaussian Mixture-based Backbround/Foreground Segmentation Algorithm.
//
// The class implements the Gaussian mixture model background subtraction described in:
//  (1) Z.Zivkovic, Improved adaptive Gausian mixture model for background subtraction, International Conference Pattern Recognition, UK, August, 2004,
//  The code is very fast and performs also shadow detection. Number of Gausssian components is adapted per pixel.
//
//  (2) Z.Zivkovic, F. van der Heijden, Efficient Adaptive Density Estimation per Image Pixel for the Task of Background Subtraction,
//  Pattern Recognition Letters, vol. 27, no. 7, pages 773-780, 2006.
//  The algorithm similar to the standard Stauffer&Grimson algorithm with additional selection of the number of the Gaussian components based on:
//    Z.Zivkovic, F.van der Heijden, Recursive unsupervised learning of finite mixture models, IEEE Trans. on Pattern Analysis and Machine Intelligence,
//    vol.26, no.5, pages 651-656, 2004.
//------------------------------------------------------------------


void MixtureOfGaussianV2BGS::process(const Mat &img_input, Mat &img_output, Mat &img_bgmodel)
{
	if(img_input.empty())
		return;

	mog(img_input, img_foreground, alpha);

	Mat img_background;
	mog.getBackgroundImage(img_background);

	if(enableThreshold)
    	threshold(img_foreground, img_foreground, gthreshold, 255, THRESH_BINARY);

	if(showOutput)
	{
		imshow("GMM (Zivkovic&Heijden)", img_foreground);
		imshow("GMM BKG (Zivkovic&Heijden)", img_background);
	}

	img_foreground.copyTo(img_output);
	img_background.copyTo(img_bgmodel);
}

MixtureOfGaussianV2BGS::MixtureOfGaussianV2BGS(){
	alpha = 0.05;
	enableThreshold = true;
	gthreshold = 15;
	showOutput = false;
}

MixtureOfGaussianV2BGS::~MixtureOfGaussianV2BGS()
{
	std::cout << "~MixtureOfGaussianV2BGS()" << std::endl;
}

