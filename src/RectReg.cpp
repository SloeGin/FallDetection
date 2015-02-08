#include "RectReg.hpp"


Rect RectReg::process(const Mat &img_input)
{
	vector<vector<Point> > contours;
	vector<Vec4i> hierarchy;

	Mat drawing( img_input );

	findContours( img_input, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0) );

	vector<vector<Point> > contours_poly( contours.size() );
	vector<Rect> boundRect( contours.size() );
	vector<Rect> boundRect_f;

	for( size_t i = 0; i < contours.size(); i++ )
	{
		approxPolyDP( Mat(contours[i]), contours_poly[i], 3, true );
		boundRect[i] = boundingRect( Mat(contours_poly[i]) );
		if (boundRect[i].height > 5 && boundRect[i].width > 3)
			boundRect_f.push_back(boundRect[i]);
	}

	for( size_t i = 0; i< boundRect_f.size(); i++ )
	{
		if (ftl.x > boundRect_f[i].tl().x)
			ftl.x = boundRect_f[i].tl().x;
		if (ftl.y > boundRect_f[i].tl().y)
			ftl.y = boundRect_f[i].tl().y;
		if (fbr.x < boundRect_f[i].br().x)
			fbr.x = boundRect_f[i].br().x;
		if (fbr.y < boundRect_f[i].br().y)
			fbr.y = boundRect_f[i].br().y;

		rectangle( drawing, boundRect_f[i].tl(), boundRect_f[i].br(), Scalar( 255,0,0 ), 2, 8, 0 );
	}

	//imshow ("drawing",drawing);

	return Rect(ftl,fbr);
}

RectReg::RectReg(const Size framesize)
{
	ftl = Point(framesize.width,framesize.height);
	fbr = Point(0,0);
}

RectReg::~RectReg(){}
