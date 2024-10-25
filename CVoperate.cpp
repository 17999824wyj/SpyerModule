#pragma once
#include "CVoperate.h"

cv::Mat frame0, frame;
std::vector<cv::Point> cut_range;
cv::Point good_position;
int counters = 0;
Strategy* CVoperate::executer = nullptr;
int CVoperate::videoIndex = 0;

void CVoperate::setStrategy(Strategy* strategy)
{
    executer = strategy;
}

void CVoperate::setVideoIndex(int newIndex)
{
    videoIndex = newIndex;
}

// opencv����¼���ȡ
void CVoperate::get_coor(int event, int x, int y, int flags, void* param)
{
    if (event == EVENT_LBUTTONDBLCLK) {
        if (cut_range.empty()) {
            cut_range.push_back(Point(x, y));
            cout << "��һ�������������ϣ�����Ϊ��" << x << "," << y << endl;
        }
        else if (cut_range.size() == 1) {
            cut_range.push_back(Point(x, y));
            cout << "�ڶ��������������ϣ�����Ϊ��" << x << "," << y << endl;
            destroyAllWindows();
        }
    }
    else if (event == EVENT_RBUTTONDBLCLK) {
        if (cut_range.size() == 1) {
            cut_range.clear();
            cout << "����ִ�����" << endl;
        }
    }
}

// canny�㷨��ȡ��Ե
Mat CVoperate::canny_edge(Mat src)
{
    Mat gray, denoised_src, edges;
    cvtColor(src, gray, COLOR_BGR2GRAY);
    fastNlMeansDenoising(gray, denoised_src, 5);
    Canny(denoised_src, edges, 100, 200);
    return edges;
}

// ��ȡ�豸��������ͷ������
std::vector<std::wstring> CVoperate::getAllCameraNames()
{
    std::vector<std::wstring> openCVCameraNames;
    cv::VideoCapture capture;
    int numDevices = 4; // ���4������ͷ�����Ը���ʵ���������
    for (int i = 0; i < numDevices; i++) {
        capture.open(i);
        if (capture.isOpened()) {
            std::wstring cameraName = L"Camera " + std::to_wstring(i);
            if (i == 0) {
                cameraName += L" -- Default";
            }
            openCVCameraNames.push_back(cameraName);
            capture.release();
        }
        else {
            break;
        }
    }
    return openCVCameraNames;
}

void CVoperate::RUN(int x, int y, int width, int height)
{
    VideoCapture vid(videoIndex);
    vid.read(frame0);

    namedWindow("frame");
    setMouseCallback("frame", get_coor, NULL);
    while (cut_range.size() < 2) {
        vid.read(frame0);
        imshow("frame", frame0);
        waitKey(1);
    }
    while (true) {
        vid.read(frame);
        Mat cropped_frame = frame(Rect(cut_range[0], cut_range[1]));
        int height = cropped_frame.rows;
        int width = cropped_frame.cols;
        Mat canny_result = canny_edge(cropped_frame);

        vector<vector<Point>> contours;
        vector<Vec4i> hierarchy;
        findContours(canny_result, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);

        // չʾ������
        imshow("Canny Result", canny_result);
        waitKey(1);

        double minimal_distance = 0xFFFF;
        Point best_point;
        for (const auto& cont : contours) {
            for (size_t i = 0; i < cont.size(); i++) {
                double dis = pow(cont[i].x, 2) + pow(cont[i].y, 2);
                if (dis < minimal_distance) {
                    best_point = cont[i];
                    minimal_distance = dis;
                }
            }
        }
        if (!contours.empty()) {
            if (good_position == Point()) {
                good_position = best_point;
                cout << good_position << endl;
                continue;
            }
            else {
                // �жϾ�����ֵ
                if (pow(best_point.x - good_position.x, 2) + pow(best_point.y - good_position.y, 2) < 30) {
                    continue;
                }
            }
        }
        // ����ģʽ������
        executer->execute();
        // ��ȡ��ǰ���ں�ʱ��
        std::cout << "Current time: " << UtilGetTime::GetTime() << std::endl;
        break;
    }
}