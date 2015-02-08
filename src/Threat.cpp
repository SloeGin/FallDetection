#include "Threat.hpp"

void Threat::check(const Rect theone)
{
	if (firsttime)
	{
		for (int i = 0; i < MAXT; i++)
		{
			data.push_back(theone);
		}
		firsttime = false;
	}//initialize

	mh = 0;

	for (int i=0 ; i<MAXT; i++)
		if (mh < data[i].height)
			mh = data[i].height;
	//find the maximum height in past MAXT frames

	if (theone.br().y - data.back().br().y > -theone.height/50 && (theone.y - data.back().y)> theone.height/40 && data.back().y - data[MAXT - 2].y > theone.height/40)
		on();
	//Check if the detected person is falling

	if((data.back().y - theone.y) > theone.height/80 && data[MAXT - 2].y - data.back().y > theone.height/80)
		off();
	//Cancel the threaten if the person stand up again / remove false alert

	if (caution())
	{
		count += 1;
		if ((theone.x < 5 || framesize.width - theone.br().x < 5) && theone.width < theone.height/3)
			count -= 1;
	}
	else
	{
		count = 0;
		alarm = false;
	}
	if (count > MAXT && theone.height < mh/DHC)
		alarm = true;
	//Set the alarm on

	data.push_back(theone);

	vector<Rect>::iterator itl = data.begin();
	if (data.end()- data.begin() > MAXT)
	{
		data.erase(itl);
	}
	//delete frame MAXT frames ago
}

Threat::Threat(const Size fsize)
{
	threaten = false;
	alarm = false;
	firsttime = true;
	count = 0;
	mh = 0;
	framesize = fsize;
}

Threat::~Threat(){}

void Threat::on()
{
	threaten = true;
}
//set warning on

void Threat::off()
{
	threaten = false;
}
//set warning off

bool Threat::alert()
{
	return alarm;
}
//get alert status

bool Threat::caution()
{
	return threaten;
}
//get warning status
