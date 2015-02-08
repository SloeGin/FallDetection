#include <cv.h>
#include <core/core.hpp>
#include <highgui/highgui.hpp>
#include <video/background_segm.hpp>

using namespace std;
using namespace cv;

class MixtureOfGaussianV2BGS
{
	BackgroundSubtractorMOG2 mog;
	Mat img_foreground;
	double alpha;
	bool enableThreshold;
	int gthreshold;
	bool showOutput;

public:
	MixtureOfGaussianV2BGS();
	~MixtureOfGaussianV2BGS();

	void process(const Mat &img_input, Mat &img_output, Mat &img_bgmodel);
};
