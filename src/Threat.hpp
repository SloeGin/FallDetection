#include <cv.h>
#include <core/core.hpp>

#define MAXT 45
//the maximum count for frames to trigger the alarm while person fallen
#define DHC 1.5

using namespace std;
using namespace cv;

class Threat
{
	Size framesize;
	bool threaten;
	bool firsttime;
	bool alarm;
	vector<Rect> data;
	vector<int> y;
	vector<int> h;
	vector<int> w;
	int mh;
	int count;
public:
	Threat(const Size fsize);
	virtual ~Threat();
	void on();
	void off();
	void check(const Rect theone);
	bool alert();
	bool caution();
};
