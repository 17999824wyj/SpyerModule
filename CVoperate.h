#pragma once
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <windows.h>
#include <winUser.h>
#include <vector>

#include "TurnToDesktopStrategy.h"
#include "StartSearchStrategy.h"
#include "UtilGetTime.h"

using namespace std;
using namespace cv;
#pragma warning(disable : 4996) // ½ûÓÃ _CRT_SECURE_NO_WARNINGS ¾¯¸æ

extern cv::Mat frame0, frame;
extern std::vector<cv::Point> cut_range;
extern cv::Point good_position;
extern int counters;

class CVoperate
{
private:
	static Strategy* executer;
	static int videoIndex;
public:
	static void setStrategy(Strategy* strategy);
	static void setVideoIndex(int newIndex);
	static std::vector<std::wstring> getAllCameraNames();
	static void get_coor(int event, int x, int y, int flags, void* param);
	static Mat canny_edge(Mat src);
	static void RUN(int x = -1, int y = -1, int width = -1, int height = -1);
};