#include <OpenCV2/OpenCV.hpp>
#include <iostream>
using namespace std;
using namespace cv;

void PlayVideo(const char* vidName)
{
	VideoCapture vid(vidName);
	
	const char* windTitle = vidName;
	if (!vid.isOpened())
	{
		cout << "\t cannot open " << vidName;
		return;
	}
	double vidFps = vid.get(CV_CAP_PROP_FPS);

	cout << "video fps = " << vidFps;
	
	cv::namedWindow(windTitle, WINDOW_AUTOSIZE);

	while (1)
	{
		Mat curFrame;

		if (!vid.read(curFrame))
		{
			cout << "cannot read " << vidName;
			break;
		}

		cv::imshow(windTitle, curFrame);

		if (cv::waitKey(30) == 27)
			break;

	}

	vid.release();
	destroyWindow(windTitle);
}

void DisplayImage(const char *imgName)
{
	Mat img = imread(imgName);
	cv::namedWindow(imgName,WINDOW_NORMAL);
	cv::imshow(imgName,img);
	waitKey(0);
	destroyWindow(imgName);
}


void StartWebCam()
{
	//0 is for video input device id. there can be multiple webcams
	VideoCapture vidCap(0);

	if (!vidCap.isOpened())
	{
		cout << "Webcam not found!";
		return;
	}

	const char* windName = "Webcam";
	namedWindow(windName,WINDOW_AUTOSIZE);

	while (true)
	{
		Mat vidFrame;
		
		if (!vidCap.read(vidFrame))
		{
			cout << "Error in reading webcam input";
			return;
		}
		imshow(windName,vidFrame);

		if (waitKey(30) == 27)
		{			
			break;
		}
	}
	vidCap.release();
	destroyWindow(windName);
}

int main()
{
	const char* windName = "Open CV input window";

	cv::namedWindow(windName,WINDOW_AUTOSIZE);
	cout << "Press i for image and v for video (i/v) ";
	while (true)
	{		
		int pressedKey = waitKey(0);
		//cout << "Pressed key is = ";

		//Press i or I to render image
		if (pressedKey == 73 || pressedKey == 105)
		{
			destroyWindow(windName);
			DisplayImage("MediaFiles/freature graphic.png");
			break;
		}

		//Press v or V to render video
		if (pressedKey == 86 || pressedKey == 118)
		{
			destroyWindow(windName);
			PlayVideo("MediaFiles/sadain.mp4");
			break;
		}

		//Press c or C to render webCam input
		if (pressedKey == 67 || pressedKey == 99)
		{
			destroyWindow(windName);
			StartWebCam();
			break;
		}
	}
	return 0;
}