#include <cv.h>
#include <core/core.hpp>
#include <imgproc/imgproc.hpp>
#include <highgui/highgui.hpp>
#include <video/background_segm.hpp>

using namespace std;
using namespace cv;

class RectReg
{
	Point ftl;
	Point fbr;
public:
	RectReg(const Size framesize);
	~RectReg();

	Rect process(const Mat &img_input);
};
