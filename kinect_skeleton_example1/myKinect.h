#include <windows.h>
#include <NuiApi.h>
#include <NuiSkeleton.h>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>

const NUI_IMAGE_RESOLUTION CAMERA_RESOLUTION = NUI_IMAGE_RESOLUTION_640x480;


bool connectKinect();
void drawPoint( cv::Mat& image, Vector4 position );
void drawLine( cv::Mat& image, Vector4 pos1, Vector4 pos2);

